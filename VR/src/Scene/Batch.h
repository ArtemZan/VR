#pragma once

namespace VR {

	struct Batch
	{
		//Batch(const Material& material);
		Batch();
		Batch(const Batch& batch);
		~Batch();

		//Returns size of added vertices
		size_t Add(const std::shared_ptr<MeshContainer>& mesh);
		void EraseMesh(size_t mesh_ind);
		void Delete(Mesh& mesh);

		std::vector<uint8_t> vertices;
		std::vector<uint32_t> indices;

		gl::VertexArray va;
		gl::VertexBuffer vb;
		std::vector<std::shared_ptr<MeshContainer>> meshes;
	};
}