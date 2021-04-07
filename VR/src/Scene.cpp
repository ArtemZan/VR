#include "pch.h"
#include "VR.h"

namespace VR
{
	Scene::Batch::Batch(const Material* material)
		:material(material), vb(0)
	{
		
	}

	void Scene::Batch::Add(const Mesh& mesh)
	{
		indices.insert(indices.end(), mesh.geometry.indices, mesh.geometry.indices + mesh.geometry.indices_count);
		vertices.insert(vertices.end(), mesh.geometry.vertices, mesh.geometry.vertices + mesh.geometry.vertices_size);
		vb.Resize(vertices.size());
		va.AddBuffer(material->attributesLayout);
	}

	void Scene::Batch::Add(Mesh* mesh)
	{
		Add(*mesh);
		meshes.push_back(mesh);
		mesh->geometry.indices = indices.data() + indices.size() - mesh->geometry.indices_count;
		mesh->geometry.vertices = vertices.data() + vertices.size() - mesh->geometry.vertices_size;
	}

	void Scene::Add(Mesh* mesh)
	{
		for (Batch& batch : batches)
		{
			if (batch.material == mesh->material)
			{
				batch.Add(mesh);
				return;
			}
		}

		batches.emplace_back(mesh->material);
		
		batches.back().Add(mesh);
	}

	void Scene::Add(const Mesh& mesh)
	{
		for (Batch& batch : batches)
		{
			if (batch.material == mesh.material)
			{
				batch.Add(mesh);
				return;
			}
		}

		batches.emplace_back(mesh.material);

		batches.back().Add(mesh);
	}

	Material::Material(const char* shader, const gl::AttribLayout& layout)
		:shader(shader), attributesLayout(layout)
	{

	}

	Mesh::Mesh(const Material* material)
		:material(material)
	{
	}

	Mesh::Mesh(const Material* material, const Geometry& geometry)
		:material(material), geometry(geometry)
	{
	}
}