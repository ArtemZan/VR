#include "pch.h"
#include "VR.h"

VR::Camera3D::Camera3D(float fov, float aspect, float near, float far, const math::vec3& pos, const math::vec3& direction)
	:fov(fov), aspect(aspect), pos(pos), dir(direction)
{
	proj = math::perspective(fov, aspect, near, far);
	SetView();
}

void VR::Camera3D::SetPosition(math::vec3 pos)
{
	this->pos = pos;
	SetView();
}

void VR::Camera3D::Move(math::vec3 dPos)
{
	pos += dPos;
	SetView();
}

void VR::Camera3D::SetRotation(math::vec3 rot)
{
	dir = normalize(rot);
	SetView();
}

void VR::Camera3D::Rotate(math::vec3 axis, float angle)
{
	dir *= math::rotate(axis, angle);
	dir.normalize(); // ?
	SetView();
}

void VR::Camera3D::SetFOV(float fov)
{
	this->fov = fov;
	proj.x.x = 1.0f / aspect / tan(fov / 2);
	proj.y.y = 1.0f / tan(fov / 2);
}

void VR::Camera3D::SetAspectRatio(float aspect)
{
	this->aspect = aspect;
	proj.x.x = 1.0f / aspect / tan(fov / 2);
}

using namespace VR::fit_types;

VR::Camera2D::Camera2D(float aspect, const math::vec3& pos, fit_t fit)
	:pos(pos), view(1.f), fit(fit)
{
	SetView();
}

void VR::Camera2D::SetPosition(math::vec3 pos)
{
	this->pos = pos;
	SetView();
}

void VR::Camera2D::Move(math::vec3 dPos)
{
	SetPosition(pos + dPos);
}

void VR::Camera2D::SetView()
{
	view.x.x = 1 / pos.z;
	view.y.y = 1 / pos.z;
	view.z.x = pos.x;
	view.z.y = pos.y;

	float x_space = 0;
	float y_space = 0;

	//Scale

	if (fit & FIT_X)
	{
		view.y.y *= aspect;
		y_space = 1 - 1 / aspect;
	}
	else if (fit & FIT_Y)
	{
		view.x.x /= aspect;
		x_space = aspect - 1;
	}
	else if (fit & FIT_MAX)
	{
		if (aspect > 1)
		{
			view.y.y *= aspect;
			y_space = 1 - 1 / aspect;
		}
		else
		{
			view.x.x *= aspect;
			x_space = 1 - 1 / aspect;
		}
	}
	else if((fit & SCREEN) == 0)
	{
		if (aspect > 1)
		{
			view.x.x /= aspect;
			x_space = 1 - 1 / aspect;
		}
		else
		{
			view.y.y *= aspect;
			y_space = 1 - 1 * aspect;
		}
	}

	//Move

	if (fit & ALIGN_LEFT)
	{
		view.z.x -= x_space / pos.z;
	}
	else if (fit & ALIGN_RIGHT)
	{
		view.z.x += x_space / pos.z;
	}

	if (fit & ALIGN_TOP)
	{
		view.z.y += y_space / pos.z;
	}
	else if (fit & ALIGN_BOTTOM)
	{
		view.z.y -= y_space / pos.z;
	}


	/*view.y.y = 1 / pos.z;
	view.z.x = pos.x - 1 / aspect / pos.z;
	view.z.x = pos.x - 1 / aspect / pos.z;
	view.z.y = pos.y;*/
}

void VR::Camera2D::SetAspectRatio(float aspect)
{
	this->aspect = aspect;
	SetView();
}
