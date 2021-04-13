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


	struct Mesh
	{
		Mesh() = default;
		Mesh(Material* material, const Geometry& geometry);

		void Move(math::vec3 bias);
		void Rotate(math::vec3 axis, math::vec3 center, float angle);

		Material* material;
		Geometry geometry;
	};


	struct Scene
	{
		struct Batch
		{
			Batch(const Material& material);
			Batch(const Batch& batch);
			~Batch();

			//Returns size of added vertices
			size_t Add(const Mesh& mesh);
			void Add(Mesh* mesh);

			std::vector<uint8_t> vertices;
			std::vector<uint32_t> indices;

			MATERIAL_TYPE materialType;
			gl::AttribLayout attribLayout;
			gl::Shader* shader;

			gl::VertexArray va;
			gl::VertexBuffer vb;
			std::vector<Mesh*> meshes;

		private:
			uint8_t* prev_place;
		};

		Scene();

		Mesh AddBox(math::vec3 size, Material* material);

		std::vector<Batch> batches;

		void Add(Mesh* mesh);
		void Add(const Mesh& mesh);
	};
}
