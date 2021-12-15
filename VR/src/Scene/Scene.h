#pragma once
#include "./Batch.h";

namespace VR
{
	struct Scene
	{
		Scene();

		void Render();

		std::vector<std::weak_ptr<Batch>> m_batches;

		void Delete(Mesh& mesh);

		void Add(Mesh& mesh);
	private:

		void Add(Mesh& mesh, const std::shared_ptr<Batch>& batch);
	};
}
