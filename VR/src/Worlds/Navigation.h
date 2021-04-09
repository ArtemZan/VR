#pragma once
#pragma once
#include "VR.h"

using namespace VR;

class Navigation : public World
{
	Material btnMat;
	Material material;
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
		:btnMat("Buttons.shader"), material("Color.shader")
	{
		btnMat.attributesLayout.Push<float>(2);
		btnMat.attributesLayout.Push<float>(4);
		AddButton({ 0.1, 0.1 }, { -0.9, 0.9 }, { 0.0, 1.0, 0.0, 0.0 });
		AddButton({ 0.1, 0.1 }, { -0.7, 0.9 }, { 1.0, 0.0, 0.0, 0.0 });
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
					w->Detach();
					break;
				}
			}
			});

		Render();
	}

	void OnUpdate(float dTime) override
	{

		if (glfwWindowShouldClose(Context::Get()->window))
		{
			Detach();
		}
	}

	void AddButton(const math::vec2& size, const math::vec2& pos, const math::vec4& color)
	{
		float vert[]
		{
			pos.x, pos.y, color.r, color.g, color.b, color.a,
			pos.x, pos.y + size.y, color.r, color.g, color.b, color.a,
			pos.x + size.x, pos.y, color.r, color.g, color.b, color.a,
			pos.x + size.x, pos.y + size.y, color.r, color.g, color.b, color.a
		};

		uint32_t indices[]
		{
			0, 1, 2,
			3, 2, 1
		};

		Geometry geo;
		geo.indices = indices;
		geo.indices_count = 6;
		geo.vertices = (uint8_t*)vert;
		geo.vertices_size = sizeof(vert);

		meshes.emplace_back(&btnMat, geo);

		buttons.emplace_back(pos, size);

		scene.Add(&meshes.back());
	}
};

