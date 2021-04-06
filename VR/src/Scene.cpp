#include "pch.h"
#include "VR.h"

namespace VR
{
	Scene::Batch::Batch(const Material& material)
		:material(material)
	{
	}

	bool Scene::AddMaterial(const char* id, const char* shader, const gl::AttribLayout& layout)
	{
		for (const Batch& batch : batches)
		{
			if (batch.material.id == id)
			{
				return false;
			}
		}

		batches.emplace_back(Material({ id, shader, layout }));

		batches.back().vb = new gl::VertexBuffer(224);
		batches.back().vb->Bind();
		batches.back().material.shader.Bind();
		batches.back().material.shader.SetUniform("mvp", math::mat4(1.0f));
		batches.back().va.AddBuffer(layout);

		return true;
	}

	Scene::Batch* Scene::Add(uint8_t* vertices, size_t vertices_size, uint32_t* indices, size_t indices_count, const char* material_id)
	{
		for (Batch& batch : batches)
		{
			if (batch.material.id == material_id)
			{
				//batch.indices.reserve(batch.indices.size() + indices_count);
				batch.indices.insert(batch.indices.end(), indices, indices + indices_count);
				batch.vertices.insert(batch.vertices.end(), vertices, vertices + vertices_size);
				return &batch;
			}
		}
	}
}