#pragma once
#include "./Batch.h";

namespace VR
{
	struct Scene
	{
		Scene();

		void Render();

		std::vector<Batch> batches;

		void Add(Mesh& mesh);
		void Delete(Mesh& mesh);

	private:
		void Add(const std::shared_ptr<MeshContainer>& mesh);
	};
}
