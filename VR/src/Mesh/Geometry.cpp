#include "pch.h"
#include "VR.h"

VR::Geometry::~Geometry()
{
	//Clear();
}

VR::Geometry::Geometry(const Geometry& geo)
{
	Alloc(geo.vertices_size, geo.indices_count);
	memcpy(vertices, geo.vertices, vertices_size);
	memcpy(indices, geo.indices, indices_count * sizeof(*indices));
}


void VR::Geometry::Alloc(size_t vertSize, size_t indCount)
{
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
