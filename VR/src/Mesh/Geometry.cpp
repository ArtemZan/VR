#include "pch.h"
#include "VR.h"
#include "Geometry.h"

namespace VR {

	std::vector<gl::AttribLayout> Geometry::layouts;


	Geometry::~Geometry()
	{
		//Clear();
	}

	Geometry::Geometry(const Geometry& geo)
	{
		SetLayout(geo.GetLayout());
	}

	Geometry::Geometry(const gl::AttribLayout& layout) {
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

		props.attribsPos.color = pos;
		props.attribsOffsets.color = GetLayout().GetOffset(pos);

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
			props._3d = true;
		}

		if (attribs[pos].count == 2)
		{
			props._3d = false;
		}

		if (attribs[pos].count == 2 || attribs[pos].count == 3)
		{
			props.attribsPos.pos = pos;
			props.attribsOffsets.pos = GetLayout().GetOffset(pos);
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
			if (!props._3d)
			{
				std::cout << "Warning: set position attribute before setting normal attribute\n";
			}

			props._3d = true;
		}

		if (attribs[pos].count == 2)
		{
			if (props._3d)
			{
				std::cout << "Warning: set position attribute before setting normal attribute\n";
			}
			props._3d = false;
		}

		if (attribs[pos].count == 2 || attribs[pos].count == 3)
		{
			props.attribsPos.normal = pos;
			props.attribsOffsets.normal = GetLayout().GetOffset(pos);
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
	}

	void Geometry::SetColor(const math::vec4& color) {
		const size_t verticesSize = m_data->GetVerticesSize();

		if (verticesSize == 0)
		{
			return;
		}

		const size_t vertex_size = GetVertexSize();
		const size_t vert_count = verticesSize / vertex_size;
		const size_t color_offset = GetColorOffset();

		for (int v = 0; v < vert_count; v++)
		{
			SetColor(v, color);
		}
	}


	Geometry2D::Geometry2D() {
		PushAttrib<float>(2);

		SetPosOffset(0);
	}

	void Geometry2D::Transform(const math::mat3& transform)
	{
		const int vertCount = m_data->GetVerticesSize() / GetVertexSize();

		for (int v = 0; v < vertCount; v++)
		{
			const math::vec2& pos = GetPos(v);
			math::vec3 pos3d(pos, 1);
			pos3d *= transform;
			SetPos(v, pos3d);
		}

		SetPos(GetPos() + transform.z);
		SetScale(GetScale() * math::mat2(transform.x, transform.y).det());
	}

	void Geometry2D::Transform(const math::mat2& transform)
	{
		const int vertCount = m_data->GetVerticesSize() / GetVertexSize();

		for (int v = 0; v < vertCount; v++)
		{
			SetPos(v, GetPos(v) * transform);
		}

		SetScale(GetScale() * transform.det());
	}

	void Geometry2D::CreateShape(const uint8_t* vertices, size_t vert_size, gl::AttribLayout input_layout, const uint32_t* indices, size_t ind_count)
	{

	}


	Rect::Rect(const math::vec2& size)
	{
		SetPos(0);
		SetScale(1);


		const float x = size.x / 2;
		const float y = size.y / 2;


		const size_t vertexSize = GetVertexSize();
		constexpr size_t vertCount = 4;

		m_data->Allocate(vertCount * vertexSize, 6);

		SetPos(0, { -x, -y });
		SetPos(1, {  x, -y });
		SetPos(2, { -x,  y });
		SetPos(3, {  x,  y });

		m_data->SetIndex(0, 0);
		m_data->SetIndex(1, 1);
		m_data->SetIndex(2, 2);
		m_data->SetIndex(3, 2);
		m_data->SetIndex(4, 1);
		m_data->SetIndex(5, 3);
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

	void Geometry3D::Transform(const math::mat4& transform)
	{
		const int vertCount = m_data->GetVerticesSize() / GetVertexSize();

		for (int v = 0; v < vertCount; v++)
		{
			const math::vec3& pos = GetPos(v);
			math::vec4 pos4d(pos, 1);
			pos4d *= transform;

			SetPos(v, pos4d);
		}

		SetPos(GetPos() + math::vec3(transform.w));
		SetScale(GetScale() * math::mat3(transform.x, transform.y, transform.z).det());
	}

	void Geometry3D::Transform(const math::mat3& transform)
	{
		const int vertCount = m_data->GetVerticesSize() / GetVertexSize();

		for (int v = 0; v < vertCount; v++)
		{
			SetPos(v, GetPos(v) * transform);
			SetNormal(v, GetNormal(v) * transform);
		}

		SetScale(GetScale() * transform.det());
	}


	/*void Geometry3D::CreateShape(const uint8_t* vertices, size_t vert_size, gl::AttribLayout input_layout, const uint32_t* indices, size_t ind_count) {

		SetPos(0);
		SetScale(1);


		size_t vert_count = vert_size / (geometry.GetVertexSize() - sizeof(math::vec4));
		size_t vertex_size = geometry.GetVertexSize();

		geometry.m_data->Reallocate(vert_count * vertex_size, ind_count);
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
	}*/


	Geometry3D::Geometry3D() {
		PushAttrib<float>(3);

		SetPosOffset(0);
	}

	GeometryWithNormals::GeometryWithNormals() {
		PushAttrib<float>(3);

		SetNormalOffset(1);
	}


	Box::Box(const math::vec3& size)
	{
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
				SetPos(s * 4 + v, GetPos(s * 4 - 4 + v) * Rz);
				SetNormal(s * 4 + v, GetNormal(s * 4 - 4 + v) * Rz);
			}
		}

		const math::mat3 Ry = math::mat3({ 0, 0, -1 }, { 0, 1, 0 }, { 1, 0, 0 });

		for (int v = 0; v < 4; v++) {
			SetPos(4 * 4 + v, GetPos(3 * 4 + v) * Ry);
			SetNormal(4 * 4 + v, GetNormal(3 * 4 + v) * Ry);
		}

		for (int v = 0; v < 4; v++) {
			SetPos(5 * 4 + v, GetPos(4 + v) * Ry);
			SetNormal(5 * 4 + v, GetNormal(4 + v) * Ry);
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


}