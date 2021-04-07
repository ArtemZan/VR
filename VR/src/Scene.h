#pragma once

namespace VR
{
	struct Geometry
	{
		uint8_t* vertices;
		size_t vertices_size;
		uint32_t* indices;
		size_t indices_count;
	};

	struct Material
	{
		Material(const char* shader, const gl::AttribLayout& layout = {});

		gl::Shader shader;
		gl::AttribLayout attributesLayout;
	};

	struct Mesh
	{
		Mesh(const Material* material);
		Mesh(const Material* material, const Geometry& geometry);

		const Material* const material;
		Geometry geometry;
	};


	struct Scene
	{
		struct Batch
		{
			Batch(const Material* material);

			void Add(const Mesh& mesh);
			void Add(Mesh* mesh);

			const Material* const material;
			std::vector<uint8_t> vertices;
			std::vector<uint32_t> indices;
			gl::VertexArray va;
			gl::VertexBuffer vb;
			std::vector<Mesh*> meshes;
		};

		std::vector<Batch> batches;

		void Add(Mesh* mesh);
		void Add(const Mesh& mesh);
	};
}
