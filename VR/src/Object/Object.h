#pragma once

namespace VR {


	class Object
	{
	};

	struct Object2D : public Object {
		inline virtual const math::vec2& GetPos() const = 0;

		inline virtual void SetPos(const math::vec2& new_pos) = 0;

		inline virtual const math::vec2& GetScale() const = 0;

		inline virtual void SetScale(const math::vec2& new_scale) = 0;
	};

	struct Object3D : public Object {
		inline virtual const math::vec3& GetPos() const = 0;

		inline virtual void SetPos(const math::vec3& new_pos) = 0;

		inline virtual const math::vec3& GetScale() const = 0;

		inline virtual void SetScale(const math::vec3& new_scale) = 0;
	};
}