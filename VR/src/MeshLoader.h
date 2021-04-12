#pragma once

namespace VR
{
	class OBJLoader
	{

	public:
		void Load(const char* filepath);

	private:
		Geometry geometry;
	};

	class MeshLoader
	{
	public:
		MeshLoader();
		void Load(const char* obj, const char* mtl);

		Mesh mesh;
		LambertMaterial mat;
	private:

		std::vector<float> vertices;
		std::vector<uint32_t> indices;
	};
}

