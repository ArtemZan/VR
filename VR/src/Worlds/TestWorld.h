#pragma once
#include "VR.h"

using namespace VR;

class TestWorld : public World
{
	math::mat4 proj;
	math::mat4 view;
	math::mat4 mvp;

	_2DMaterial btnMat;
	BasicMaterial sunMat;
	LambertMaterial earthMat;
	std::vector<Mesh> meshes;

	int wWidth;
	int wHeight;
public:

	TestWorld()
		:sunMat({ 1.0, 1.0, 0.0, 0.0 }), earthMat({0.0, 0.1, 0.8, 1.0})
	{
		glfwGetWindowSize(Context::Get()->window, &wWidth, &wHeight);

		proj = math::perspective(1.f, float(wWidth) / wHeight, 0.1, 100.0f);

		camera.SetPosition(math::vec3(0.0, 4.0, 5));
		camera.SetRotation(math::vec3(0.0, -0.4, -1.0));

		uint32_t btn_indices[]
		{
			0, 1, 2,
			3, 2, 1
		};

		float btn_vert[]
		{
			-1.0, 0.95,
			-1.0, 1.0, 
			-0.9, 0.95,
			-0.9, 1.0, 
		};

		Geometry geo;
		geo.indices = btn_indices;
		geo.indices_count = 6;
		geo.vertices = (uint8_t*)btn_vert;
		geo.vertices_size = sizeof(btn_vert);

		Mesh button(&btnMat, geo);
		scene.Add(button);

		MeshLoader loader;
		loader.Load("res/sphere.obj", "");
		loader.mesh.material = &sunMat;
		meshes.push_back(loader.mesh);
		scene.Add(&meshes.back());
		meshes.back().Scale({ 0.5, 0.5, 0.5 }, {0.0, 0.0, 0.0});

		/*float data[] =
		{
			 0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,

			 0.5f, -0.5f, 0.5f, 
			-0.5f, -0.5f, 0.5f, 
			 0.5f,  0.5f, 0.5f, 
			-0.5f,  0.5f, 0.5f, 
		};


		uint32_t indices[]
		{
			2, 1, 0, 3, 1, 2,

			6, 4, 5, 5, 7, 6,

			 6, 3, 2, 3, 6, 7,

			 3, 5, 1, 5, 3, 7,

			 0, 1, 4, 5, 4, 1,

			 4, 2, 0, 6, 2, 4
		};	*/	
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
		glfwSetWindowSizeCallback(Context::Get()->window, [](GLFWwindow* window, int width, int height) {
			TestWorld* w = (TestWorld*)glfwGetWindowUserPointer(window);
			w->OnResize(width, height);
			});
	}

	void OnUpdate(float dTime) override
	{
		Input(dTime);
		//camera.SetPosition(math::vec3(sin(glfwGetTime()) * 2.f, 0.0f, cos(glfwGetTime()) * 2.f));
		//camera.SetRotation(math::vec3(-sin(glfwGetTime()), 0.0f, -cos(glfwGetTime())));
		mvp = proj * camera.view;
		sunMat.shader->Bind();
		sunMat.shader->SetUniform("mvp", mvp);
		earthMat.shader->Bind();
		earthMat.shader->SetUniform("mvp", mvp);

		Render();

		if (glfwWindowShouldClose(Context::Get()->window))
		{
			Detach();
		}
	}

	void OnResize(int width, int height)
	{
		wWidth = width;
		wHeight = height;
		proj = math::perspective(1.f, float(wWidth) / wHeight, 0.1, 100.0f);
		glViewport(0, 0, width, height);
	}

	void Input(float dTime)
	{
		if (glfwGetKey(Context::Get()->window, GLFW_KEY_W) == GLFW_PRESS)
		{
			camera.Move({ camera.dir.x / 100 * dTime, 0.0, camera.dir.z / 100 * dTime });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_S) == GLFW_PRESS)
		{
			camera.Move({ -camera.dir.x / 100 * dTime, 0.0, -camera.dir.z / 100 * dTime });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_A) == GLFW_PRESS)
		{
			camera.Move({ camera.dir.z / 100 * dTime, 0.0, -camera.dir.x / 100 * dTime });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_D) == GLFW_PRESS)
		{
			camera.Move({ -camera.dir.z / 100 * dTime, 0.0, camera.dir.x / 100 * dTime });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			camera.Rotate({ 0.0, 1.0, 0.0 }, 0.005 * dTime);
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			camera.Rotate({ 0.0, 1.0, 0.0 }, -0.005 * dTime);
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			camera.Move({ 0.0, 0.005f * dTime, 0.0 });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			camera.Move({ 0.0, -0.005f * dTime, 0.0 });
		}
	}
};

