#include "pch.h"
#include "VR.h"

namespace VR
{

	Scene::Scene()
	{

	}

	/*void Scene::AddBox(math::vec2 size, Material* material, Mesh* mesh)
	{
		if (material->GetTypeID() == MATERIAL_TYPE::_2D || material->GetTypeID() == MATERIAL_TYPE::GUI)
		{
			float x = size.x / 2;
			float y = size.y / 2;

			float vertices[] =
			{
				 x, -y,
				-x, -y,
				 x,  y,
				-x,  y,
			};

			uint32_t indices[]
			{
				2, 1, 0,
				1, 2, 3
			};

			Geometry geo({ (uint8_t*)vertices, sizeof(vertices), indices, 6 });

			mesh->material = material;
			mesh->geometry = geo;

			Add(mesh);
		}
	}

	void Scene::AddBox(math::vec3 size, Material* material, Mesh* mesh)
	{
			float x = size.x / 2;
			float y = size.y / 2;
			float z = size.z / 2;

			float vertices[] =
			{
				 x, -y, -z,
				-x, -y, -z,
				 x,  y, -z,
				-x,  y, -z,

				 x, -y,  z,
				-x, -y,  z,
				 x,  y,  z,
				-x,  y,  z,
			};

			uint32_t indices[]
			{
				0, 1, 2, 2, 1, 3,

				5, 4, 6, 6, 7, 5,

				2, 3, 6, 7, 6, 3,

				1, 5, 3, 7, 3, 5,

				4, 1, 0, 1, 4, 5,

				0, 2, 4, 4, 2, 6
			};

			Geometry geo({ (uint8_t*)vertices, sizeof(vertices), indices, 36 });

			mesh->material = material;
			mesh->geometry = geo;

			Add(mesh);
	}*/

	void Scene::Add(Mesh* mesh)
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

	void Scene::Add(const Mesh& mesh)
	{
		for (Batch& batch : batches)
		{
			if (batch.meshes.size() == 0 || batch.meshes[0]->material.GetShaderId() == mesh.material.GetShaderId())
			{
				batch.Add(mesh);
				return;
			}
		}

		batches.emplace_back();

		batches.back().Add(mesh);
	}


	Scene::Batch::Batch()
		:vb(0)
	{
	}

	Scene::Batch::Batch(const Batch& batch)
		:vertices(batch.vertices), indices(batch.indices), va(batch.va), vb(batch.vb)/* SUS */, meshes(batch.meshes)
	{
		for (Mesh* m : meshes)
		{
			m->geometry.vertices = m->geometry.vertices - batch.vertices.data() + vertices.data();
		}
	}

	//returns size of added vertices
	size_t Scene::Batch::Add(const Mesh& mesh)
	{
		
		return 0;
	}

	//returns size of added vertices
	size_t Scene::Batch::Add(Mesh* mesh)
	{
		meshes.push_back(mesh);

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
	}

	Scene::Batch::~Batch()
	{

	}



	
}