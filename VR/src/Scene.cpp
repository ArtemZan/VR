#include "pch.h"
#include "VR.h"

namespace VR
{

	Scene::Scene()
	{

	}

	Mesh Scene::AddBox(math::vec3 size, Material* material)
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

		Mesh mesh(material, geo);

		Add(&mesh);

		return mesh;
	}

	void Scene::Add(Mesh* mesh)
	{
		for (Batch& batch : batches)
		{
			if (batch.materialType == mesh->material->GetTypeID())
			{
				batch.Add(mesh);
				return;
			}
		}

		batches.emplace_back(*mesh->material);
		
		batches.back().Add(mesh);
	}

	void Scene::Add(const Mesh& mesh)
	{
		for (Batch& batch : batches)
		{
			if (batch.materialType == mesh.material->GetTypeID())
			{
				batch.Add(mesh);
				return;
			}
		}

		batches.emplace_back(*mesh.material);

		batches.back().Add(mesh);
	}


	Scene::Batch::Batch(const Material& material)
		:materialType(material.GetTypeID()), attribLayout(material.attributesLayout), shader(material.shader), vb(0)
	{
	}

	Scene::Batch::Batch(const Batch& batch)
		:materialType(batch.materialType), attribLayout(batch.attribLayout), shader(batch.shader), vertices(batch.vertices), indices(batch.indices), va(batch.va), vb(batch.vb), meshes(batch.meshes)
	{
		for (int i = 0; i < meshes.size(); i++)
		{
			meshes[i]->geometry.vertices = meshes[i]->geometry.vertices - batch.vertices.data() + vertices.data();
		}
	}

	size_t Scene::Batch::Add(const Mesh& mesh)
	{
		indices.reserve(indices.size() + mesh.geometry.indices_count);
		for (int i = 0; i < mesh.geometry.indices_count; i++)
		{
			indices.push_back(mesh.geometry.indices[i] + vertices.size() / attribLayout.GetStride());
		}
			
			int vert_size = mesh.material->attributesLayout.GetStride();
			int vert_count = mesh.geometry.vertices_size / (vert_size - sizeof(math::vec4));
			int color_offset = mesh.material->GetColorOffset();
			int new_vert_size = vert_count * vert_size;

		if (mesh.material->GetTypeID() == MATERIAL_TYPE::BASIC
			|| mesh.material->GetTypeID() == MATERIAL_TYPE::LAMBERT
			|| mesh.material->GetTypeID() == MATERIAL_TYPE::_2D)
		{

			math::vec4 color;
			switch (mesh.material->GetTypeID())
			{
			case MATERIAL_TYPE::BASIC: color = ((BasicMaterial*)mesh.material)->color; break;
			case MATERIAL_TYPE::LAMBERT: color = ((LambertMaterial*)mesh.material)->color; break;
			case MATERIAL_TYPE::_2D: color = ((_2DMaterial*)mesh.material)->color; break;
			}

			prev_place = vertices.data();
			vertices.resize(vertices.size() + new_vert_size);
			uint8_t* vert_buffer = vertices.data() + vertices.size() - new_vert_size;

			for (int i = 0; i < vert_count; i++)
			{
				memcpy(vert_buffer + i * vert_size, mesh.geometry.vertices + i * (vert_size - sizeof(math::vec4)), color_offset);
				*(math::vec4*)(vert_buffer + i * vert_size + color_offset) = color;
				memcpy(vert_buffer + i * vert_size + color_offset + sizeof(math::vec4), mesh.geometry.vertices + i * (vert_size - sizeof(math::vec4)) + color_offset, vert_size - color_offset - sizeof(math::vec4));
			}
		}
		vb.Resize(vertices.size());
		va.AddBuffer(attribLayout);

		return new_vert_size;
	}

	void Scene::Batch::Add(Mesh* mesh)
	{
		size_t added = Add(*mesh);
		for (Mesh* m : meshes)
		{
			m->geometry.vertices = m->geometry.vertices - prev_place + vertices.data();
		}
		meshes.push_back(mesh);
		mesh->geometry.indices = indices.data() + indices.size() - mesh->geometry.indices_count;
		mesh->geometry.vertices = vertices.data() + vertices.size() - added;
	}





	Mesh::Mesh(Material* material, const Geometry& geometry)
		:material(material), geometry(geometry)
	{
	}

	void Mesh::Move(math::vec3 bias)
	{
		int vert_size = material->attributesLayout.GetStride();
		int vert_count = geometry.vertices_size / (vert_size - sizeof(math::vec4)); // for now;
		for (int i = 0; i < vert_count; i++)
		{
			((float*)(geometry.vertices + i * vert_size))[0] += bias.x;
			((float*)(geometry.vertices + i * vert_size))[1] += bias.y;
			((float*)(geometry.vertices + i * vert_size))[2] += bias.z;
		}
	}

	void Mesh::Rotate(math::vec3 axis, math::vec3 center, float angle)
	{
		math::mat3 m = math::rotate(axis, angle);

		int vert_size = material->attributesLayout.GetStride();
		int vert_count = geometry.vertices_size / vert_size;
		for (int i = 0; i < vert_count; i++)
		{
			float* vertex = ((float*)(geometry.vertices + i * vert_size));
			math::vec3 v(vertex[0], vertex[1], vertex[2]);
			v -= center;
			v *= m;
			v += center;
			if (vert_size == 10 * sizeof(float))//for now
			{
				*(math::vec3*)((float*)(vertex)+7) *= m;
			}
			vertex[0] = v.x;
			vertex[1] = v.y;
			vertex[2] = v.z;
		}
	}

}