#include "pch.h"
#include "VR.h"
#include "Geometry.h"

namespace VR {

	std::vector<gl::AttribLayout> Geometry::layouts;


	Geometry::~Geometry()
	{
		//Clear();
	}

	Geometry& Geometry::operator=(const Geometry& geometry)
	{
		m_layoutId = geometry.m_layoutId;
		m_props = geometry.m_props;
		m_data = std::unique_ptr<GeometryData>(new DetachedGeometryData(geometry.m_data));

		return *this;
	}

	Geometry::Geometry(const Geometry& geo)
	{
		*this = geo;
	}

	Geometry::Geometry(const gl::AttribLayout& layout)
	{
		m_data = std::unique_ptr<GeometryData>(new DetachedGeometryData());
		SetLayout(layout);
	}

#define AttribSetterInit\
	const std::vector<gl::VertexAttrib>& attribs = GetLayout().GetAttributes(); \
	if (attribs.size() <= pos)																			 \
	{																										 \
		std::cout << "Attribute position out of range\n";													 \
		return false;																						 \
	}

	bool Geometry::SetColorOffset(size_t pos)
	{
		AttribSetterInit;

		if (attribs[pos].count != 4 || attribs[pos].type != GL_FLOAT)
		{
			std::cout << "Attribute at given offset cannot be color\n";
			return false;
		}

		m_props.attribsPos.color = pos;
		m_props.attribsOffsets.color = GetLayout().GetOffset(pos);

		return true;
	}

	bool Geometry::SetPosOffset(size_t pos)
	{
		AttribSetterInit

			if (attribs[pos].type != GL_FLOAT)
			{
				std::cout << "Attribute at given offset cannot be position\n";
				return false;
			}

		if (attribs[pos].count == 3)
		{
			m_props._3d = true;
		}

		if (attribs[pos].count == 2)
		{
			m_props._3d = false;
		}

		if (attribs[pos].count == 2 || attribs[pos].count == 3)
		{
			m_props.attribsPos.pos = pos;
			m_props.attribsOffsets.pos = GetLayout().GetOffset(pos);
			return true;
		}

		std::cout << "Attribute at given position cannot be position (invalid dimension)\n";
		return false;
	}

	bool Geometry::SetNormalOffset(size_t pos)
	{
		AttribSetterInit;

		if (attribs[pos].type != GL_FLOAT)
		{
			std::cout << "Attribute at given position cannot be normal\n";
			return false;
		}

		if (attribs[pos].count == 3)
		{
			if (!m_props._3d)
			{
				std::cout << "Warning: set position attribute before setting normal attribute\n";
			}

			m_props._3d = true;
		}

		if (attribs[pos].count == 2)
		{
			if (m_props._3d)
			{
				std::cout << "Warning: set position attribute before setting normal attribute\n";
			}
			m_props._3d = false;
		}
		
		if (attribs[pos].count == 2 || attribs[pos].count == 3)
		{
			m_props.attribsPos.normal = pos;
			m_props.attribsOffsets.normal = GetLayout().GetOffset(pos);
			return true;
		}

		std::cout << "Attribute at given position cannot be normal (invalid dimension)\n";
		return false;
	}

	int Geometry::FindLayout(const gl::AttribLayout& layout)
	{
		int id = 0;
		for (auto& _layout : layouts)
		{
			if (_layout.GetAttributes().size() == layout.GetAttributes().size())
			{
				auto attribs = layout.GetAttributes();
				auto _attribs = _layout.GetAttributes();

				bool same = true;

				for (int i = 0; i < attribs.size(); i++)
				{
					if (attribs[i].type != _attribs[i].type)
					{
						same = false;
					}
				}

				if (same)
				{
					return id;
				}
			}

			id++;
		}

		return -1;
	}

	void Geometry::SetLayout(const gl::AttribLayout& layout)
	{
		m_layoutId = FindLayout(layout);

		if (m_layoutId == -1)
		{
			layouts.push_back(layout);
			m_layoutId = layouts.size() - 1;
		}

		m_props.vertexSize = layout.GetStride();
	}

	void Geometry::SetColor(const math::vec4& color) {
		const size_t verticesSize = m_data->GetVerticesSize();

		if (verticesSize == 0)
		{
			return;
		}

		const size_t vertexSize = GetVertexSize();
		const size_t vertCount = verticesSize / vertexSize;
		const size_t colorOffset = GetColorOffset();

		for (int v = 0; v < vertCount; v++)
		{
			SetColor(v, color);
		}
	}


	Geometry2D::Geometry2D() {
		PushAttrib<float>(2);

		SetPosOffset(0);
	}

	Geometry2D::Geometry2D(const Geometry2D& geometry)
	{
		*this = geometry;
	}

	Geometry2D& Geometry2D::operator=(const Geometry2D& geometry)
	{
		*(Geometry*)(this) = geometry;

		m_pos = geometry.m_pos;
		m_scale = geometry.m_scale;

		return *this;
	}

	void Geometry2D::SetPos(const math::vec2& new_pos)
	{
		const int vertCount = m_data->GetVerticesSize() / GetVertexSize();
		const math::vec2 dPos = new_pos - m_pos;

		for (int v = 0; v < vertCount; v++)
		{
			SetPos(v, GetPos(v) + dPos);
		}

		m_pos = new_pos;
	}

	void Geometry2D::SetScale(const math::vec2& new_scale)
	{
		const int vertCount = m_data->GetVerticesSize() / GetVertexSize();
		const math::vec2 dScale = new_scale / m_scale;

		for (int v = 0; v < vertCount; v++)
		{
			SetPos(v, GetPos(v) * dScale);
		}

		m_scale = new_scale;
	}

	void Geometry2D::Rotate(const math::vec2& center, float angle)
	{
		const int vertCount = m_data->GetVerticesSize() / GetVertexSize();

		const math::mat2 R = math::rotate(angle);

		for (int v = 0; v < vertCount; v++)
		{
			SetPos(v, R * (GetPos(v) - center) + center);
		}
	}

	void Geometry2D::Transform(const math::mat3f& transform)
	{
		const int vertCount = m_data->GetVerticesSize() / GetVertexSize();

		for (int v = 0; v < vertCount; v++)
		{
			const math::vec2& pos = GetPos(v);
			math::vec3 pos3d(pos, 1);
			pos3d *= transform;
			SetPos(v, pos3d);
		}

		m_pos = GetPos() + transform.z;
		m_scale = GetScale() * math::mat2(transform.x, transform.y).det();
	}

	void Geometry2D::Transform(const math::mat2f& transform)
	{
		const int vertCount = m_data->GetVerticesSize() / GetVertexSize();

		for (int v = 0; v < vertCount; v++)
		{
			SetPos(v, transform * GetPos(v));
		}

		m_scale = GetScale() * transform.det();
	}

	void Geometry2D::CreateShape(const uint8_t* vertices, size_t vert_size, gl::AttribLayout input_layout, const uint32_t* indices, size_t ind_count)
	{

	}

	void Geometry2D::CreateRect(const math::vec2& size)
	{
		SetPos(0);
		SetScale(1);


		const float x = size.x / 2;
		const float y = size.y / 2;


		const size_t vertexSize = GetVertexSize();
		constexpr size_t vertCount = 4;

		m_data->Reallocate(vertCount * vertexSize, 6);

		SetPos(0, { -x, -y });
		SetPos(1, { x, -y });
		SetPos(2, { -x,  y });
		SetPos(3, { x,  y });

		m_data->SetIndex(0, 0);
		m_data->SetIndex(1, 1);
		m_data->SetIndex(2, 2);
		m_data->SetIndex(3, 2);
		m_data->SetIndex(4, 1);
		m_data->SetIndex(5, 3);
	}

	void Geometry2D::CreateLine(float length, float width, float border_radius, size_t border_sections)
	{
		const math::Tvec2 start(0);
		const math::vec2 end(length, 0);

		m_pos = math::vec2();
		m_scale = math::vec2(1);

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

		const int posOffset = GetPosOffset();
		const int vertexSize = GetVertexSize();

		m_data->Allocate(vpc * 4 * vertexSize, 6 + border_sections * 4 * 3);


		math::Tvec2 rotationCenter;
		math::Tvec2 rotVec;

		const float rotationCenterOffset = width - border_radius;

		for (int corner = 0; corner < 4; corner++)
		{
			switch (corner)
			{
			case 0:
				rotationCenter = start - math::vec2(rotationCenterOffset);
				rotVec = { 0.0, -border_radius };
				break;
			case 1:
				rotationCenter = start + math::vec2(-rotationCenterOffset, rotationCenterOffset);
				rotVec = { -border_radius, 0.0 };
				break;
			case 2:
				rotationCenter = end + math::vec2(rotationCenterOffset);
				rotVec = { 0.0, border_radius };
				break;
			case 3:
				rotationCenter = end + math::vec2(rotationCenterOffset, -rotationCenterOffset);
				rotVec = { border_radius, 0.0 };
				break;
			}

			//All triangles in this half of the line include this point
			const int pivotInd = (corner / 2 + 1) * 2 * vpc - 1;

			for (int v = 0; v < vpc; v++)
			{
				SetPos(corner * vpc + v, rotationCenter + rotVec);

				m_data->SetIndex((corner * border_sections + v) * 3, pivotInd);
				m_data->SetIndex((corner * border_sections + v) * 3 + 1, v + corner * vpc);
				m_data->SetIndex((corner * border_sections + v) * 3 + 2, v + corner * vpc + 1);

				rotVec *= math::rotate(-math::PI / 2 / border_sections);
			}

			if (corner % 2)
			{
				m_data->SetIndex(((corner + 1) * border_sections - 1) * 3, pivotInd);
				m_data->SetIndex(((corner + 1) * border_sections - 1) * 3 + 1, corner * vpc - 1);
				m_data->SetIndex(((corner + 1) * border_sections - 1) * 3 + 2, corner * vpc);
			}

		}

		const int rectInd = border_sections * 4 * 3;

		m_data->SetIndex(rectInd + 0, 0);
		m_data->SetIndex(rectInd + 1, vpc * 2 - 1);
		m_data->SetIndex(rectInd + 2, vpc * 2);
		m_data->SetIndex(rectInd + 3, vpc * 2);
		m_data->SetIndex(rectInd + 4, vpc * 4 - 1);
		m_data->SetIndex(rectInd + 5, 0);
	}

	void Geometry2D::CreateLine(const math::vec2& start, const math::vec2& end, float width, float border_radius, size_t border_sections)
	{
		CreateLine(start.distance(end), width, border_radius, border_sections);

		math::vec2 norm = math::normalize(end - start);

		SetPos(start);
		Rotate(start, (asin(norm.y) < 0 ? -1 : 1) * acos(norm.x));
	}



	void Geometry3D::ShadeSmooth(float distance_threshold)
	{
		const size_t normalOffset = GetNormalOffset();
		const size_t posOffset = GetPosOffset();
		const size_t vertexSize = GetVertexSize();
		const size_t verticesSize = m_data->GetVerticesSize();
		const size_t vertCount = verticesSize / vertexSize;

		if (normalOffset == -1)
			return;

		struct VecComparator
		{
			float m_distanceTreshold;

			bool operator()(const math::vec3& v1, const math::vec3& v2) const
			{
				double dx = v1.x - v2.x;
				double dy = v1.y - v2.y;
				double dz = v1.z - v2.z;

				if (dx < -m_distanceTreshold || dx > m_distanceTreshold) {
					return dx < 0;
				}

				if (dy < -m_distanceTreshold || dy > m_distanceTreshold) {
					return dy < 0;
				}

				if (dz < -m_distanceTreshold || dz > m_distanceTreshold) {
					return dz < 0;
				}

				return false;
			}
		};


		std::map<math::vec3, math::vec3, VecComparator> normals(VecComparator({ distance_threshold }));

		for (int v = 0; v < vertCount; v++)
		{
			normals[GetPos(v)] += GetNormal(v);
		}

		for (auto& [pos, normal] : normals)
		{
			normal.normalize();
		}

		for (int v = 0; v < vertCount; v++)
		{
			SetNormal(v, normals[GetPos(v)]);
		}
	}

	void Geometry3D::Transform(const math::mat4f& transform)
	{
		const int vertCount = m_data->GetVerticesSize() / GetVertexSize();

		for (int v = 0; v < vertCount; v++)
		{
			const math::vec3& pos = GetPos(v);
			math::vec4 pos4d(pos, 1);
			pos4d *= transform;

			SetPos(v, pos4d);
		}

		m_pos = GetPos() + math::vec3(transform.w);
		m_scale = GetScale() * math::mat3f(transform.x, transform.y, transform.z).det();
	}

	void Geometry3D::Transform(const math::mat3f& transform)
	{
		const int vertCount = m_data->GetVerticesSize() / GetVertexSize();

		for (int v = 0; v < vertCount; v++)
		{
			SetPos(v, transform * GetPos(v));
			SetNormal(v, transform * GetNormal(v));
		}

		m_scale = GetScale() * transform.det();
	}


	/*void Geometry3D::CreateShape(const uint8_t* vertices, size_t vert_size, gl::AttribLayout input_layout, const uint32_t* indices, size_t ind_count) {

		SetPos(0);
		SetScale(1);


		size_t vert_count = vert_size / (geometry.GetVertexSize() - sizeof(math::Tvec4));
		size_t vertex_size = geometry.GetVertexSize();

		geometry.m_data->Reallocate(vert_count * vertex_size, ind_count);
		uint8_t* vert = geometry.vertices;

		const uint8_t* vertSrc = vertices;

		for (int i = 0; i < vert_count; i++)
		{
			memcpy(vert, vertSrc, material.GetColorOffset());
			*(math::Tvec4*)(vert + material.GetColorOffset()) = material.GetColor();
			memcpy(vert + material.GetColorOffset() + sizeof(math::Tvec4), vertSrc + material.GetColorOffset(), vertex_size - material.GetColorOffset() - sizeof(math::Tvec4));

			vert += vertex_size;
			vertSrc += vertex_size - sizeof(math::Tvec4);
		}

		for (int i = 0; i < ind_count; i++)
		{
			geometry.indices[i] = indices[i];
		}
	}*/


	Geometry3D::Geometry3D() {
		PushAttrib<float>(3);

		SetPosOffset(0);
	}

	Geometry3D& Geometry3D::operator=(const Geometry3D& geometry)
	{
		*(Geometry*)(this) = geometry;

		m_pos = geometry.m_pos;
		m_scale = geometry.m_scale;

		return *this;
	}

	void Geometry3D::CreateBox(const math::vec3& size) {
		SetPos(0);
		SetScale(1);

		const float x = size.x / 2;
		const float y = size.y / 2;
		const float z = size.z / 2;


		const size_t vertexSize = GetVertexSize();
		constexpr size_t vertCount = 24;

		m_data->Allocate(vertexSize * vertCount, 36);

		SetPos(0, math::vec3(-x, -y, -z));
		SetNormal(0, math::vec3(0, 0, -1));

		SetPos(1, math::vec3(x, -y, -z));
		SetNormal(1, math::vec3(0, 0, -1));

		SetPos(2, math::vec3(-x, y, -z));
		SetNormal(2, math::vec3(0, 0, -1));

		SetPos(3, math::vec3(x, y, -z));
		SetNormal(3, math::vec3(0, 0, -1));

		const math::mat3 Rz = math::mat3({ 0, 1, 0 }, { -1, 0, 0 }, { 0, 0, 1 });

		for (int s = 1; s < 4; s++)
		{
			for (int v = 0; v < 4; v++) {
				SetPos(s * 4 + v, Rz * GetPos(s * 4 - 4 + v));
				SetNormal(s * 4 + v, Rz * GetNormal(s * 4 - 4 + v));
			}
		}

		const math::mat3 Ry = math::mat3({ 0, 0, -1 }, { 0, 1, 0 }, { 1, 0, 0 });

		for (int v = 0; v < 4; v++) {
			SetPos(4 * 4 + v, Ry * GetPos(3 * 4 + v));
			SetNormal(4 * 4 + v, Ry * GetNormal(3 * 4 + v));
		}

		for (int v = 0; v < 4; v++) {
			SetPos(5 * 4 + v, Ry * GetPos(4 + v));
			SetNormal(5 * 4 + v, Ry * GetNormal(4 + v));
		}

		for (int i = 0; i < 36; i += 6)
		{
			m_data->SetIndex(i, i);
			m_data->SetIndex(i + 1, i + 1);
			m_data->SetIndex(i + 2, i + 2);
			m_data->SetIndex(i + 3, i + 2);
			m_data->SetIndex(i + 4, i + 1);
			m_data->SetIndex(i + 5, i + 3);
		}
	}

	void Geometry3D::SetPos(const math::vec3& new_pos)
	{
		const int vertCount = m_data->GetVerticesSize() / GetVertexSize();
		const math::vec3 dPos = new_pos - m_pos;

		for (int v = 0; v < vertCount; v++)
		{
			SetPos(v, GetPos(v) + dPos);
		}

		m_pos = new_pos;
	}

	void Geometry3D::SetScale(const math::vec3& new_scale)
	{
		const int vertCount = m_data->GetVerticesSize() / GetVertexSize();
		const math::vec3 dScale = new_scale / m_scale;

		for (int v = 0; v < vertCount; v++)
		{
			SetPos(v, GetPos(v) * dScale);
		}

		m_scale = new_scale;
	}

	GeometryWithNormals::GeometryWithNormals() {
		PushAttrib<float>(3);

		SetNormalOffset(1);
	}


	Geometry2DColor::Geometry2DColor()
	{
		PushAttrib<float>(4);

		SetColorOffset(1);
	}



	/*void Mesh2DContainer::Triangle(float a, float b, float c)
	{
		const int vertex_size = mat.GetVertexSize();
		const int pos_offset = mat.GetPosOffset();
		const int color_offset = mat.GetColorOffset();

		geo.Alloc(vertex_size * 3, 3);

		float cos = (c * c + b * b - a * a) / (2.f * b * c);
		float h = sqrt(1 - cos * cos) * a;

		*(math::Tvec2*)(geo.vertices + vertex_size * 0 + pos_offset) = { -c / 2.f, -0.5f * h };
		*(math::Tvec2*)(geo.vertices + vertex_size * 1 + pos_offset) = { -c / 2.f + a * cos, 0.5f * h };
		*(math::Tvec2*)(geo.vertices + vertex_size * 2 + pos_offset) = {  c / 2.f, -0.5f * h };

		*(math::Tvec4*)(geo.vertices + vertex_size * 0 + color_offset) = mat.GetColor();
		*(math::Tvec4*)(geo.vertices + vertex_size * 1 + color_offset) = mat.GetColor();
		*(math::Tvec4*)(geo.vertices + vertex_size * 2 + color_offset) = mat.GetColor();

		geo.indices[0] = 0;
		geo.indices[1] = 1;
		geo.indices[2] = 2;
	}*/


	/* 


	void Mesh2DContainer::Curve(const std::vector<math::Tvec2>& points, float width, float border_radius, size_t border_sections)
	{
		Material& material = mesh->material;
		Geometry& geometry = mesh->geometry;

		if (points.size() < 2)
		{
			return;
		}

		const int pos_offset = material.GetPosOffset();
		const int color_offset = material.GetColorOffset();
		const math::Tvec4 color = material.GetColor();
		const int vertex_size = material.GetVertexSize();
		const size_t ind_offset = geometry.ind_offset;

		if (mesh.use_count() == 1)
		{
			geometry.Clear();
		}
		geometry.Alloc(points.size() * 2 * vertex_size, (points.size() - 1) * 2 * 3);

		math::Tvec2 next_side;

		for (int p = 0; p < points.size() - 1; p++)
		{
			math::Tvec2 side = next_side;
			next_side = math::normalize(points[p + 1] - points[p]);
			float dir_y = next_side.y;
			next_side.y = -next_side.x;
			next_side.x = dir_y;
			next_side *= width;

			if (!p)
			{
				side = next_side;
			}

			math::Tvec2 offset = (side + next_side) / 2;

			*(math::Tvec2*)(geometry.vertices + p * 2 * vertex_size + pos_offset) = points[p] + offset;
			*(math::Tvec2*)(geometry.vertices + (p * 2 + 1) * vertex_size + pos_offset) = points[p] - offset;

			*(math::Tvec4*)(geometry.vertices + (p * 2) * vertex_size + color_offset) = color;
			*(math::Tvec4*)(geometry.vertices + (p * 2 + 1) * vertex_size + color_offset) = color;

			size_t first_ind = ind_offset + p * 2;

			geometry.indices[p * 6 + 0] = first_ind;
			geometry.indices[p * 6 + 1] = first_ind + 1;
			geometry.indices[p * 6 + 2] = first_ind + 2;
			geometry.indices[p * 6 + 3] = first_ind + 1;
			geometry.indices[p * 6 + 4] = first_ind + 3;
			geometry.indices[p * 6 + 5] = first_ind + 2;
		}

		*(math::Tvec2*)(geometry.vertices + (points.size() - 1) * 2 * vertex_size + pos_offset) = points.back() + next_side;
		*(math::Tvec2*)(geometry.vertices + ((points.size() - 1) * 2 + 1) * vertex_size + pos_offset) = points.back() - next_side;

		*(math::Tvec4*)(geometry.vertices + (points.size() - 1) * 2 * vertex_size + color_offset) = color;
		*(math::Tvec4*)(geometry.vertices + ((points.size() - 1) * 2 + 1) * vertex_size + color_offset) = color;
	}

	void Mesh2DContainer::BezierCurve(const std::vector<math::Tvec2>& pivot_points, float width, int quality, float border_radius, size_t border_sections)
	{
		if (pivot_points.size() < 2)
		{
			std::cout << "Too little pivot points provided for bezier curve (at least 2 needed)\n";
			return;
		}

		const size_t points_count = pivot_points.size() * quality;

		const math::Tvec2 start = pivot_points.front();

		std::vector<math::Tvec2> points;
		points.reserve(points_count);

		std::vector<std::vector<math::Tvec2>> helpers(pivot_points.size() - 1);

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


	void Mesh2DContainer::Shape(const uint8_t* vertices, size_t vert_size, const uint32_t* indices, size_t ind_count)
	{
		Geometry& geometry = mesh->geometry;

		m_pos = math::Tvec2();
		m_scale = math::Tvec2(1);

		geometry.Alloc(vert_size, ind_count);

		memcpy(geometry.vertices, vertices, vert_size);
		memcpy(geometry.indices, indices, ind_count * sizeof(*indices));
	}

	void Mesh2DContainer::Shape(const Geometry& geo)
	{
		Shape(geo.vertices, geo.vertices_size, geo.indices, geo.indices_count);
	} */

}