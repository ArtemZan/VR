#include "pch.h"
#include "VR.h"

namespace VR
{
	Mesh::Mesh(const Material& material)
		:material(material)
	{

	}

	Mesh::~Mesh()
	{
	}


#define ASSERT_3D 								 \
	if (!material.Is3D())						 \
	{											 \
		std::cout << "Failed to move mesh\n";	 \
		return;									 \
	}

#define ASSERT_2D 								 \
	if (material.Is3D())						 \
	{											 \
		std::cout << "Failed to move mesh\n";	 \
		return;									 \
	}

	void Mesh::Move(const math::vec3& bias)
	{
		ASSERT_3D;

		int vert_size = material.GetVertexSize();
		int offset = material.GetPosOffset();
		int vert_count = geometry.vertices_size / vert_size;
		for (int i = 0; i < vert_count; i++)
		{
			math::vec3& vertPos = *(math::vec3*)(geometry.vertices + i * vert_size + offset);
			vertPos += bias;
		}

		pos.Get3D() += bias;
	}

	void Mesh::Move(const math::vec2& bias)
	{
		ASSERT_2D

		int vert_size = material.GetVertexSize();
		int offset = material.GetPosOffset();
		int vert_count = geometry.vertices_size / vert_size;
		for (int i = 0; i < vert_count; i++)
		{
			math::vec2& vertPos = *(math::vec2*)(geometry.vertices + i * vert_size + offset);
			vertPos += bias;
		}

		pos.Get2D() += bias;
	}

	void Mesh::MoveTo(const math::vec3& new_pos)
	{
		ASSERT_3D

		Move(new_pos - pos.Get3D());
	}

	void Mesh::MoveTo(const math::vec2& new_pos)
	{
		ASSERT_2D

		Move(new_pos - pos.Get2D());
	}

	void Mesh::Rotate(const math::vec3& axis, const math::vec3& center, float angle)
	{
		ASSERT_3D

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
		ASSERT_2D

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
		ASSERT_3D;

		int vert_size = material.GetVertexSize();
		int vert_count = geometry.vertices_size / vert_size;
		for (int i = 0; i < vert_count; i++)
		{
			math::vec3& pos = *(math::vec3*)(geometry.vertices + i * vert_size);
			pos -= center;

			pos *= scale;

			pos += center;
		}
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

	void Mesh::Scale(const math::vec3& scale)
	{
		ASSERT_3D;

		int vert_size = material.GetVertexSize();
		int vert_count = geometry.vertices_size / vert_size;
		for (int i = 0; i < vert_count; i++)
		{
			math::vec3& pos = *(math::vec3*)(geometry.vertices + i * vert_size);
			pos *= scale;
		}
	}

	void Mesh::Scale(const math::vec2& scale)
	{
		ASSERT_2D;

		Scale(scale, pos.Get2D());
	}





	void Mesh::Square(float size)
	{
		Rect(size);
	}

	void Mesh::Rect(math::vec2 size)
	{
		pos = math::vec2();
		this->size = size;

		size_t vert_size = material.GetVertexSize();
		size_t pos_offset = material.GetPosOffset();
		size_t color_offset = material.GetColorOffset();

		geometry.Alloc(vert_size * 4, 6);

		uint8_t* vert = geometry.vertices;

		for (int x = -1; x < 2; x += 2)
			for (int y = -1; y < 2; y += 2)
			{
				uint8_t* v = vert + ((x + 1) * 2 + y + 1) / 2 * vert_size;

				if (pos_offset != -1)
				{
					*(math::vec2*)(v + pos_offset) = math::vec2(x, y) * size / 2;
				}

				if (color_offset != -1)
				{
					*(math::vec4*)(v + color_offset) = material.GetColor();
				}
			}

		geometry.indices[0] = 0;
		geometry.indices[1] = 1;
		geometry.indices[2] = 2;
		geometry.indices[3] = 2;
		geometry.indices[4] = 1;
		geometry.indices[5] = 3;
	}

	void Mesh::Cube(float size)
	{
		Box(size);
	}

	void Mesh::Box(math::vec3 size)
	{
		pos = math::vec3();
		this->size = size;

		const size_t vertex_size = material.GetVertexSize();
		const size_t color_offset = material.GetColorOffset();
		const size_t pos_offset = material.GetPosOffset();

		geometry.Alloc(vertex_size * 4 * 6, 6 * 6);

		uint8_t* vert = geometry.vertices;

		for (int i = 0; i < 3; i++)
		{
			for (int x = -1; x < 2; x += 2)
				for (int y = -1; y < 2; y += 2)
					for (int z = -1; z < 2; z += 2)
					{
						size_t vi = ((x + 1) * 4 + (y + 1) * 2 + z + 1) / 2;
						size_t offset = (vi + i * 8) * vertex_size;

						*(math::vec4*)(vert + offset + color_offset) = material.GetColor();

						math::mat3 r;
						if (i == 1)
						{
							r = math::rotate({ 0.0, 1.0, 0.0 }, math::PI / 2);
						}
						if (i == 2)
						{
							r = math::rotate({ 1.0, 0.0, 0.0 }, math::PI / 2);
						}

						*(math::vec3*)(vert + offset) = ((math::vec3(x, y, z) * size / 2) * r);
					}
		}

		for (int i = 0; i < 6; i++)
		{
			geometry.indices[i * 6 + 0] = i * 4 + 0;
			geometry.indices[i * 6 + 1] = i * 4 + 1;
			geometry.indices[i * 6 + 2] = i * 4 + 2;
			geometry.indices[i * 6 + 3] = i * 4 + 2;
			geometry.indices[i * 6 + 4] = i * 4 + 1;
			geometry.indices[i * 6 + 5] = i * 4 + 3;
		}
	}

	void Mesh::Shape2D(const uint8_t* vertices, size_t vert_size, const uint32_t* indices, size_t ind_count)
	{
		pos = math::vec2();
		this->size = math::vec2(1);

		geometry.Alloc(vert_size, ind_count);

		memcpy(geometry.vertices, vertices, vert_size);
		memcpy(geometry.indices, indices, ind_count * sizeof(*indices));
	}

	void Mesh::Shape2D(const Geometry& geo)
	{
		Shape3D(geo.vertices, geo.vertices_size, geo.indices, geo.indices_count);
	}

	void Mesh::Shape3D(const uint8_t* vertices, size_t vert_size, const uint32_t* indices, size_t ind_count)
	{
		ASSERT_3D;

		pos = math::vec3();
		this->size = math::vec3(1);


		size_t vert_count = vert_size / (material.GetVertexSize() - sizeof(math::vec4));
		size_t vertex_size = material.GetVertexSize();

		geometry.Alloc(vert_count * vertex_size, ind_count);
		uint8_t* vert = geometry.vertices;

		const uint8_t* vertSrc = vertices;

		for (int i = 0; i < vert_count; i++)
		{
			memcpy(vert, vertSrc, material.GetColorOffset());
			*(math::vec4*)(vert + material.GetColorOffset()) = material.GetColor();
			memcpy(vert + material.GetColorOffset() + sizeof(math::vec4), vertSrc + material.GetColorOffset(), vertex_size - material.GetColorOffset() - sizeof(math::vec4));
			
			vert += vertex_size;
			vertSrc += vertex_size - sizeof(math::vec4);
		}

		for (int i = 0; i < ind_count; i++)
		{
			geometry.indices[i] = indices[i];
		}
	}
	
	void Mesh::Shape3D(const Geometry& geo)
	{
		Shape3D(geo.vertices, geo.vertices_size, geo.indices, geo.indices_count);
	}

	void Vec::Clear()
	{
		if (data != nullptr && size)
		{
			delete[] data;
			size = 0;
		}
	}

	Vec::Vec()
	{
	}

	Vec::Vec(const math::vec2& vec)
	{
		*this = vec;
	}

	Vec::Vec(const math::vec3& vec)
	{
		*this = vec;
	}

	Vec::Vec(const Vec& vec)
	{
		*this = vec;
	}

	Vec& Vec::operator=(const Vec& vec)
	{
		size = vec.size;
		data = new float[vec.size];
		memcpy(data, vec.data, size * 4);
		return *this;
	}

	Vec& Vec::operator=(const math::vec2& vec)
	{
		Clear();
		size = 2;
		data = (float*)new math::vec2(vec);
		return *this;
	}

	Vec& Vec::operator=(const math::vec3& vec)
	{
		Clear();
		size = 3;
		data = (float*)new math::vec3(vec);
		return *this;
	}

	Vec::~Vec()
	{
		Clear();
	}
}