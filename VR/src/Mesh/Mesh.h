#pragma once

namespace VR
{
	struct Mesh
	{
		Mesh(const Material& material, const Geometry& geometry);

		void Move(const math::vec3& bias);
		void Move(const math::vec2& bias);
		void Rotate(const math::vec3& axis, const math::vec3& center, float angle);
		void Rotate(const math::vec2& center, float angle);
		void Scale(const math::vec3& scale, const math::vec3& center);
		void Scale(const math::vec2& scale, const math::vec2& center);

		Material material;
		Geometry geometry;

	};
}
