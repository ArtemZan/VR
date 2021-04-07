#pragma once

namespace VR
{
	struct Camera
	{
		Camera(const math::vec3& pos = math::vec3(), const math::vec3& direction = math::vec3(0.0, 0.0, 1.0));

		void SetPosition(math::vec3 pos);
		void Move(math::vec3 dPos);
		void SetRotation(math::vec3 rot);
		void Rotate(math::vec3 axis, float angle);

		math::vec3 pos;
		math::vec3 dir;
		math::mat4 view;
	};
}