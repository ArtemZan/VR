#pragma once

namespace VR
{
	class MeshLoader
	{
	public:
		MeshLoader();
		void Load(const char* obj);

		Mesh mesh;
	private:

		std::vector<float> vertices;
		std::vector<uint32_t> indices;
	};
}

