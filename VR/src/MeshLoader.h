#pragma once

namespace VR
{
	class MeshLoader
	{
	public:
		MeshLoader();
		void Load(const char* obj);

		inline const std::vector<float>& GetVertices() const { return vertices; }
		inline const std::vector<uint32_t>& GetIndices() const { return indices; }
		inline const Material& GetMaterial() const { return mat; }

	private:
		Material mat;
		std::vector<float> vertices;
		std::vector<uint32_t> indices;
	};
}

