#pragma once
namespace VR
{
	struct Geometry
	{
		friend class Mesh;
		friend class Scene;

		~Geometry();
		Geometry() = default;
		Geometry(const Geometry& geo);


	private:
		uint8_t* vertices = nullptr;
		size_t vertices_size = 0;
		uint32_t* indices = nullptr;
		size_t indices_count = 0;

		//Normals?

		void Alloc(size_t vertSize, size_t indCount);
		void Clear();
	};
}
