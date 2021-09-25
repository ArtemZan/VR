#include "pch.h"
#include "VR.h"

VR::Geometry::~Geometry()
{
	//Clear();
}

VR::Geometry::Geometry(const Geometry& geo)
	:ind_offset(geo.ind_offset)
{
	Alloc(geo.vertices_size, geo.indices_count);
	memcpy(vertices, geo.vertices, vertices_size);
	memcpy(indices, geo.indices, indices_count * sizeof(*indices));

	SetIndOffset(0);
}


void VR::Geometry::SetIndOffset(size_t new_offset)
{
	size_t offset_dif = new_offset - ind_offset;

	for (int i = 0; i < indices_count; i++)
	{
		indices[i] += offset_dif;
	}

	ind_offset = new_offset;
}

void VR::Geometry::Alloc(size_t vertSize, size_t indCount)
{
	if (vertSize <= vertices_size || indCount <= indices_count)
	{
		return;
	}

	Clear();

	vertices = new uint8_t[vertSize];
	indices = new uint32_t[indCount];

	vertices_size = vertSize;
	indices_count = indCount;
}

void VR::Geometry::Clear()
{
	if (vertices != nullptr && vertices_size)
	{
		delete[] vertices;
	}

	if (indices != nullptr && indices_count)
	{
		delete[] indices;
	}
}
