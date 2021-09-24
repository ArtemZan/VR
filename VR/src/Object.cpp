#include "pch.h"
#include "VR.h"

namespace VR
{
	Object::Object(const Mesh& mesh)
		:mesh(mesh)
	{
		AddHandler(this);
	}

	Object::Object(const Material& material)
		: mesh(material)
	{
		AddHandler(this);
	}

	Object::Object(const Object& object)
		:mesh(object.mesh)
	{
		AddHandler(this);
	}

	Object::~Object()
	{
		RemoveHandler(this);
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


	Object2D::Object2D()
		:Object(Material2D())
	{
		
	}

	Object2D::Object2D(const Material& material)
		:Object(material)
	{
	}

	void Object2D::Line(const math::vec2& start, const math::vec2& end, float width, float border_radius, size_t border_sections)
	{
		mesh.Line(start.distance(end), width, border_radius, border_sections);

		math::vec2 norm = math::normalize(end - start);

		math::mat2 r = 1;

		mesh.Rotate(start, (asin(norm.y) < 0 ? -1 : 1) * acos(norm.x));
	}


}