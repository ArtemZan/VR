#include "pch.h"
#include "VR.h"

namespace VR
{
	MeshContainer::MeshContainer(const Material& material, const Geometry& geometry)
		:material(material), geometry(geometry)
	{
	}

	MeshContainer::~MeshContainer()
	{

	}


	Mesh::Mesh(const Material& material)
		:mesh(std::make_shared<MeshContainer>(material))
	{

	}

	Mesh::Mesh(const Mesh& mesh)
		: mesh(std::make_shared<MeshContainer>(mesh.GetMaterial(), mesh.GetGeometry()))
	{
	}

	Mesh::~Mesh()
	{
		if (mesh.use_count() == 1)
		{
			mesh->geometry.Clear();
		}
	}


	void Mesh::SetColor(const math::vec4& color)
	{
		Material& material = GetMaterial();
		Geometry& geometry = GetGeometry();

		material.SetColor(color);

		if (geometry.vertices_size == 0)
		{
			return;
		}

		const size_t vertex_size = material.GetVertexSize();
		const size_t vert_count = geometry.vertices_size / vertex_size;
		const size_t color_offset = material.GetColorOffset();

		for (int v = 0; v < vert_count; v++)
		{
			*(math::vec4*)(geometry.vertices + v * vertex_size + color_offset) = color;
		}
	}

	void Mesh::Transform(const math::mat4& transform)
	{
		Material& material = mesh->material;
		Geometry& geometry = mesh->geometry;

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
		Material& material = mesh->material;
		Geometry& geometry = mesh->geometry;

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
		Material& material = mesh->material;
		Geometry& geometry = mesh->geometry;

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

	math::vec4& Mesh::GetColor(size_t vertex) const
	{
		const int vert_offset = vertex * mesh->material.GetVertexSize();
		if (vert_offset >= mesh->geometry.vertices_size)
		{
			std::cout << "Tried to access vertex that is out of range\n";
		}

		return *(math::vec4*)(mesh->geometry.vertices + vert_offset + mesh->material.GetColorOffset());
	}

	Mesh3D::Mesh3D(const Material& material)
		:Mesh(material)
	{

	}

	void Mesh3D::Move(const math::vec3& bias)
	{


		math::mat4 m = 1;
		m.w = { bias, 1 };

		Transform(m);

		pos += bias;
	}

	void Mesh3D::MoveTo(const math::vec3& new_pos)
	{


		Move(new_pos - pos);
	}


	void Mesh3D::Rotate(const math::vec3& axis, const math::vec3& center, float angle)
	{
		Material& material = mesh->material;
		Geometry& geometry = mesh->geometry;

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
				*(math::vec3*)(geometry.vertices + i * vert_size + material.GetNormalOffset()) *= m;
			}
		}
	}


	void Mesh3D::Scale(const math::vec3& scale, const math::vec3& center)
	{
		Material& material = mesh->material;
		Geometry& geometry = mesh->geometry;

		size *= scale;

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

	void Mesh3D::Scale(const math::vec3& scale)
	{
		Scale(scale, pos);
	}

	void Mesh3D::SetScale(const math::vec3& scale)
	{
		Scale(scale / size);
	}

	void Mesh3D::SetScale(const math::vec3& scale, const math::vec3& center)
	{
		Scale(scale / size, center);
	}


	void Mesh3D::Cube(float size)
	{
		Box(size);
	}

	void Mesh3D::Box(const math::vec3& size)
	{
		Material& material = mesh->material;
		Geometry& geometry = mesh->geometry;

		pos = math::vec3();
		this->size = size;

		const size_t vertex_size = material.GetVertexSize();
		const size_t color_offset = material.GetColorOffset();
		const size_t pos_offset = material.GetPosOffset();

		geometry.Alloc(vertex_size * 4 * 6, 6 * 6);

		uint8_t* vert = geometry.vertices;

		math::mat3 rot = math::rotate({ 0.0, 1.0, 0.0 }, math::PI / 2);

		*(math::vec3*)(vert + vertex_size * 0 + pos_offset) = -size;
		*(math::vec3*)(vert + vertex_size * 1 + pos_offset) = { -size.x, size.y, -size.z };
		*(math::vec3*)(vert + vertex_size * 2 + pos_offset) = { size.x, -size.y, -size.z };
		*(math::vec3*)(vert + vertex_size * 3 + pos_offset) = { size.x, size.y, -size.z };


		*(math::vec3*)(vert + vertex_size * 0 + color_offset) = material.GetColor();
		*(math::vec3*)(vert + vertex_size * 1 + color_offset) = material.GetColor();
		*(math::vec3*)(vert + vertex_size * 2 + color_offset) = material.GetColor();
		*(math::vec3*)(vert + vertex_size * 3 + color_offset) = material.GetColor();

		for (int s = 1; s < 6; s++)
		{
			for (int v = 0; v < 4; v++)
			{
				*(math::vec3*)(vert + vertex_size * (4 * s + v) + color_offset) = material.GetColor();
				*(math::vec3*)(vert + vertex_size * (4 * s + v) + pos_offset) = *(math::vec3*)(vert + vertex_size * (4 * (s - 1) + v) + pos_offset) * rot;
			}

			if (s == 3)
			{
				rot = math::rotate({ 0.f, 0.f, 1.f }, math::PI / 2);
			}

			if (s == 4)
			{
				rot = rot * rot;
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

	void Mesh3D::Shape(const uint8_t* vertices, size_t vert_size, const uint32_t* indices, size_t ind_count)
	{
		Material& material = mesh->material;
		Geometry& geometry = mesh->geometry;

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

	void Mesh3D::Shape(const Geometry& geo)
	{
		Shape(geo.vertices, geo.vertices_size, geo.indices, geo.indices_count);
	}


	bool Mesh3D::IsHovered(const math::mat4& mvp) const
	{
		Material& material = mesh->material;
		Geometry& geometry = mesh->geometry;

		IO* io = IO::Get();
		math::vec2 mPos = io->MousePos();
		mPos /= io->WindowSize();
		mPos.x = mPos.x * 2 - 1;
		mPos.y = 1 - mPos.y * 2;

		const size_t vertex_size = material.GetVertexSize();
		const size_t vert_count = geometry.vertices_size / vertex_size;
		const size_t pos_offset = material.GetPosOffset();

		//std::cout << "\n------------\nMouse position: {" << mPos.x << ", " << mPos.y << "}\n";

		for (int v = 0; v < int(geometry.indices_count) - 2; v += 3)
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

	void Mesh3D::CreateNormals()
	{
		Geometry& geo = mesh->geometry;
		const Material& mat = mesh->material;

		const size_t normal_offset = mat.GetNormalOffset();
		const size_t pos_offset = mat.GetPosOffset();
		const size_t vertex_size = mat.GetVertexSize();

		if (normal_offset == -1)
			return;


		for (int i = 0; i < geo.indices_count; i += 3)
		{
			uint8_t* v1 = geo.vertices + (geo.indices[i] - geo.ind_offset) * vertex_size;
			uint8_t* v2 = geo.vertices + (geo.indices[i + 1] - geo.ind_offset) * vertex_size;
			uint8_t* v3 = geo.vertices + (geo.indices[i + 2] - geo.ind_offset) * vertex_size;

			math::vec3 norm = math::cross(*(math::vec3*)(v2 + pos_offset) - *(math::vec3*)(v1 + pos_offset), *(math::vec3*)(v3 + pos_offset) - *(math::vec3*)(v1 + pos_offset));

			norm.normalize();

			*(math::vec3*)(v1 + normal_offset) = *(math::vec3*)(v2 + normal_offset) = *(math::vec3*)(v3 + normal_offset) = norm;
		}
	}

	void Mesh3D::ShadeSmooth(float distance_treshold)
	{
		Geometry& geo = mesh->geometry;
		const Material& mat = mesh->material;

		const size_t normal_offset = mat.GetNormalOffset();
		const size_t pos_offset = mat.GetPosOffset();
		const size_t vertex_size = mat.GetVertexSize();

		if (normal_offset == -1)
			return;

		struct VecComparator
		{
			bool operator()(const math::vec3& v1, const math::vec3& v2) const
			{
				return double(v1.x) * 1e10 + double(v1.y) * 1e5 + v1.z < double(v2.x) * 1e10 + double(v2.y) * 1e5 + v2.z;
			}
		};

		std::map<math::vec3, math::vec3, VecComparator> normals;

		for (int v = 0; v < geo.vertices_size / vertex_size; v++)
		{
			normals[*(math::vec3*)(geo.vertices + v * vertex_size + pos_offset)] += *(math::vec3*)(geo.vertices + v * vertex_size + normal_offset);
		}

		for (auto& [pos, normal] : normals)
		{
			normal.normalize();
		}

		for (int v = 0; v < geo.vertices_size / vertex_size; v++)
		{
			*(math::vec3*)(geo.vertices + v * vertex_size + normal_offset) = normals[*(math::vec3*)(geo.vertices + v * vertex_size + pos_offset)];
		}
	}



	void Mesh2D::Move(const math::vec2& bias)
	{

		math::mat3 m = 1;
		m.z = { bias, 1 };

		Transform(m);

		pos += bias;
	}

	void Mesh2D::MoveTo(const math::vec2& new_pos)
	{
		Move(new_pos - pos);
	}


	void Mesh2D::Rotate(const math::vec2& center, float angle)
	{
		Material& material = mesh->material;
		Geometry& geometry = mesh->geometry;

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


	void Mesh2D::Scale(const math::vec2& scale, const math::vec2& center)
	{
		Material& material = mesh->material;
		Geometry& geometry = mesh->geometry;

		size *= scale;

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

	void Mesh2D::Scale(const math::vec2& scale)
	{
		Scale(scale, pos);
	}

	void Mesh2D::SetScale(const math::vec2& scale)
	{
		Scale(scale / size);
	}

	void Mesh2D::SetScale(const math::vec2& scale, const math::vec2& center)
	{
		Scale(scale / size, center);
	}


	void Mesh2D::Square(float size)
	{
		Rect(size);
	}

	void Mesh2D::Rect(const math::vec2& size)
	{
		Material& material = mesh->material;
		Geometry& geometry = mesh->geometry;

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

	void Mesh2D::Triangle(float a, float b, float c)
	{
		Geometry& geo = mesh->geometry;
		Material& mat = mesh->material;

		const int vertex_size = mat.GetVertexSize();
		const int pos_offset = mat.GetPosOffset();
		const int color_offset = mat.GetColorOffset();

		geo.Alloc(vertex_size * 3, 3);

		float cos = (c * c + b * b - a * a) / (2.f * b * c);
		float h = sqrt(1 - cos * cos) * a;

		*(math::vec2*)(geo.vertices + vertex_size * 0 + pos_offset) = { -c / 2.f, -0.5f * h };
		*(math::vec2*)(geo.vertices + vertex_size * 1 + pos_offset) = { -c / 2.f + a * cos, 0.5f * h };
		*(math::vec2*)(geo.vertices + vertex_size * 2 + pos_offset) = {  c / 2.f, -0.5f * h };

		*(math::vec4*)(geo.vertices + vertex_size * 0 + color_offset) = mat.GetColor();
		*(math::vec4*)(geo.vertices + vertex_size * 1 + color_offset) = mat.GetColor();
		*(math::vec4*)(geo.vertices + vertex_size * 2 + color_offset) = mat.GetColor();

		geo.indices[0] = 0;
		geo.indices[1] = 1;
		geo.indices[2] = 2;
	}

	void Mesh2D::Triangle(const math::vec2& A, const math::vec2& B, const math::vec2& C)
	{
	}


	void Mesh2D::Line(float length, float width, float border_radius, size_t border_sections)
	{
		Material& material = mesh->material;
		Geometry& geometry = mesh->geometry;

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
				rot_vec = { 0.0, -border_radius };
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

	void Mesh2D::Line(const math::vec2& start, const math::vec2& end, float width, float border_radius, size_t border_sections)
	{
		Line(start.distance(end), width, border_radius, border_sections);

		math::vec2 norm = math::normalize(end - start);

		//math::mat2 r = 1;
		//r.x.x = norm.x;
		//r.x.y = norm.y;
		//
		//r.y.x = norm.y;
		//r.y.y = norm.x;

		Move(start);
		Rotate(start, (asin(norm.y) < 0 ? -1 : 1) * acos(norm.x));
	}

	void Mesh2D::Curve(const std::vector<math::vec2>& points, float width, float border_radius, size_t border_sections)
	{
		Material& material = mesh->material;
		Geometry& geometry = mesh->geometry;

		if (points.size() < 2)
		{
			return;
		}

		const int pos_offset = material.GetPosOffset();
		const int color_offset = material.GetColorOffset();
		const math::vec4 color = material.GetColor();
		const int vertex_size = material.GetVertexSize();
		const size_t ind_offset = geometry.ind_offset;

		if (mesh.use_count() == 1)
		{
			geometry.Clear();
		}
		geometry.Alloc(points.size() * 2 * vertex_size, (points.size() - 1) * 2 * 3);

		math::vec2 next_side;

		for (int p = 0; p < points.size() - 1; p++)
		{
			math::vec2 side = next_side;
			next_side = math::normalize(points[p + 1] - points[p]);
			float dir_y = next_side.y;
			next_side.y = -next_side.x;
			next_side.x = dir_y;
			next_side *= width;

			if (!p)
			{
				side = next_side;
			}

			math::vec2 offset = (side + next_side) / 2;

			*(math::vec2*)(geometry.vertices + p * 2 * vertex_size + pos_offset) = points[p] + offset;
			*(math::vec2*)(geometry.vertices + (p * 2 + 1) * vertex_size + pos_offset) = points[p] - offset;

			*(math::vec4*)(geometry.vertices + (p * 2) * vertex_size + color_offset) = color;
			*(math::vec4*)(geometry.vertices + (p * 2 + 1) * vertex_size + color_offset) = color;

			size_t first_ind = ind_offset + p * 2;

			geometry.indices[p * 6 + 0] = first_ind;
			geometry.indices[p * 6 + 1] = first_ind + 1;
			geometry.indices[p * 6 + 2] = first_ind + 2;
			geometry.indices[p * 6 + 3] = first_ind + 1;
			geometry.indices[p * 6 + 4] = first_ind + 3;
			geometry.indices[p * 6 + 5] = first_ind + 2;
		}

		*(math::vec2*)(geometry.vertices + (points.size() - 1) * 2 * vertex_size + pos_offset) = points.back() + next_side;
		*(math::vec2*)(geometry.vertices + ((points.size() - 1) * 2 + 1) * vertex_size + pos_offset) = points.back() - next_side;

		*(math::vec4*)(geometry.vertices + (points.size() - 1) * 2 * vertex_size + color_offset) = color;
		*(math::vec4*)(geometry.vertices + ((points.size() - 1) * 2 + 1) * vertex_size + color_offset) = color;
	}

	void Mesh2D::BezierCurve(const std::vector<math::vec2>& pivot_points, float width, int quality, float border_radius, size_t border_sections)
	{
		if (pivot_points.size() < 2)
		{
			std::cout << "Too little pivot points provided for bezier curve (at least 2 needed)\n";
			return;
		}

		const size_t points_count = pivot_points.size() * quality;

		const math::vec2 start = pivot_points.front();

		std::vector<math::vec2> points;
		points.reserve(points_count);

		std::vector<std::vector<math::vec2>> helpers(pivot_points.size() - 1);

		for (int ppi = 0; ppi < pivot_points.size() - 1; ppi++)
		{
			helpers[ppi].resize(helpers.size() - ppi);
		}

		for (int vi = 0; vi < points_count; vi++)
		{
			const float ratio = float(vi) / points_count;

			for (int hgi = 0; hgi < pivot_points.size() - 1; hgi++)
			{
				for (int helper = 0; helper < helpers.size() - hgi; helper++)
				{
					if (hgi == 0)
					{
						helpers[hgi][helper] = pivot_points[helper] + (pivot_points[helper + 1] - pivot_points[helper]) * ratio;
					}
					else
					{
						helpers[hgi][helper] = helpers[hgi - 1][helper] + (helpers[hgi - 1][helper + 1] - helpers[hgi - 1][helper]) * ratio;
					}
				}
			}

			points.emplace_back(helpers.back().front());
		}

		Curve(points, width, border_radius, border_sections);
	}


	void Mesh2D::Shape(const uint8_t* vertices, size_t vert_size, const uint32_t* indices, size_t ind_count)
	{
		Geometry& geometry = mesh->geometry;

		pos = math::vec2();
		this->size = math::vec2(1);

		geometry.Alloc(vert_size, ind_count);

		memcpy(geometry.vertices, vertices, vert_size);
		memcpy(geometry.indices, indices, ind_count * sizeof(*indices));
	}

	void Mesh2D::Shape(const Geometry& geo)
	{
		Shape(geo.vertices, geo.vertices_size, geo.indices, geo.indices_count);
	}

	bool Mesh2D::IsHovered(const math::mat3x2& view) const
	{
		math::mat3 m(math::vec3(view.x, 0.0), { view.y , 0.0f }, { view.z, 1.0f });
		return IsHovered(m);
	}

	bool Mesh2D::IsHovered(const math::mat3& view) const
	{
		Material& material = mesh->material;
		Geometry& geometry = mesh->geometry;

		IO* io = IO::Get();
		math::vec2 mPos = io->MousePos();
		mPos /= io->WindowSize();
		mPos.x = mPos.x * 2 - 1;
		mPos.y = 1 - mPos.y * 2;

		const size_t vertex_size = material.GetVertexSize();
		const size_t vert_count = geometry.vertices_size / vertex_size;
		const size_t pos_offset = material.GetPosOffset();

		for (int v = 0; v < int(geometry.indices_count) - 2; v += 3)
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
}