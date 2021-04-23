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

		void Move(const math::vec3& bias);
		void Move(const math::vec2& bias);
		void Rotate(const math::vec3& axis, const math::vec3& center, float angle);
		void Rotate(const math::vec2& center, float angle);
		void Scale(const math::vec3& scale, const math::vec3& center);
		void Scale(const math::vec2& scale, const math::vec2& center);

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

		void AddBox(math::vec2 size, Material* material, Mesh* mesh);
		void AddBox(math::vec3 size, Material* material, Mesh* mesh_buffer);

		std::vector<Batch> batches;

		void Add(Mesh* mesh);
		void Add(const Mesh& mesh);
	};
}
