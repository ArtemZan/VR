#include "pch.h"
#include "VR.h"


namespace VR {
	GeometryData::GeometryData()
	{

	}


	AttachedGeometryData::AttachedGeometryData(const std::shared_ptr<Batch>& batch)
		:m_batch(batch)
	{
	}

	uint8_t* AttachedGeometryData::GetVertData(size_t offset)
	{
		return m_batch->m_vertices.data() + m_vertices.offset + offset;
	}

	uint32_t AttachedGeometryData::GetIndex(size_t position)
	{
		return m_batch->m_indices[m_indices.offset + position];
	}

	void AttachedGeometryData::SetIndex(size_t position, uint32_t index)
	{
		m_batch->m_indices[m_indices.offset + position] = index;
	}

	void AttachedGeometryData::Allocate(size_t vert_size, size_t ind_count)
	{

	}

	void AttachedGeometryData::Clear()
	{

	}


	DetachedGeometryData::DetachedGeometryData()
	{
	}

	DetachedGeometryData::DetachedGeometryData(const std::unique_ptr<GeometryData>& geometry_data)
	{
		const size_t vertSize = geometry_data->GetVerticesSize();
		m_vertices.reserve(vertSize);

		for (int v = 0; v < vertSize; v++) {
			m_vertices.push_back(*geometry_data->GetVertData(v));
		}


		const size_t indCount = geometry_data->GetIndicesCount();
		m_indices.reserve(indCount);

		for (int i = 0; i < indCount; i++) {
			m_indices.push_back(geometry_data->GetIndex(i));
		}
	}

}