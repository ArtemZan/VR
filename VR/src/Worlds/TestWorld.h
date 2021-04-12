#pragma once
#include "VR.h"

using namespace VR;

class TestWorld : public World
{
	math::mat4 model;
	math::mat4 proj;
	math::mat4 view;
	math::mat4 rotX;
	math::mat4 rotY;
	math::mat4 mvp;

	_2DMaterial btnMat;
	BasicMaterial material;
	std::vector<Mesh> meshes;

	int wWidth;
	int wHeight;
public:

	TestWorld()
	{
		glfwGetWindowSize(Context::Get()->window, &wWidth, &wHeight);

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

		


		proj = math::perspective(1.f, float(wWidth) / wHeight, 0.1, 100.0f);

		camera.SetPosition(math::vec3(0.0, 4.0, 5));
		camera.SetRotation(math::vec3(0.0, -0.4, -1.0));

		model = math::mat4(1.0f);

		rotX = math::mat4(1.0f);
		rotY = math::mat4(1.0f);

		float data[] =
		{
			 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f,

			 0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
		};


		uint32_t indices[]
		{
			2, 1, 0, 3, 1, 2,

			6, 4, 5, 5, 7, 6,

			 6, 3, 2, 3, 6, 7,

			 3, 5, 1, 5, 3, 7,

			 0, 1, 4, 5, 4, 1,

			 4, 2, 0, 6, 2, 4
		};

		SetClearColor({ 0.7, 0.9, 0.5, 0.0 });

		material.attributesLayout.Push<float>(3);
		material.attributesLayout.Push<float>(4); 
		
		Geometry geometry;
		geometry.vertices = (uint8_t*)data;
		geometry.vertices_size = sizeof(data);
		geometry.indices = indices;
		geometry.indices_count = 36;

		meshes.emplace_back(&material, geometry);
		meshes.emplace_back(&material, geometry);
		meshes.emplace_back(&material, geometry);
		meshes.emplace_back(&material, geometry);

		scene.Add(&meshes[0]);
		scene.Add(&meshes[1]);
		scene.Add(&meshes[2]);
		scene.Add(&meshes[3]);

		for (int i = 0; i < 8; i++)
		{
			((float*)meshes[0].geometry.vertices)[i * 7] -= 2;
			((float*)meshes[1].geometry.vertices)[i * 7] += 2;
			((float*)meshes[2].geometry.vertices)[i * 7 + 2] += 2;
			((float*)meshes[3].geometry.vertices)[i * 7 + 2] -= 2;
		}
		
	}

	~TestWorld()
	{
	}

	void OnAttach() override
	{
		glfwSetWindowUserPointer(Context::Get()->window, this);
		glfwSetMouseButtonCallback(Context::Get()->window, [](GLFWwindow* window, int button, int action, int mods) {
			TestWorld* w = (TestWorld*)glfwGetWindowUserPointer(window);

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
		/*((float*)meshes[0].geometry.vertices)[7 * 0] += 0.001;
		((float*)meshes[0].geometry.vertices)[7 * 2] += 0.001;
		((float*)meshes[0].geometry.vertices)[7 * 4] += 0.001;
		((float*)meshes[0].geometry.vertices)[7 * 6] += 0.001;*/

		meshes[0].Move({ sin((float)glfwGetTime()) / 1000.0f, 0.0f, 0.0f });
		meshes[1].Move({ 0.0f, sin((float)glfwGetTime()) / 1000.0f, 0.0f });
		meshes[2].Move({ 0.0f, 0.0f, sin((float)glfwGetTime()) / 1000.0f });
		meshes[3].Rotate({ 1.0f, 1.0, 1.0 }, {0.0, 0.0, -2.0}, 0.001);

		rotX.y.y = cos(dTime / 1000.0f);
		rotX.y.z = -sin(dTime / 1000.0f);
		rotX.z.y = sin(dTime / 1000.0f);
		rotX.z.z = cos(dTime / 1000.0f);

		rotY.x.x = cos(dTime / 1000.0f);
		rotY.x.z = sin(dTime / 1000.0f);
		rotY.z.x = -sin(dTime / 1000.0f);
		rotY.z.z = cos(dTime / 1000.0f);

		//model *= rotY *rotX;

		//camera.SetPosition(math::vec3(sin(glfwGetTime()) * 5, 0.0, cos(glfwGetTime()) * 5));
		mvp = proj * camera.view * model;
		material.shader.Bind();
		material.shader.SetUniform("mvp", mvp);

		Render();

		if (glfwWindowShouldClose(Context::Get()->window))
		{
			Detach();
		}
	}
};

