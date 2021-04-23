#pragma once
#include "VR.h"

using namespace VR;

class Navigation : public World
{
	GUIMaterial btnMat;
	std::vector<Mesh> meshes;

	struct Button
	{
		Button(math::vec2 pos, math::vec2 size)
			:pos(pos), size(size)
		{

		}
		math::vec2 pos;
		math::vec2 size;
	};

	std::vector<Button> buttons;

public:
	int link = -1;

	Navigation()
		:btnMat({0.0, 1.0, 0.0, 0.0})
	{
		AddButton({ 0.1, 0.1 }, { -0.9, 0.9 }, &btnMat);
		btnMat.color = {0.2, 0.8, 0.0, 0.0};
		AddButton({ 0.1, 0.1 }, { -0.7, 0.9 }, &btnMat);
		btnMat.color = { 0.4, 0.6, 0.0, 0.0 };
		AddButton({ 0.1, 0.1 }, { -0.5, 0.9 }, &btnMat);
		btnMat.color = { 0.6, 0.4, 0.0, 0.0 };
		AddButton({ 0.1, 0.1 }, { -0.3, 0.9 }, &btnMat);
	}

	~Navigation()
	{
	}

	void OnAttach() override
	{
		glfwSetWindowUserPointer(Context::Get()->window, this);
		glfwSetMouseButtonCallback(Context::Get()->window, [](GLFWwindow* window, int button, int action, int mode) {
			Navigation* w = (Navigation*)glfwGetWindowUserPointer(window);
			for (int i = 0; i < w->meshes.size(); i++)
			{
				double mX, mY;
				glfwGetCursorPos(window, &mX, &mY);
				int width, height;
				glfwGetWindowSize(window, &width, &height);
				mX -= width / 2;
				mX /= width / 2;
				mY = height / 2 - mY;
				mY /= height / 2;

				bool inside = false;


				if (w->buttons[i].pos.x < mX &&
					w->buttons[i].pos.x + w->buttons[i].size.x > mX &&
					w->buttons[i].pos.y < mY &&
					w->buttons[i].pos.y + w->buttons[i].size.y > mY)
				{
					w->link = i;
					w->OnDetach();
					break;
				}
			}
			});
		glfwSetWindowSizeCallback(Context::Get()->window, [](GLFWwindow* window, int width, int height) {
			Navigation* w = (Navigation*)glfwGetWindowUserPointer(window);
			w->OnResize(width, height);
			});

		Render();
	}

	void OnResize(int width, int height)
	{
		//proj = math::perspective(1.f, float(wWidth) / wHeight, 0.0, 1000.0f);
		glViewport(0, 0, width, height);
		Render();
	}

	void OnUpdate(float dTime) override
	{

	}

	void AddButton(const math::vec2& size, const math::vec2& pos, Material* material)
	{
		float vert[]
		{
			pos.x, pos.y,
			pos.x, pos.y + size.y,
			pos.x + size.x, pos.y,
			pos.x + size.x, pos.y + size.y,
		};

		uint32_t indices[]
		{
			2, 1, 0,
			1, 2, 3
		};

		Geometry geo;
		geo.indices = indices;
		geo.indices_count = 6;
		geo.vertices = (uint8_t*)vert;
		geo.vertices_size = sizeof(vert);

		meshes.emplace_back(material, geo);

		buttons.emplace_back(pos, size);

		scene.Add(&meshes.back());
	}

	void OnDetach()
	{
		Detach();
		glfwSetWindowSizeCallback(Context::Get()->window, [](GLFWwindow*, int, int) {});
	}
};

