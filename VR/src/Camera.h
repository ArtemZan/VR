#pragma once

namespace VR
{
	struct Camera
	{
		math::vec3 pos;
		math::vec3 dir;
		math::mat4 matrix;
	};
}