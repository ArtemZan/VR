#include "pch.h"
#include "VR.h"

namespace VR {

	Mesh::Mesh()
	{

	}



	Mesh2D::Mesh2D()
	{
		m_mesh = std::shared_ptr<Mesh2DContainer>(new Mesh2DContainer());
	}

	Mesh2D::Mesh2D(const Mesh2D& mesh)
	{
		m_mesh = mesh.m_mesh;
	}

	Mesh2D::Mesh2D(const Mesh2DContainer& mesh)
	{
		m_mesh = std::make_shared<Mesh2DContainer>(mesh);
	}

	Mesh2D::Mesh2D(const Material2D& material, const Geometry2D& geometry)
	{
		m_mesh = std::make_shared<Mesh2DContainer>(material, geometry);
	}

	Mesh2D::Mesh2D(const Geometry2D& geometry)
	{
	}



	Mesh3D::Mesh3D()
	{
		m_mesh = std::shared_ptr<Mesh3DContainer>(new Mesh3DContainer(Material3DColor())); // Color shader is default
	}

	Mesh3D::Mesh3D(const Mesh3D& mesh)
	{
		m_mesh = mesh.m_mesh;
	}

	Mesh3D::Mesh3D(const Mesh3DContainer& mesh)
	{
		m_mesh = std::make_shared<Mesh3DContainer>(mesh);
	}
}