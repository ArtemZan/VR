#include "pch.h"
#include "VR.h"

namespace VR
{

	Batch::Batch()
		:m_vb(0)
	{
	}

	Batch::Batch(const Batch& batch)
		: m_vertices(batch.m_vertices), m_indices(batch.m_indices), m_va(batch.m_va), m_vb(batch.m_vb)/* SUS */, m_meshes(batch.m_meshes)
	{
		/*for (auto& m : meshes)
		{
			m->geometry.vertices = m->geometry.vertices - batch.vertices.data() + vertices.data();
			m->geometry.indices = m->geometry.indices - batch.indices.data() + indices.data();
		}*/
	}

	void Batch::Add(Mesh& mesh, const std::shared_ptr<Batch>& batch)
	{
		batch->m_meshes.push_back(mesh);

		Geometry& geo = mesh->GetGeometry();
		//geo.m_data.reset(new AttachedGeometryData();
		AttachedGeometryData* geometryData = new AttachedGeometryData(batch);

		const Material& mat = mesh->GetMaterial();

		const size_t indCount = geo.m_data->GetIndicesCount();
		const size_t verticesSize = geo.m_data->GetVerticesSize();
		const size_t vertexSize = geo.GetVertexSize();
		const size_t vertCount = verticesSize / vertexSize;

		if (verticesSize == 0)
		{
			std::cout << "Warning: trying to add mesh without vertices\n";
			return;
		}


		batch->m_indices.reserve(batch->m_indices.size() + indCount);

		for (int i = 0; i < indCount; i++)
		{
			batch->m_indices.push_back(batch->m_vertices.size() + geo.m_data->GetIndex(i));
		}

		geometryData->m_indices.offset = batch->m_vertices.size();


		batch->m_vertices.reserve(batch->m_vertices.size() + verticesSize);

		for (int i = 0; i < verticesSize; i++)
		{
			batch->m_vertices.push_back(*geo.m_data->GetVertData(i));
		}

		geo.m_data.reset(geometryData);

		batch->m_vb.Resize(batch->m_vertices.size());
		batch->m_va.AddBuffer(geo.GetLayout());

		size_t ind_offset = 0;
		size_t vert_offset = 0;
	}

	void Batch::Delete(const Mesh& mesh)
	{
		//	for (int mi = 0; mi < m_meshes.size(); mi++)
		//	{
		//		auto& m = m_meshes[mi];

		//		if (m.get() == mesh.get())
		//		{
		//			 mesh->GetGeometry().m_data->Clear();// .vertices_size;
		//			const auto vert_begin = vertices.begin() + (m->geometry.vertices - vertices.data());

		//			const size_t ind_count = m->geometry.indices_count;
		//			const auto ind_begin = indices.begin() + (m->geometry.indices - indices.data());

		//			mesh.GetGeometry().vertices_size = 0;
		//			mesh.GetGeometry().indices_count = 0;
		//			//mesh.GetGeometry() = Geometry(mesh.GetGeometry());
		//			//mesh.GetGeometry().Clear();


		//			vertices.erase(vert_begin, vert_begin + vert_size);
		//			indices.erase(ind_begin, ind_begin + ind_count);

		//			for (int fm = mi + 1; fm < meshes.size(); fm++)
		//			{
		//				meshes[fm]->geometry.vertices -= vert_size;
		//				meshes[fm]->geometry.indices -= ind_count;
		//				meshes[fm]->geometry.ind_offset -= vert_size / m->material.GetVertexSize();
		//			}

		//			meshes.erase(meshes.begin() + mi);

		//			return;
		//		}
		//	}
	}

	//void Batch::EraseMesh(size_t mesh_ind)
	//{
	//	if (mesh_ind >= meshes.size())
	//		return;

	//	auto& mesh = meshes[mesh_ind];

	//	const size_t vert_size = mesh->geometry.vertices_size;
	//	const auto vert_begin = vertices.begin() + (mesh->geometry.vertices - vertices.data());

	//	const size_t ind_count = mesh->geometry.indices_count;
	//	const auto ind_begin = indices.begin() + (mesh->geometry.indices - indices.data());

	//	mesh->geometry.vertices_size = 0;
	//	mesh->geometry.indices_count = 0;
	//	//mesh.GetGeometry() = Geometry(mesh.GetGeometry());
	//	//mesh.GetGeometry().Clear();


	//	vertices.erase(vert_begin, vert_begin + vert_size);
	//	indices.erase(ind_begin, ind_begin + ind_count);

	//	for (int fm = mesh_ind + 1; fm < meshes.size(); fm++)
	//	{
	//		meshes[fm]->geometry.vertices -= vert_size;
	//		meshes[fm]->geometry.indices -= ind_count;
	//		meshes[fm]->geometry.ind_offset -= vert_size / mesh->material.GetVertexSize();
	//	}

	//	meshes.erase(meshes.begin() + mesh_ind);
	//}


	//returns size of added vertices
	/*size_t Scene::Batch::Add(MeshContainer* mesh)
	{
		meshes.push_back(mesh);

		mesh->Attach();

		if (mesh->geometry.vertices_size == 0)
		{
			return 0;
		}

		const size_t ind_count = mesh->geometry.indices_count;
		const size_t added_vertices_size = mesh->geometry.vertices_size;
		const size_t vertex_size = mesh->material.GetVertexSize();
		const size_t added_vert_count = added_vertices_size / vertex_size;
		const size_t verices_count = vertices.size() / vertex_size;

		indices.reserve(indices.size() + ind_count);
		for (int i = 0; i < ind_count; i++)
		{
			indices.push_back(verices_count + mesh->geometry.indices[i]);
		}
		mesh->geometry.ind_offset = verices_count;

		vertices.reserve(vertices.size() + added_vertices_size);
		for (int i = 0; i < added_vertices_size; i++)
		{
			vertices.push_back(mesh->geometry.vertices[i]);
		}

		mesh->geometry.Clear();

		vb.Resize(vertices.size());
		va.AddBuffer(mesh->material.GetLayout());

		size_t ind_offset = 0;
		size_t vert_offset = 0;

		for (MeshContainer* m : meshes)
		{
			m->geometry.vertices = vertices.data() + vert_offset;
			m->geometry.indices = indices.data() + ind_offset;

			ind_offset += m->geometry.indices_count;
			vert_offset += m->geometry.vertices_size;
		}

		return added_vertices_size;
	}*/

	Batch::~Batch()
	{

	}
}