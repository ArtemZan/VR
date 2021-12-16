#pragma once

namespace VR {

	struct Batch
	{
		friend class Scene;
		friend class AttachedGeometryData;

	private:
		std::vector<uint8_t> m_vertices;
		std::vector<uint32_t> m_indices;

		gl::VertexArray m_va;
		gl::VertexBuffer m_vb;
		std::vector<Mesh> m_meshes;

	public:
		//Batch(const Material& material);
		Batch();
		Batch(const Batch& batch);
		~Batch();

		static void Add(Mesh& mesh, const std::shared_ptr<Batch>& batch);
		void EraseMesh(size_t mesh_ind);
		void Delete(const Mesh& mesh);

	private:

		void Clear(AttachedGeometryData& geometry_data);
		void ClearVertices(AttachedGeometryData& geometry_data);
		void ClearIndices(AttachedGeometryData& geometry_data);

		void Reallocate(AttachedGeometryData& geometry_data, size_t vertices_size, size_t indices_count);
		void ReallocateVertices(AttachedGeometryData& geometry_data, size_t vertices_size);
		void ReallocateIndices(AttachedGeometryData& geometry_data, size_t indices_size);
	};
}
