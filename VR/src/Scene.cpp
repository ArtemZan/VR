#include "pch.h"
#include "VR.h"

namespace VR
{

	Scene::Scene()
	{

	}

	void Scene::AddBox(math::vec2 size, Material* material, Mesh* mesh)
	{
		/*if (material->GetTypeID() == MATERIAL_TYPE::_2D || material->GetTypeID() == MATERIAL_TYPE::GUI)
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
		}*/
	}

	void Scene::AddBox(math::vec3 size, Material* material, Mesh* mesh)
	{
			/*float x = size.x / 2;
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

			Add(mesh);*/
	}

	void Scene::Add(Mesh* mesh)
	{
		for (Batch& batch : batches)
		{
			if (batch.material.GetShaderId() == mesh->material.GetShaderId())
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
			if (batch.material.GetShaderId() == mesh.material.GetShaderId())
			{
				batch.Add(mesh);
				return;
			}
		}

		batches.emplace_back(mesh.material);

		batches.back().Add(mesh);
	}


	Scene::Batch::Batch(const Material& material)
		:material(material), vb(0)
	{
	}

	Scene::Batch::Batch(const Batch& batch)
		:material(batch.material), vertices(batch.vertices), indices(batch.indices), va(batch.va), vb(batch.vb)/* SUS */, meshes(batch.meshes)
	{
		for (Mesh* m : meshes)
		{
			m->geometry.vertices = m->geometry.vertices - batch.vertices.data() + vertices.data();
		}
	}

	//returns size of added vertices
	size_t Scene::Batch::Add(const Mesh& mesh)
	{
		indices.reserve(indices.size() + mesh.geometry.indices_count);

		for (int i = 0; i < mesh.geometry.indices_count; i++)
		{
			indices.push_back(mesh.geometry.indices[i] + vertices.size() / mesh.material.GetVertexSize());
		}

		int vert_size = mesh.material.GetVertexSize();
		int vert_count = mesh.geometry.vertices_size / (vert_size - sizeof(math::vec4));
		//int color_offset = mesh.material->GetColorOffset();
		int new_vert_size = vert_count * vert_size;

		math::vec4 color = mesh.material.GetColor();

		prev_vert_location = vertices.data();
		vertices.resize(vertices.size() + new_vert_size);
		uint8_t* vert_buffer = vertices.data() + vertices.size() - new_vert_size;

		for (int i = 0; i < vert_count; i++)
		{
			//Very bad stuff here
			memcpy(vert_buffer + i * vert_size, mesh.geometry.vertices + i * (vert_size - sizeof(math::vec4)), mesh.material.GetVertexSize() - sizeof(math::vec4));
			memcpy(vert_buffer + i * vert_size + (mesh.material.GetVertexSize() - sizeof(math::vec4)), &color, sizeof(math::vec4));

			//if (mesh.material.GetVertexSize() - sizeof(math::vec4) + sizeof(math::vec4) < vert_size)
				//memcpy(vert_buffer + i * vert_size + color_offset + sizeof(math::vec4), mesh.geometry.vertices + i * (vert_size - sizeof(math::vec4)) + color_offset, vert_size - color_offset - sizeof(math::vec4));
		}

		std::vector<float> testV;
		for (int i = 0; i < vertices.size(); i += 4)
		{
			testV.push_back(*(float*)(&vertices[i]));
		}

		vb.Resize(vertices.size());
		va.AddBuffer(mesh.material.GetLayout());

		for (Mesh* m : meshes)
		{
			m->geometry.vertices = m->geometry.vertices - prev_vert_location + vertices.data();
		}

		return new_vert_size;
		//return 0;
	}

	//returns size of added vertices
	size_t Scene::Batch::Add(Mesh* mesh)
	{
		size_t added = Add(*mesh);

		meshes.push_back(mesh);

		mesh->geometry.indices = indices.data() + indices.size() - mesh->geometry.indices_count;
		mesh->geometry.vertices = vertices.data() + vertices.size() - added;
		mesh->geometry.vertices_size = added;

		return added;
	}

	Scene::Batch::~Batch()
	{

	}



	
}