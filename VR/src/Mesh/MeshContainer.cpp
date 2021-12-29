#include "pch.h"
#include "VR.h"

namespace VR
{

	MeshContainer::MeshContainer(const Material& material)
		:m_material(material)
	{

	}


	MeshContainer::~MeshContainer()
	{
		
	}


	void MeshContainer::SetColor(const math::vec4& color)
	{
		m_material.m_color = color;
		GetGeometry().SetColor(color);
	}

	/*math::vec4& MeshContainer::GetColor(size_t vertex) const
	{
		return mesh->geometry->GetColor(vertex);
	}*/



	Mesh3DContainer::Mesh3DContainer(const Material& material)
		:MeshContainer(material)
	{

	}

	Mesh3DContainer::Mesh3DContainer(const Mesh3DContainer& mesh)
		:MeshContainer(mesh.m_material)
	{
		m_geometry = mesh.GetGeometry();
	}

	void Mesh3DContainer::Move(const math::vec3& bias)
	{
		math::Tmat4 m = 1;
		m.w = { bias, 1 };

		Transform(m);
	}

	void Mesh3DContainer::MoveTo(const math::vec3& new_pos)
	{
		Move(new_pos - GetPos());
	}


	void Mesh3DContainer::Rotate(const math::vec3& axis, const math::vec3& center, float angle)
	{
		math::Tmat4 T(1);

		T.w = math::vec4(-center, 1);

		math::mat3 R = math::rotate(axis, angle);

		T *= math::mat4({ R.x, 0.f }, { R.y, 0.f }, { R.z, 0.f }, { 0, 0, 0, 1 });

		T *= math::mat4(math::vec4(1, 0, 0, 0), math::vec4(0, 1, 0, 0), math::vec4(0, 0, 1, 0), math::vec4(center, 1));

		Transform(T);


		/*int vert_size = material.GetVertexSize();
		int vert_count = geometry.vertices_size / vert_size;

		for (int i = 0; i < vert_count; i++)
		{
			math::Tvec3& v = *(math::Tvec3*)(geometry.vertices + i * vert_size + material.GetPosOffset());
			v -= center;
			v *= m;
			v += center;
			if (material.HasNormals())
			{
				*(math::Tvec3*)(geometry.vertices + i * vert_size + material.GetNormalOffset()) *= m;
			}
		}*/
	}


	void Mesh3DContainer::Scale(const math::vec3& scale, const math::vec3& center)
	{
		math::Tmat4 T(1);

		T.w = math::vec4(-center, 1);

		T *= math::mat4({ scale.x, 0.f, 0.f, 0.f }, { 0.f, scale.y, 0.f, 0.f }, { 0.f, 0.f, scale.z, 0.f }, { 0.f, 0.f, 0.f, 1.f });

		T *= math::mat4(math::vec4(1, 0, 0, 0), math::vec4(0, 1, 0, 0), math::vec4(0, 0, 1, 0), math::vec4(center, 1));

		Transform(T);

		/*int vert_size = material.GetVertexSize();
		int vert_count = geometry.vertices_size / vert_size;
		for (int i = 0; i < vert_count; i++)
		{
			math::Tvec3& pos = *(math::Tvec3*)(geometry.vertices + i * vert_size);
			pos -= center;

			pos *= scale;

			pos += center;
		}*/
	}

	void Mesh3DContainer::Scale(const math::vec3& scale)
	{
		Scale(scale, GetPos());
	}

	void Mesh3DContainer::SetScale(const math::vec3& scale)
	{
		Scale(scale / GetScale());
	}

	void Mesh3DContainer::SetScale(const math::vec3& scale, const math::vec3& center)
	{
		Scale(scale / GetScale() , center);
	}


	void Mesh3DContainer::Cube(float size)
	{
		Box(size);
	}

	void Mesh3DContainer::Box(const math::vec3& size)
	{
		
	}

	/*void Mesh3DContainer::Shape(const Geometry& geo)
	{
		Shape(geo.vertices, geo.vertices_size, geo.indices, geo.indices_count);
	}*/


	bool Mesh3DContainer::IsHovered(const math::mat4& mvp) const
	{
		IO* io = IO::Get();
		math::vec2 mPos = io->MousePos();
		mPos /= io->WindowSize();
		mPos.x = mPos.x * 2 - 1;
		mPos.y = 1 - mPos.y * 2;

		const size_t vertex_size = m_geometry.GetVertexSize();
		const size_t vert_count = m_geometry.m_data->GetVerticesSize() / vertex_size;


		for (int i = 0; i < m_geometry.m_data->GetIndicesCount() - 2; i += 3)
		{
			const math::vec3 p1 = m_geometry.GetPos(m_geometry.m_data->GetIndex(i));
			const math::vec3 p2 = m_geometry.GetPos(m_geometry.m_data->GetIndex(i + 1));
			const math::vec3 p3 = m_geometry.GetPos(m_geometry.m_data->GetIndex(i + 2));

			const math::vec4 p1p = mvp * math::vec4(p1.x, p1.y, p1.z, 1);
			const math::vec4 p2p = mvp * math::vec4(p2.x, p2.y, p2.z, 1);
			const math::vec4 p3p = mvp * math::vec4(p3.x, p3.y, p3.z, 1);

			const math::vec2 p1d = math::vec2(p1p.x, p1p.y) / p1p.w;
			const math::vec2 p2d = math::vec2(p2p.x, p2p.y) / p2p.w;
			const math::vec2 p3d = math::vec2(p3p.x, p3p.y) / p3p.w;

			if (math::IsInside(p1d, p2d, p3d, mPos))
			{
				return true;
			}
		}

		return false;
	}

	void Mesh3DContainer::CreateNormals()
	{
		const size_t normal_offset = m_geometry.GetNormalOffset();
		const size_t pos_offset = m_geometry.GetPosOffset();
		const size_t vertex_size = m_geometry.GetVertexSize();
		const size_t indCount = m_geometry.m_data->GetVerticesSize();

		if (normal_offset == -1)
			return;


		for (int i = 0; i + 2 < indCount; i += 3)
		{
			int i1 = m_geometry.m_data->GetIndex(i);
			int i2 = m_geometry.m_data->GetIndex(i + 1);
			int i3 = m_geometry.m_data->GetIndex(i + 2);

			math::vec3 v1 = m_geometry.GetPos(i1);
			math::vec3 v2 = m_geometry.GetPos(i2);
			math::vec3 v3 = m_geometry.GetPos(i3);

			math::vec3 norm = math::cross(v2 - v1, v3 - v1);

			norm.normalize();

			m_geometry.SetNormal(i1, norm);
			m_geometry.SetNormal(i2, norm);
			m_geometry.SetNormal(i3, norm);
		}
	}

	void Mesh3DContainer::ShadeSmooth(float distance_threshold)
	{
		m_geometry.ShadeSmooth(distance_threshold);
	}


	Mesh2DContainer::Mesh2DContainer()
		:MeshContainer(Material2DColor()), m_geometry(Geometry2DColor())
	{
		
	}

	Mesh2DContainer::Mesh2DContainer(const Mesh2DContainer& mesh)
		:MeshContainer(mesh.m_material)
	{
		m_geometry = mesh.m_geometry;
	}

	Mesh2DContainer::Mesh2DContainer(const Geometry2D& geometry)
		:MeshContainer(Material2DColor()), m_geometry(geometry)
	{
	}

	Mesh2DContainer::Mesh2DContainer(const Material2D& material)
		:MeshContainer(material), m_geometry(Geometry2DColor())
	{
	}

	Mesh2DContainer::Mesh2DContainer(const Material2D& material, const Geometry2D& geometry)
		:MeshContainer(material), m_geometry(geometry)
	{
	}

	void Mesh2DContainer::Move(const math::vec2& bias)
	{
		math::mat3f m = 1;
		m.z = { bias, 1 };
		
		Transform(m);
	}

	void Mesh2DContainer::MoveTo(const math::vec2& new_pos)
	{
		Move(new_pos - GetPos());
	}


	void Mesh2DContainer::Rotate(const math::vec2& center, float angle)
	{
		m_geometry.Rotate(center, angle);
	}


	void Mesh2DContainer::Scale(const math::vec2& scale, const math::vec2& center)
	{
		
	}

	void Mesh2DContainer::Scale(const math::vec2& scale)
	{
		Scale(scale, GetPos());
	}

	void Mesh2DContainer::SetScale(const math::vec2& scale)
	{
		Scale(scale / GetScale());
	}

	void Mesh2DContainer::SetScale(const math::vec2& scale, const math::vec2& center)
	{
		Scale(scale / GetScale(), center);
	}

	

	bool Mesh2DContainer::IsHovered(const math::mat3x2& view) const
	{
		math::mat3 m(math::vec3(view.x, 0.0), { view.y , 0.0f }, { view.z, 1.0f });
		return IsHovered(m);
	}

	bool Mesh2DContainer::IsHovered(const math::mat3& view) const
	{
		IO* io = IO::Get();
		math::vec2 mPos = io->MousePos();
		mPos /= io->WindowSize();
		mPos.x = mPos.x * 2 - 1;
		mPos.y = 1 - mPos.y * 2;

		const Geometry2D& geo = GetGeometry();

		const size_t vertexSize = geo.GetVertexSize();
		const size_t vertCount = geo.m_data->GetVerticesSize() / vertexSize;
		const size_t posOffset = geo.GetPosOffset();
		const size_t indCount = GetGeometry().m_data->GetIndicesCount();

		if (indCount < 3) {
			return false;
		}

		for (int i = 0; i < indCount - 2; i += 3)
		{
			const math::vec2 p1 = geo.GetPos(geo.m_data->GetIndex(i));
			const math::vec2 p2 = geo.GetPos(geo.m_data->GetIndex(i + 1));
			const math::vec2 p3 = geo.GetPos(geo.m_data->GetIndex(i + 2));

			const math::vec3 p1t = view * math::vec3(p1.x, p1.y, 1);
			const math::vec3 p2t = view * math::vec3(p2.x, p2.y, 1);
			const math::vec3 p3t = view * math::vec3(p3.x, p3.y, 1);

			if (math::IsInside({ p1t.x, p1t.y }, { p2t.x, p2t.y }, { p3t.x, p3t.y }, mPos))
			{
				return true;
			}
		}

		return false;
	}
}