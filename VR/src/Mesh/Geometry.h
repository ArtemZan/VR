#pragma once
namespace VR
{
	struct Geometry
	{
		/*friend class Mesh;
		friend class Mesh2D;
		friend class Mesh3D;
		friend class Scene;*/

		~Geometry();
		Geometry() = default;
		Geometry(const Geometry& geo);

		//Normals?

		void SetIndOffset(size_t new_offset);

		void Alloc(size_t vertSize, size_t indCount);
		void Clear();

		size_t ind_offset = 0;

		uint8_t* vertices = nullptr;
		size_t vertices_size = 0;
		uint32_t* indices = nullptr;
		size_t indices_count = 0;

	};
}
