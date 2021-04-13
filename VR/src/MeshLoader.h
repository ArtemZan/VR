#pragma once

namespace VR
{
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

