#include "pch.h"
#include "VR.h"

VR::Camera::Camera(const math::vec3& pos, const math::vec3& direction)
	:pos(pos), dir(direction)
{
}

void VR::Camera::SetPosition(math::vec3 pos)
{
	this->pos = pos;
	view = math::lookAt(pos, dir, math::vec3(0, 1, 0));
}

void VR::Camera::Move(math::vec3 dPos)
{
	pos += dPos;
	view = math::lookAt(pos, dir, math::vec3(0, 1, 0));
}

void VR::Camera::SetRotation(math::vec3 rot)
{
	dir = rot;
	view = math::lookAt(pos, dir, math::vec3(0, 1, 0));
}

void VR::Camera::Rotate(math::vec3 axis, float angle)
{
	//view = math::lookAt(pos, dir, math::vec3(0, 1, 0));
}
