#pragma once

namespace VR
{



	struct Scene
	{
		struct Batch
		{
			//Batch(const Material& material);
			Batch();
			Batch(const Batch& batch);
			~Batch();

			//Returns size of added vertices
			size_t Add(const Mesh& mesh);
			size_t Add(Mesh* mesh);

			std::vector<uint8_t> vertices;
			std::vector<uint32_t> indices;

			gl::VertexArray va;
			gl::VertexBuffer vb;
			std::vector<Mesh*> meshes;

		private:
			uint8_t* prev_vert_location;
		};

		Scene();

		//void AddBox(math::vec2 size, Material* material, Mesh* mesh_buffer);
		//void AddBox(math::vec3 size, Material* material, Mesh* mesh_buffer);

		std::vector<Batch> batches;

		void Add(Mesh* mesh);
		void Add(const Mesh& mesh);
	};
}
