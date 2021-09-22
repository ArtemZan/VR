#include "pch.h"
#include "VR.h"

namespace VR
{

	Scene::Scene()
	{

	}

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

	// ! Deprecated !
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
			m->geometry.indices = m->geometry.indices - batch.indices.data() + indices.data();
		}
	}

	//! Deprecated !
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
	}

	Scene::Batch::~Batch()
	{

	}



	
}