#pragma once

namespace VR
{
	struct Material
	{
		const char* id;
		gl::Shader shader;
		gl::AttribLayout attributesLayout;
	};

	struct Scene
	{
		struct Batch
		{
			Batch(const Material& material);
			Material material; 
			std::vector<uint8_t> vertices; 
			std::vector<uint32_t> indices;
			gl::VertexArray va;
			gl::VertexBuffer* vb;
		};

		std::vector<Batch> batches;

		bool AddMaterial(const char* id, const char* shader, const gl::AttribLayout& layout);

		Batch* Add(uint8_t* vertices, size_t vertices_size, uint32_t* indices, size_t indices_count, const char* material_id);
	};
}
