#pragma once
namespace VR
{
	struct Object : public Events
	{
		Mesh mesh;

		Object(const Mesh& mesh);
	};

	struct Object3D : public Object
	{
		math::vec3 pos;
		math::vec3 scale;

		inline void Move(const math::vec3& bias)
		{
			mesh.Move(bias);
			pos += bias;
		}

		inline void MoveTo(const math::vec3& new_pos)
		{
			mesh.Move(new_pos - pos);
			pos = new_pos;
		}

		inline void Scale(const math::vec3& scale)
		{
			mesh.Scale(scale, pos);
			this->scale *= scale;
		}
	};

	struct Object2D : public Object
	{
		math::vec2 pos;
		math::vec2 scale;

		Object2D()
			:Object(Mesh({ "C:\\Users\\Professional\\Documents\\VisualStudio\\Fun\\VR\\VR\\res\\Shaders\\2D.shader", {} }, {})), scale({ 1.0, 1.0 })
		{
			mesh.material.PushAttrib<float>(2);
			mesh.material.PushAttrib<float>(4);
		}

		inline void Move(const math::vec2& bias)
		{
			mesh.Move(bias);
			pos += bias;
		}

		inline void MoveTo(const math::vec2& new_pos)
		{
			mesh.Move(new_pos - pos);
			pos = new_pos;
		}

		inline void Scale(const math::vec2& scale)
		{
			mesh.Scale(scale, pos);
			this->scale *= scale;
		}
	};
}
