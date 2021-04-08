#pragma once
#include "VR.h"

using namespace VR;

class TestWorld1 : public World
{
	Material btnMat;
public:
	TestWorld1()
		:btnMat("Buttons.shader")
	{
		btnMat.attributesLayout.Push<float>(2);
		btnMat.attributesLayout.Push<float>(4);

		uint32_t btn_indices[]
		{
			0, 1, 2,
			3, 2, 1
		};

		float btn_vert[]
		{
			-1.0, 0.95, 1.0, 0.0, 0.0, 0.0,
			-1.0, 1.0, 1.0, 0.0, 0.0, 0.0,
			-0.9, 0.95, 1.0, 0.0, 0.0, 0.0,
			-0.9, 1.0, 1.0, 0.0, 0.0, 0.0
		};

		Geometry geo;
		geo.indices = btn_indices;
		geo.indices_count = 6;
		geo.vertices = (uint8_t*)btn_vert;
		geo.vertices_size = sizeof(btn_vert);

		Mesh button(&btnMat, geo);

		scene.Add(button);
	}

	~TestWorld1()
	{

	}

	void OnAttach() override
	{
		glfwSetWindowUserPointer(Context::Get()->window, this);
		glfwSetMouseButtonCallback(Context::Get()->window, [](GLFWwindow* window, int button, int action, int mods) {
			TestWorld1* w = (TestWorld1*)glfwGetWindowUserPointer(window);

			double mX, mY;
			glfwGetCursorPos(window, &mX, &mY);
			int width, height;
			glfwGetWindowSize(window, &width, &height);
			mX -= width / 2;
			mX /= width / 2;
			mY = height / 2 - mY;
			mY /= height / 2;

			bool inside = false;


			if (-1.0 < mX &&
				-0.9 > mX &&
				1.0 > mY &&
				0.95 < mY)
			{
				w->Detach();
			}
			});
	}

	void OnUpdate(float dTime) override
	{
		Render();

		if (glfwWindowShouldClose(Context::Get()->window))
		{
			Detach();
		}
	}
};