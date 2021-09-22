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


#define ASSERT_3D 									\
	if (!material.Is3D())							\
	{												\
		std::cout << "Failed to change mesh (expected to be 3d)\n";	 \
		return;										\
	}

#define ASSERT_2D 									\
	if (material.Is3D())							\
	{												\
		std::cout << "Failed to change mesh (expected to be 2d)\n";	 \
		return;										\
	}

	void Mesh::Transform(const math::mat4& transform)
	{
		int vert_size = material.GetVertexSize();
		int offset = material.GetPosOffset();
		int vert_count = geometry.vertices_size / vert_size;

		//Supports only 3d (might change)
		if (material.Is3D())
		{
			for (int i = 0; i < vert_count; i++)
			{
				math::vec3& pos = *(math::vec3*)(geometry.vertices + i * vert_size + offset);
				math::vec4 pos4d(pos, 1);
				pos4d *= transform;
				pos.x = pos4d.x;
				pos.y = pos4d.y;
				pos.z = pos4d.z;
			}
		}
	}

	void Mesh::Transform(const math::mat3& transform)
	{
		int vert_size = material.GetVertexSize();
		int offset = material.GetPosOffset();
		int vert_count = geometry.vertices_size / vert_size;

		if (material.Is3D())
		{
			for (int i = 0; i < vert_count; i++)
			{
				math::vec3& pos = *(math::vec3*)(geometry.vertices + i * vert_size + offset);
				pos *= transform;
			}
		}
		else
		{
			for (int i = 0; i < vert_count; i++)
			{
				math::vec2& pos = *(math::vec2*)(geometry.vertices + i * vert_size + offset);
				math::vec3 pos3d(pos, 1);
				pos3d *= transform;
				pos.x = pos3d.x;
				pos.y = pos3d.y;
			}
		}

	}

	void Mesh::Transform(const math::mat2& transform)
	{
		int vert_size = material.GetVertexSize();
		int offset = material.GetPosOffset();
		int vert_count = geometry.vertices_size / vert_size;

		if (!material.Is3D())
		{
			for (int i = 0; i < vert_count; i++)
			{
				math::vec2& pos = *(math::vec2*)(geometry.vertices + i * vert_size + offset);
				pos *= transform;
			}
		}
	}

	void Mesh::Move(const math::vec3& bias)
	{
		ASSERT_3D;

		math::mat4 m = 1;
		m.w = { bias, 1 };

		Transform(m);

		pos.Get3D() += bias;
	}

	void Mesh::Move(const math::vec2& bias)
	{
		ASSERT_2D;

		math::mat3 m = 1;
		m.z = { bias, 1 };

		Transform(m);

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

		if (size.Is3D())
		{
			size.Get3D() *= scale;
		}
		else
		{
			size = scale;
			std::cout << "Warning: Scaling before size is set\n";
		}

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
		ASSERT_2D;

		if (size.Is2D())
		{
			size.Get2D() *= scale;
		}
		else
		{
			size = scale;
			std::cout << "Warning: Scaling before size is set\n";
		}

		int vert_size = material.GetVertexSize();
		int vert_count = geometry.vertices_size / vert_size;
		for (int i = 0; i < vert_count; i++)
		{
			math::vec2& pos = *(math::vec2*)(geometry.vertices + i * vert_size);
			pos -= center;

			pos *= scale;

			pos += center;
		}
	}

	void Mesh::Scale(const math::vec3& scale)
	{
		ASSERT_3D;

		if (pos.Is3D())
		{
			Scale(scale, pos.Get3D());
		}
		else
		{
			std::cout << "Couldn't scale because position isn't set\n";
		}
	}

	void Mesh::Scale(const math::vec2& scale)
	{
		ASSERT_2D;

		Scale(scale, pos.Get2D());
	}

	void Mesh::SetScale(const math::vec2& scale)
	{
		ASSERT_2D;

		Scale(scale / size.Get2D());
	}

	void Mesh::SetScale(const math::vec3& scale)
	{
		ASSERT_3D;

		Scale(scale / size.Get3D());
	}

	void Mesh::SetScale(const math::vec2& scale, const math::vec2& center)
	{
		ASSERT_2D;

		Scale(scale / size.Get2D(), center);
	}

	void Mesh::SetScale(const math::vec3& scale, const math::vec3& center)
	{
		ASSERT_3D;

		Scale(scale / size.Get3D(), center);
	}



	void Mesh::Square(float size)
	{
		Rect(size);
	}

	void Mesh::Rect(const math::vec2& size)
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

	void Mesh::Line(float length, float width, float border_radius, size_t border_sections)
	{
		const math::vec2 start(0);
		const math::vec2 end(start.x + length, start.y);

		pos = math::vec2();
		size = math::vec2(1);

		constexpr int MAX_BORDER_SECTIONS = 100;

		if (border_radius > width)
		{
			border_radius = width;
		}

		if (border_sections > MAX_BORDER_SECTIONS)
		{
			border_sections = border_radius / width * 10;
		}

		const int vpc = border_sections + 1; //vertices per corner

		const int pos_offset = material.GetPosOffset();
		const int color_offset = material.GetColorOffset();
		const math::vec4 color = material.GetColor();
		const int vertex_size = material.GetVertexSize();

		math::vec2 vec = end - start;
		math::vec2 side = math::normalize(vec) * math::rotate(math::PI / 2) * width;

		geometry.Alloc(vpc * 4 * vertex_size, 6 + border_sections * 4 * 3);


		math::vec2 rotation_center;
		math::vec2 rot_vec;

		const float rotation_center_offset = width - border_radius;

		for (int corner = 0; corner < 4; corner++)
		{
			switch (corner)
			{
			case 0:
				rotation_center = start - math::vec2(rotation_center_offset);
				rot_vec = {0.0, -border_radius};
				break;
			case 1:
				rotation_center = start + math::vec2(-rotation_center_offset, rotation_center_offset);
				rot_vec = { -border_radius, 0.0 };
				break;
			case 2:
				rotation_center = end + math::vec2(rotation_center_offset);
				rot_vec = { 0.0, border_radius };
				break;
			case 3:
				rotation_center = end + math::vec2(rotation_center_offset, -rotation_center_offset);
				rot_vec = { border_radius, 0.0 };
				break;
			}

			//All triangles in this half of the line include this point
			const int pivot_ind = (corner / 2 + 1) * 2 * vpc - 1;

			for (int v = 0; v < vpc; v++)
			{
				*(math::vec4*)(geometry.vertices + (corner * vpc + v) * vertex_size + color_offset) = color;

				*(math::vec2*)(geometry.vertices + (corner * vpc + v) * vertex_size + pos_offset) = rotation_center + rot_vec;

				geometry.indices[(corner * border_sections + v) * 3] = pivot_ind;
				geometry.indices[(corner * border_sections + v) * 3 + 1] = v + corner * vpc;
				geometry.indices[(corner * border_sections + v) * 3 + 2] = v + corner * vpc + 1;

				rot_vec *= math::rotate(-math::PI / 2 / border_sections);
			}

			if (corner % 2)
			{
				geometry.indices[((corner + 1) * border_sections - 1) * 3] = pivot_ind;
				geometry.indices[((corner + 1) * border_sections - 1) * 3 + 1] = corner * vpc - 1;
				geometry.indices[((corner + 1) * border_sections - 1) * 3 + 2] = corner * vpc;
			}

		}

		const int rect_ind = border_sections * 4 * 3;

		geometry.indices[rect_ind + 0] = 0;
		geometry.indices[rect_ind + 1] = vpc * 2 - 1;
		geometry.indices[rect_ind + 2] = vpc * 2;
		geometry.indices[rect_ind + 3] = vpc * 2;
		geometry.indices[rect_ind + 4] = vpc * 4 - 1;
		geometry.indices[rect_ind + 5] = 0;
	}

	void Mesh::BezierCurve(const std::vector<math::vec2>& points)
	{
	}



	void Mesh::Cube(float size)
	{
		Box(size);
	}

	void Mesh::Box(const math::vec3& size)
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

						*(math::vec3*)(vert + offset) = ((math::vec3(x, y, z) * r) * size / 2);
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


	void Mesh::SetColor(const math::vec4& color)
	{
		material.SetColor(color);

		const size_t vertex_size = material.GetVertexSize();
		const size_t vert_count = geometry.vertices_size / vertex_size;
		const size_t color_offset = material.GetColorOffset();

		for (int v = 0; v < vert_count; v++)
		{
			*(math::vec4*)(geometry.vertices + v * vertex_size + color_offset) = color;
		}
	}

	void Mesh::Shape3D(const Geometry& geo)
	{
		Shape3D(geo.vertices, geo.vertices_size, geo.indices, geo.indices_count);
	}

	bool Mesh::IsHovered(const math::mat4& mvp) const
	{
		IO* io = IO::Get();
		math::vec2 mPos = io->MousePos();
		mPos /= io->WindowSize();
		mPos.x = mPos.x * 2 - 1;
		mPos.y = 1 - mPos.y * 2;

		const size_t vertex_size = material.GetVertexSize();
		const size_t vert_count = geometry.vertices_size / vertex_size;
		const size_t pos_offset = material.GetPosOffset();

		//std::cout << "\n------------\nMouse position: {" << mPos.x << ", " << mPos.y << "}\n";

		for (int v = 0; v < geometry.indices_count - 2; v += 3)
		{
			const math::vec3 p1 = *(const math::vec3*)(geometry.vertices + (geometry.indices[v + 0] - geometry.ind_offset) * vertex_size + pos_offset);
			const math::vec3 p2 = *(const math::vec3*)(geometry.vertices + (geometry.indices[v + 1] - geometry.ind_offset) * vertex_size + pos_offset);
			const math::vec3 p3 = *(const math::vec3*)(geometry.vertices + (geometry.indices[v + 2] - geometry.ind_offset) * vertex_size + pos_offset);

			const math::vec4 p1p = math::vec4(p1.x, p1.y, p1.z, 1) * mvp;
			const math::vec4 p2p = math::vec4(p2.x, p2.y, p2.z, 1) * mvp;
			const math::vec4 p3p = math::vec4(p3.x, p3.y, p3.z, 1) * mvp;

			const math::vec2 p1d = math::vec2(p1p.x, p1p.y) / p1p.w;
			const math::vec2 p2d = math::vec2(p2p.x, p2p.y) / p2p.w;
			const math::vec2 p3d = math::vec2(p3p.x, p3p.y) / p3p.w;

			//std::cout << p1d.x << " " << p1d.y << std::endl;
			//std::cout << p2d.x << " " << p2d.y << std::endl;
			//std::cout << p3d.x << " " << p3d.y << "\n\n";

			if (math::IsInside(p1d, p2d, p3d, mPos))
			{
				//std::cout << "------------\n";
				return true;
			}
		}

		//std::cout << "------------\n";
		return false;
	}

	bool Mesh::IsHovered(const math::mat3& view) const
	{
		IO* io = IO::Get();
		math::vec2 mPos = io->MousePos();
		mPos /= io->WindowSize();
		mPos.x = mPos.x * 2 - 1;
		mPos.y = 1 - mPos.y * 2;

		const size_t vertex_size = material.GetVertexSize();
		const size_t vert_count = geometry.vertices_size / vertex_size;
		const size_t pos_offset = material.GetPosOffset();

		for (int v = 0; v < geometry.indices_count - 2; v += 3)
		{
			const math::vec2 p1 = *(const math::vec2*)(geometry.vertices + (geometry.indices[v + 0] - geometry.ind_offset) * vertex_size + pos_offset);
			const math::vec2 p2 = *(const math::vec2*)(geometry.vertices + (geometry.indices[v + 1] - geometry.ind_offset) * vertex_size + pos_offset);
			const math::vec2 p3 = *(const math::vec2*)(geometry.vertices + (geometry.indices[v + 2] - geometry.ind_offset) * vertex_size + pos_offset);

			const math::vec3 p1t = math::vec3(p1.x, p1.y, 1) * view;
			const math::vec3 p2t = math::vec3(p2.x, p2.y, 1) * view;
			const math::vec3 p3t = math::vec3(p3.x, p3.y, 1) * view;

			//std::cout << p1d.x << " " << p1d.y << std::endl;
			//std::cout << p2d.x << " " << p2d.y << std::endl;
			//std::cout << p3d.x << " " << p3d.y << "\n\n";

			if (math::IsInside({ p1t.x, p1t.y }, { p2t.x, p2t.y }, { p3t.x, p3t.y }, mPos))
			{
				//std::cout << "------------\n";
				return true;
			}
		}

		//std::cout << "------------\n";
		return false;
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