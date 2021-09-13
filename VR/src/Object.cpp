#include "pch.h"
#include "VR.h"

namespace VR
{
	Object::Object(const Mesh& mesh)
		:mesh(mesh)
	{
		std::cout << "Object::Object() :( \n";
	}

	Object::Object(const Material& material)
		: mesh(material)
	{
	}

	Object2D::Object2D()
		:Object(Material("C:\\Users\\Professional\\Documents\\VisualStudio\\Fun\\VR\\VR\\res\\Shaders\\2D.shader"))
	{
		mesh.material.PushAttrib<float>(2);
		mesh.material.PushAttrib<float>(4);
	}

	Object2D::Object2D(const Material& material)
		:Object(material)
	{
	}

	Object3D::Object3D()
		: Object(Material("C:\\Users\\Professional\\Documents\\VisualStudio\\Fun\\VR\\VR\\res\\Shaders\\Color.shader"))
	{
		mesh.material.PushAttrib<float>(3);
		mesh.material.PushAttrib<float>(4);

		mesh.material.SetPosOffset(0);
		mesh.material.SetColorOffset(1);
	}
	Object3D::Object3D(const Material& material)
		: Object(material)
	{
	}
}