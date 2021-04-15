#pragma once
#include "VR.h"

using namespace VR;

constexpr float G = 6.6708e-11;

class TestWorld : public World
{
	math::mat4 proj;
	math::mat4 view;
	math::mat4 mvp;

	_2DMaterial btnMat;
	BasicMaterial sunMat;
	LambertMaterial planetMat;
	std::vector<Mesh> meshes;

	struct Object
	{
		Object(const math::vec3& pos, const math::vec3& velocity, float diameter, float mass, const Mesh& mesh)
			:pos(pos), v(velocity), diameter(diameter), mass(mass), mesh(mesh)
		{

		}
		math::vec3 pos; // 1e6 km
		math::vec3 v;	// 1e6 km/s
		float diameter; // 1e6 km
		float mass;		// 1e18 kg
		Mesh mesh;
	};

	std::vector<Object> objects;

	int wWidth;
	int wHeight;

	float timeWarp = 1.0;
public:

	TestWorld()
		:sunMat({ 1.0, 1.0, 0.2, 0.0 })
	{
		glfwGetWindowSize(Context::Get()->window, &wWidth, &wHeight);

		proj = math::perspective(1.f, float(wWidth) / wHeight, 0.0, 1000.0f);

		camera.SetPosition(math::vec3(0.0, 0.0, 5));
		camera.SetRotation(math::vec3(0.0, 0.0, -1.0));

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

		objects.reserve(5);

		MeshLoader loader;
		loader.Load("res/sphere.obj", &sunMat);
		objects.emplace_back(math::vec3(0.0, 0.0, 0.0), math::vec3(0.0, 0.0, 0.0), 0.695 * 2, 1'988'500e6, loader.mesh);
		scene.Add(&objects.back().mesh);
		objects.back().mesh.Scale(math::vec3( 1.0, 1.0, 1.0 ) * 0.695f * 1e3, {0.0, 0.0, 0.0});

		loader.Load("res/sphere.obj", &planetMat);

		AddObject(loader.mesh, { 0.3, 0.3, 0.3, 0.0 }, { 57.9, 0.0, 0.0 }, 328'500, 4.879e-1, { 0.0, 0.0, 47.4e-6 });
		AddObject(loader.mesh, { 0.9, 0.6, 0.4, 0.0 }, { 108.2, 0.0, 0.0 }, 4'870'000, 12.104e-1, { 0.0, 0.0, 35.0e-6 });
		AddObject(loader.mesh, { 0.3, 0.6, 0.9, 0.0 }, { 149.6, 0.0, 0.0 }, 5'970'000, 12.756e-1, { 0.0, 0.0, 29.8e-6 });

		/*planets.push_back(loader.mesh);
		planetMat.color = ;
		scene.Add(&planets.back());
		planets.back().Scale({ 0.1, 0.1, 0.1 }, {0.0, 0.0, 0.0});
		planets.back().Move({1.0, 0.0, 0.0});
		positions.push_back({ 1.0, 0.0, 0.0 });

		planets.push_back(loader.mesh);
		planetMat.color = {0.9, 0.6, 0.4, 0.0};
		scene.Add(&planets.back());
		planets.back().Scale({ 0.1, 0.1, 0.1 }, { 0.0, 0.0, 0.0 });
		planets.back().Move({ 2.0, 0.0, 0.0 });
		positions.push_back({ 2.0, 0.0, 0.0 });

		planets.push_back(loader.mesh);
		planetMat.color = {0.5, 0.7, 0.9, 0.0};
		scene.Add(&planets.back());
		planets.back().Scale({ 0.1, 0.1, 0.1 }, { 0.0, 0.0, 0.0 });
		planets.back().Move({ 3.0, 0.0, 0.0 });
		positions.push_back({ 3.0, 0.0, 0.0 });

		planets.push_back(loader.mesh);
		planetMat.color = {0.7, 0.3, 0.1, 0.0};
		scene.Add(&planets.back());
		planets.back().Scale({ 0.1, 0.1, 0.1 }, { 0.0, 0.0, 0.0 });
		planets.back().Move({ 4.0, 0.0, 0.0 });
		positions.push_back({ 4.0, 0.0, 0.0 });*/
		
		planetMat.shader->Bind();
		planetMat.shader->SetUniform("ambientLightColor", 0.1, 0.1, 0.1);
		planetMat.shader->SetUniform("diffuseLight.color", 1.0, 1.0, 0.8);
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

		dTime *= timeWarp;

		planetMat.shader->Bind();
		planetMat.shader->SetUniform("diffuseLight.position", 0.0, 0.0, 0.0);

		mvp = proj * camera.view;
		sunMat.shader->Bind();
		sunMat.shader->SetUniform("mvp", mvp);
		planetMat.shader->Bind();
		planetMat.shader->SetUniform("mvp", mvp);

		for (int i = 0; i < objects.size(); i++)
		{
			Object& object = objects[i];
			object.mesh.Move(object.v * dTime * 1e-3 * 1e3);
			object.pos += object.v * dTime * 1e-3;
			math::vec3 a;
			for (int j = 0; j < objects.size(); j++)
			{
				if (i == j) continue;
				math::vec3 d = objects[j].pos - object.pos;
				a += normalize(d) * (objects[j].mass * 1e18 * G / (d.x * d.x + d.y * d.y + d.z * d.z) / 1e18);
				if (abs(d.x) < 1e-5) a.x = 0;
				if (abs(d.y) < 1e-5) a.y = 0;
				if (abs(d.z) < 1e-5) a.z = 0;
			}
			object.v += a * 1e-9 * dTime * 1e-3;
		}

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
		proj = math::perspective(1.f, float(wWidth) / wHeight, 0.0, 1000.0f);
		glViewport(0, 0, width, height);
	}

	void Input(float dTime)
	{
		float speed;//1e6 km/s

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS
			|| glfwGetKey(Context::Get()->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			speed = 10000.0f;
		}
		else
		{
			speed = 500.0f;
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_W) == GLFW_PRESS)
		{
			camera.Move({ camera.dir.x * dTime * 1e-3f * speed, 0.0, camera.dir.z * dTime * 1e-3f * speed });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_S) == GLFW_PRESS)
		{
			camera.Move({ -camera.dir.x * dTime * 1e-3f * speed, 0.0, -camera.dir.z * dTime * 1e-3f * speed });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_A) == GLFW_PRESS)
		{
			camera.Move({ camera.dir.z * dTime * 1e-3f * speed, 0.0, -camera.dir.x * dTime * 1e-3f * speed });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_D) == GLFW_PRESS)
		{
			camera.Move({ -camera.dir.z * dTime * 1e-3f * speed, 0.0, camera.dir.x * dTime * 1e-3f * speed });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			camera.Rotate({ 0.0, 1.0, 0.0 }, 0.003 * dTime);
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			float k = -0.003 * dTime;
			camera.Rotate({ 0.0, 1.0, 0.0 }, k);
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			camera.Move({ 0.0, 0.005f * dTime, 0.0 });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			camera.Move({ 0.0, -0.005f * dTime, 0.0 });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_M) == GLFW_PRESS 
			&& (glfwGetKey(Context::Get()->window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS
			|| glfwGetKey(Context::Get()->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS))
		{
			camera.SetPosition(objects[1].pos * 1e3);
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_V) == GLFW_PRESS 
			&& (glfwGetKey(Context::Get()->window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS
			|| glfwGetKey(Context::Get()->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS))
		{
			camera.SetPosition(objects[2].pos * 1e3);
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_E) == GLFW_PRESS 
			&& (glfwGetKey(Context::Get()->window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS
			|| glfwGetKey(Context::Get()->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS))
		{
			camera.SetPosition(objects[3].pos * 1e3);
		}
		
		if (glfwGetKey(Context::Get()->window, GLFW_KEY_EQUAL) == GLFW_PRESS)
		{
			timeWarp *= 1.1;
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_MINUS) == GLFW_PRESS)
		{
			timeWarp /= 1.1;
		}
	}

	void AddObject(const Mesh& mesh, const math::vec4 color, const math::vec3& position, float mass, float diameter, const math::vec3& velocity = {})
	{
		objects.emplace_back(position, velocity, diameter, mass, mesh);
		planetMat.color = color;
		scene.Add(&objects.back().mesh);
		objects.back().mesh.Scale(math::vec3(1.0, 1.0, 1.0) * diameter * 0.5 * 1e3, { 0.0, 0.0, 0.0 });
		objects.back().mesh.Move(position * 1e3);
	}
};

