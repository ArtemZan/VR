#include "pch.h"
#include "VR.h"

namespace VR
{
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


	Scene::Batch::Batch(const Material* material)
		:material(material), vb(0)
	{
	}

	Scene::Batch::Batch(const Batch& batch)
		:material(batch.material), vertices(batch.vertices), indices(batch.indices), va(batch.va), vb(batch.vb), meshes(batch.meshes)
	{
		for (int i = 0; i < meshes.size(); i++)
		{
			meshes[i]->geometry.vertices = meshes[i]->geometry.vertices - batch.vertices.data() + vertices.data();
		}
	}

	void Scene::Batch::Add(const Mesh& mesh)
	{
		indices.reserve(indices.size() + mesh.geometry.indices_count);
		for (int i = 0; i < mesh.geometry.indices_count; i++)
		{
			indices.push_back(mesh.geometry.indices[i] + vertices.size() / material->attributesLayout.GetStride());
		}
		prev_place = vertices.data();
		vertices.insert(vertices.end(), mesh.geometry.vertices, mesh.geometry.vertices + mesh.geometry.vertices_size);
		vb.Resize(vertices.size());
		va.AddBuffer(material->attributesLayout);
	}

	void Scene::Batch::Add(Mesh* mesh)
	{
		Add(*mesh);
		for (Mesh* m : meshes)
		{
			m->geometry.vertices = m->geometry.vertices - prev_place + vertices.data();
		}
		meshes.push_back(mesh);
		mesh->geometry.indices = indices.data() + indices.size() - mesh->geometry.indices_count;
		mesh->geometry.vertices = vertices.data() + vertices.size() - mesh->geometry.vertices_size;
	}


	Material* Material::BasicMaterial;
	Material* Material::LambertMaterial;

	Material::Material(const char* shader, const gl::AttribLayout& layout)
		:shader(shader), attributesLayout(layout)
	{

	}


	Mesh::Mesh(Material* material)
		:material(material)
	{
	}

	Mesh::Mesh(Material* material, const Geometry& geometry)
		:material(material), geometry(geometry)
	{
	}

	void Mesh::Move(math::vec3 bias)
	{
		int vert_size = material->attributesLayout.GetStride();
		int vert_count = geometry.vertices_size / vert_size;
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

	Scene::Scene()
	{
		Material::BasicMaterial = new Material("Color.shader");
		Material::BasicMaterial->attributesLayout.Push<float>(3);
		Material::BasicMaterial->attributesLayout.Push<float>(4);
		
		Material::LambertMaterial = new Material("Diffuse.shader");
		Material::LambertMaterial->attributesLayout.Push<float>(3);
		Material::LambertMaterial->attributesLayout.Push<float>(4);
		Material::LambertMaterial->attributesLayout.Push<float>(3);
	}

	Mesh Scene::AddBasicBox(math::vec3 size, math::vec4 color)
	{
		float x = size.x / 2;
		float y = size.y / 2;
		float z = size.z / 2;

		float vertices[] =
		{
			 x, -y, -z, color.r, color.g, color.b, color.a,
			-x, -y, -z, color.r, color.g, color.b, color.a,
			 x,  y, -z, color.r, color.g, color.b, color.a,
			-x,  y, -z, color.r, color.g, color.b, color.a,
			 
			 x, -y,  z, color.r, color.g, color.b, color.a,
			-x, -y,  z, color.r, color.g, color.b, color.a,
			 x,  y,  z, color.r, color.g, color.b, color.a,
			-x,  y,  z, color.r, color.g, color.b, color.a,
		};

		uint32_t indices[]
		{
			2, 1, 0, 3, 1, 2,

			6, 4, 5, 5, 7, 6,

			6, 3, 2, 3, 6, 7,

			3, 5, 1, 5, 3, 7,

			0, 1, 4, 5, 4, 1,

			4, 2, 0, 6, 2, 4
		};

		Geometry geo({(uint8_t*)vertices, sizeof(vertices), indices, 36});

		Mesh mesh(Material::BasicMaterial, geo);

		Add(&mesh);

		return mesh;
	}

	/*Mesh Scene::LoadMesh(const char* OBJfile)
	{
		
	}*/
}