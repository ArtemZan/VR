#pragma once

namespace VR {

	//Controls the memory of a geometry
	class GeometryData
	{
	public:
		virtual bool IsAttached() const = 0;


		//Data access

		virtual size_t GetVerticesSize() const = 0;

		virtual inline uint8_t* GetVertData(size_t offset) = 0;

		virtual size_t GetIndicesCount() const = 0;
		virtual inline uint32_t GetIndex(size_t position) = 0;

		virtual inline void SetIndex(size_t position, uint32_t value) = 0;


		//Memory managment
		inline void Reallocate(size_t vert_size, size_t ind_count) {
			Clear();
			Allocate(vert_size, ind_count);
		}

		virtual void Allocate(size_t vert_size, size_t ind_count) = 0;

		virtual void Clear() = 0;
	};

	//Not attached to scene
	class DetachedGeometryData : public GeometryData {
		std::vector<uint8_t> m_vertices;
		std::vector<uint32_t> m_indices;

	public:
		bool IsAttached() const override { return false; }

		inline uint8_t* GetVertData(size_t offset) override {
#ifdef DEBUG
			if (offset >= m_vertices.size()) {
				throw "Error: trying to access vertices out of bounds";
			}
#endif

			return m_vertices.data() + offset;
		}

		inline uint32_t GetIndex(size_t position) override {
#ifdef DEBUG
			if (position >= m_vertices.size()) {
				throw "Error: trying to access index out of bounds";
			}
#endif

			return m_vertices[position];
		}

		inline void SetIndex(size_t position, uint32_t index) override {
#ifdef DEBUG
			if (position >= m_indices.size()) {
				throw "Error: trying to access index out of bounds";
			}
#endif
			m_indices[position] = index;
		}


		inline void Allocate(size_t vert_size, size_t ind_count) override {
			m_vertices.resize(m_vertices.size() + vert_size);
			m_indices.resize(m_indices.size() + ind_count);
		}

		inline void Clear() override {
			m_vertices.clear();
			m_indices.clear();
		}
	};

	//Attached to scene
	class AttachedGeometryData : public GeometryData {
		std::unique_ptr<Scene> m_scene;

	public:
		bool IsAttached() const override { return true; }

		void SetScene(Scene* scene) {
			m_scene = std::unique_ptr<Scene>(scene);
		}


		void Allocate(size_t vert_size, size_t ind_count) override;

		void Clear() override;
	};
}