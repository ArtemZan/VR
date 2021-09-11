#include "pch.h"
#include "VR.h"

namespace VR
{
	Mesh::Mesh(const Material& material, const Geometry& geometry)
		:material(material), geometry(geometry)
	{

	}



	void Mesh::Move(const math::vec3& bias)
	{
		if (material.Is3D())
		{
			std::cout << "Failed to move mesh\n";
			return;
		}

		int vert_size = material.GetVertexSize();
		int offset = material.GetPosOffset();
		int vert_count = geometry.vertices_size / vert_size;
		for (int i = 0; i < vert_count; i++)
		{
			math::vec3& vertPos = *(math::vec3*)(geometry.vertices + i * vert_size + offset);
			vertPos += bias;
		}
	}

	void Mesh::Move(const math::vec2& bias)
	{
		if (material.Is3D())
		{
			std::cout << "Failed to move mesh\n";
			return;
		}

		int vert_size = material.GetVertexSize();
		int offset = material.GetPosOffset();
		int vert_count = geometry.vertices_size / vert_size;
		for (int i = 0; i < vert_count; i++)
		{
			math::vec2& vertPos = *(math::vec2*)(geometry.vertices + i * vert_size + offset);
			vertPos += bias;
		}
	}

	void Mesh::Rotate(const math::vec3& axis, const math::vec3& center, float angle)
	{
		if (!material.Is3D())
		{
			std::cout << "Failed to move mesh\n";
			return;
		}

		math::mat3 m = math::rotate(axis, angle);

		int vert_size = material.GetVertexSize();
		int vert_count = geometry.vertices_size / vert_size;

		for (int i = 0; i < vert_count; i++)
		{
			math::vec3& v = *(math::vec3*)(geometry.vertices + i * vert_size + material.GetPosOffset());
			v -= center;
			v *= m;
			v += center;
			if (material.HasNormals())
			{
				*(math::vec3*)(geometry.vertices + i * vert_size + material.GetNormalOffset()) *= m;//Anything else?
			}
		}
	}

	void Mesh::Rotate(const math::vec2& center, float angle)
	{
		if (material.Is3D())
		{
			std::cout << "Failed to move mesh\n";
			return;
		}

		math::mat2 m = math::rotate(angle);

		int vert_size = material.GetVertexSize();
		int vert_count = geometry.vertices_size / vert_size;

		for (int i = 0; i < vert_count; i++)
		{
			math::vec2& v = *(math::vec2*)(geometry.vertices + i * vert_size + material.GetPosOffset());
			v -= center;
			v *= m;
			v += center;
			if (material.HasNormals())
			{
				*(math::vec2*)(geometry.vertices + i * vert_size + material.GetNormalOffset()) *= m;//Anything else?
			}
		}
	}

	void Mesh::Scale(const math::vec3& scale, const math::vec3& center)
	{
		/*int vert_size = material->attributesLayout.GetStride();
		int vert_count = geometry.vertices_size / vert_size;
		for (int i = 0; i < vert_count; i++)
		{
			math::vec3& pos = *(math::vec3*)(geometry.vertices + i * vert_size);
			pos -= center;

			pos *= scale;

			pos += center;
		}*/
	}

	void Mesh::Scale(const math::vec2& scale, const math::vec2& center)
	{
		/*int vert_size = material->attributesLayout.GetStride();
		int vert_count = geometry.vertices_size / vert_size;
		for (int i = 0; i < vert_count; i++)
		{
			math::vec2& pos = *(math::vec2*)(geometry.vertices + i * vert_size);
			pos -= center;

			pos *= scale;

			pos += center;
		}*/
	}
}