#include "pch.h"
#include "VR.h"

namespace VR
{

	Scene::Scene()
	{

	}

	void Scene::Add(Mesh& mesh)
	{
		Add(mesh.GetData());
	}

	void Scene::Add(const std::shared_ptr<MeshContainer>& mesh)
	{
		for (Batch& batch : batches)
		{
			if (batch.meshes.size() == 0 || batch.meshes[0]->material.GetShaderId() == mesh->material.GetShaderId())
			{
				batch.Add(mesh);
				return;
			}
		}

		batches.emplace_back();

		batches.back().Add(mesh);
	}

	void Scene::Delete(Mesh& mesh)
	{
		for (Batch& batch : batches)
		{
			if (batch.meshes.size())
			{
				batch.Delete(mesh);
				return;
			}
		}
	}


	void Scene::Render()
	{

		//glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);

		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		for (Batch& batch : batches)
		{
			Material& mat = batch.meshes.front()->material;

			for (int m = 0; m < batch.meshes.size(); m++)
			{
				if (batch.vertices.data() > batch.meshes[m]->geometry.vertices 
					&& batch.vertices.data() + batch.vertices.size() < batch.meshes[m]->geometry.vertices + batch.meshes[m]->geometry.vertices_size)
				{
					batch.EraseMesh(m);
					Add(batch.meshes[m]);
				}
			}

			mat.BindShader();
			mat.SetShaderUniforms();

			batch.vb.Bind();
			batch.vb.Data(batch.vertices.size(), batch.vertices.data());
			/*for (int i = 0; i < batch.vertices.size(); i+=4)
			{
				if (i % batch.meshes[0]->material.GetVertexSize() == 0)
				{
					std::cout << std::endl;
				}
				std::cout << std::setw(8) << *(float*)(&batch.vertices[i]) << " ";
			}*/
			batch.va.Bind();
			batch.va.AddBuffer(mat.GetLayout());
			GLCall(glDrawElements(GL_TRIANGLES, batch.indices.size(), GL_UNSIGNED_INT, batch.indices.data()));
		}

		glfwSwapBuffers(Context::Get()->m_window.m_window);

	}


	Scene::Batch::Batch()
		:vb(0)
	{
	}

	Scene::Batch::Batch(const Batch& batch)
		:vertices(batch.vertices), indices(batch.indices), va(batch.va), vb(batch.vb)/* SUS */, meshes(batch.meshes)
	{
		for (auto& m : meshes)
		{
			m->geometry.vertices = m->geometry.vertices - batch.vertices.data() + vertices.data();
			m->geometry.indices = m->geometry.indices - batch.indices.data() + indices.data();
		}
	}

	//Returns size of added vertices
	size_t Scene::Batch::Add(const std::shared_ptr<MeshContainer>& mesh)
	{
		meshes.push_back(mesh);

		Geometry& geo = mesh->geometry;
		Material& mat = mesh->material;

		if (geo.vertices_size == 0)
		{
			return 0;
		}

		const size_t ind_count = geo.indices_count;
		const size_t added_vertices_size = geo.vertices_size;
		const size_t vertex_size = mat.GetVertexSize();
		const size_t added_vert_count = added_vertices_size / vertex_size;
		const size_t verices_count = vertices.size() / vertex_size;

		indices.reserve(indices.size() + ind_count);
		for (int i = 0; i < ind_count; i++)
		{
			indices.push_back(verices_count + geo.indices[i]);
		}
		geo.ind_offset = verices_count;

		vertices.reserve(vertices.size() + added_vertices_size);
		for (int i = 0; i < added_vertices_size; i++)
		{
			vertices.push_back(geo.vertices[i]);
		}

		geo.Clear();

		vb.Resize(vertices.size());
		va.AddBuffer(mat.GetLayout());

		size_t ind_offset = 0;
		size_t vert_offset = 0;

		for (auto& m : meshes)
		{
			m->geometry.vertices = vertices.data() + vert_offset;
			m->geometry.indices = indices.data() + ind_offset;

			ind_offset += m->geometry.indices_count;
			vert_offset += m->geometry.vertices_size;
		}

		return added_vertices_size;
	}

	void Scene::Batch::Delete(Mesh& mesh)
	{
		for (int mi = 0; mi < meshes.size(); mi++)
		{
			auto& m = meshes[mi];

			if (m.get() == mesh.GetData().get())
			{
				const size_t vert_size = m->geometry.vertices_size;
				const auto vert_begin = vertices.begin() + (m->geometry.vertices - vertices.data());

				const size_t ind_count = m->geometry.indices_count;
				const auto ind_begin = indices.begin() + (m->geometry.indices - indices.data());

				mesh.GetGeometry().vertices_size = 0;
				mesh.GetGeometry().indices_count = 0;
				//mesh.GetGeometry() = Geometry(mesh.GetGeometry());
				//mesh.GetGeometry().Clear();


				vertices.erase(vert_begin, vert_begin + vert_size);
				indices.erase(ind_begin, ind_begin + ind_count);

				for (int fm = mi + 1; fm < meshes.size(); fm++)
				{
					meshes[fm]->geometry.vertices -= vert_size;
					meshes[fm]->geometry.indices -= ind_count;
					meshes[fm]->geometry.ind_offset -= vert_size / m->material.GetVertexSize();
				}

				meshes.erase(meshes.begin() + mi);
			}
		}
	}

	void Scene::Batch::EraseMesh(size_t mesh_ind)
	{
		if (mesh_ind >= meshes.size())
			return;

		auto& mesh = meshes[mesh_ind];

		const size_t vert_size = mesh->geometry.vertices_size;
		const auto vert_begin = vertices.begin() + (mesh->geometry.vertices - vertices.data());

		const size_t ind_count = mesh->geometry.indices_count;
		const auto ind_begin = indices.begin() + (mesh->geometry.indices - indices.data());

		mesh->geometry.vertices_size = 0;
		mesh->geometry.indices_count = 0;
		//mesh.GetGeometry() = Geometry(mesh.GetGeometry());
		//mesh.GetGeometry().Clear();


		vertices.erase(vert_begin, vert_begin + vert_size);
		indices.erase(ind_begin, ind_begin + ind_count);

		for (int fm = mesh_ind + 1; fm < meshes.size(); fm++)
		{
			meshes[fm]->geometry.vertices -= vert_size;
			meshes[fm]->geometry.indices -= ind_count;
			meshes[fm]->geometry.ind_offset -= vert_size / mesh->material.GetVertexSize();
		}

		meshes.erase(meshes.begin() + mesh_ind);
	}

	//returns size of added vertices
	/*size_t Scene::Batch::Add(Mesh* mesh)
	{
		meshes.push_back(mesh);

		mesh->Attach();

		if (mesh->geometry.vertices_size == 0)
		{
			return 0;
		}

		const size_t ind_count = mesh->geometry.indices_count;
		const size_t added_vertices_size = mesh->geometry.vertices_size;
		const size_t vertex_size = mesh->material.GetVertexSize();
		const size_t added_vert_count = added_vertices_size / vertex_size;
		const size_t verices_count = vertices.size() / vertex_size;

		indices.reserve(indices.size() + ind_count);
		for (int i = 0; i < ind_count; i++)
		{
			indices.push_back(verices_count + mesh->geometry.indices[i]);
		}
		mesh->geometry.ind_offset = verices_count;

		vertices.reserve(vertices.size() + added_vertices_size);
		for (int i = 0; i < added_vertices_size; i++)
		{
			vertices.push_back(mesh->geometry.vertices[i]);
		}

		mesh->geometry.Clear();

		vb.Resize(vertices.size());
		va.AddBuffer(mesh->material.GetLayout());

		size_t ind_offset = 0;
		size_t vert_offset = 0;

		for (Mesh* m : meshes)
		{	
			m->geometry.vertices = vertices.data() + vert_offset;
			m->geometry.indices = indices.data() + ind_offset;

			ind_offset += m->geometry.indices_count;
			vert_offset += m->geometry.vertices_size;
		}

		return added_vertices_size;
	}*/

	Scene::Batch::~Batch()
	{

	}



	
}