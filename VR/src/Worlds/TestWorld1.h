#pragma once
#include "VR.h"

using namespace VR;

class TestWorld1 : public World
{
	Material btnMat;
	Material basicMat;
	Material diffuse;

	math::mat4 proj;
	math::mat4 mvp;

	std::vector<Mesh> meshes;

public:
	TestWorld1()
		:btnMat("Buttons.shader"), diffuse("Diffuse.shader"), basicMat("Color.shader"), mvp(1.0)
	{
		int width, height;
		glfwGetWindowSize(Context::Get()->window, &width, &height);
		proj = math::perspective(1.0, (float)width / height, 0.01, 100.0f);
		camera.SetPosition({ -7.0, 0.0, 0.0 });
		camera.SetRotation({ 5.0, 0.0, 0.0 });

		btnMat.attributesLayout.Push<float>(2);
		btnMat.attributesLayout.Push<float>(4);

		diffuse.attributesLayout.Push<float>(3);
		diffuse.attributesLayout.Push<float>(4);
		diffuse.attributesLayout.Push<float>(3);

		basicMat.attributesLayout.Push<float>(3);
		basicMat.attributesLayout.Push<float>(4);

		diffuse.shader.Bind();
		diffuse.shader.SetUniform("mvp", math::mat4(1.0f));
		diffuse.shader.SetUniform("ambientLightColor", 0.1, 0.1, 0.1);
		diffuse.shader.SetUniform("diffuseLight.color", 0.9, 0.9, 0.9);
		diffuse.shader.SetUniform("diffuseLight.position", -4.0, 0.0, 3.0);

		Material::LambertMaterial->shader.Bind();
		Material::LambertMaterial->shader.SetUniform("mvp", math::mat4(1.0f));
		Material::LambertMaterial->shader.SetUniform("ambientLightColor", 0.1, 0.1, 0.1);
		Material::LambertMaterial->shader.SetUniform("diffuseLight.color", 0.9, 0.9, 0.9);
		Material::LambertMaterial->shader.SetUniform("diffuseLight.position", -4.0, 0.0, 3.0);


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

		Geometry btn_geo;
		btn_geo.indices = btn_indices;
		btn_geo.indices_count = 6;
		btn_geo.vertices = (uint8_t*)btn_vert;
		btn_geo.vertices_size = sizeof(btn_vert);

		Mesh button(&btnMat, btn_geo);

		scene.Add(button);

		float light_vert[] =
		{
			 0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0, 0.0f,
			-0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0, 0.0f,
			 0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0f,
			-0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0f,

			 0.5f, -0.5f, 0.5f, 1.0, 1.0, 1.0, 0.0f,
			-0.5f, -0.5f, 0.5f, 1.0, 1.0, 1.0, 0.0f,
			 0.5f,  0.5f, 0.5f, 1.0, 1.0, 1.0, 1.0f,
			-0.5f,  0.5f, 0.5f, 1.0, 1.0, 1.0, 1.0f,
		};

		uint32_t light_ind[]
		{
			2, 1, 0, 3, 1, 2,

			6, 4, 5, 5, 7, 6,

			 6, 3, 2, 3, 6, 7,

			 3, 5, 1, 5, 3, 7,

			 0, 1, 4, 5, 4, 1,

			 4, 2, 0, 6, 2, 4
		};


		float cube_vert[] =
		{
			-0.5f, -0.5f, -0.5f,  0.0, 1.0, 1.0, 0.0,  -1.0, 0.0, 0.0,
			-0.5f, -0.5f,  0.5f,  0.0, 1.0, 1.0, 0.0,  -1.0, 0.0, 0.0,
			-0.5f,  0.5f, -0.5f,  0.0, 1.0, 1.0, 0.0,  -1.0, 0.0, 0.0,
			-0.5f,  0.5f,  0.5f,  0.0, 1.0, 1.0, 0.0,  -1.0, 0.0, 0.0,
								  				   
			 0.5f, -0.5f, -0.5f,  0.0, 1.0, 1.0, 0.0,  1.0, 0.0, 0.0,
			 0.5f, -0.5f,  0.5f,  0.0, 1.0, 1.0, 0.0,  1.0, 0.0, 0.0,
			 0.5f,  0.5f, -0.5f,  0.0, 1.0, 1.0, 0.0,  1.0, 0.0, 0.0,
			 0.5f,  0.5f,  0.5f,  0.0, 1.0, 1.0, 0.0,  1.0, 0.0, 0.0,
								  				   
			-0.5f, -0.5f, -0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, -1.0, 0.0,
			-0.5f, -0.5f,  0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, -1.0, 0.0,
			 0.5f, -0.5f, -0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, -1.0, 0.0,
			 0.5f, -0.5f,  0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, -1.0, 0.0,
								  		   
			-0.5f,  0.5f, -0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, 1.0, 0.0,
			-0.5f,  0.5f,  0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, 1.0, 0.0,
			 0.5f,  0.5f, -0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, 1.0, 0.0,
			 0.5f,  0.5f,  0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, 1.0, 0.0,
								  			   
			-0.5f, -0.5f, -0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, 0.0, -1.0,
			-0.5f,  0.5f, -0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, 0.0, -1.0,
			 0.5f, -0.5f, -0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, 0.0, -1.0,
			 0.5f,  0.5f, -0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, 0.0, -1.0,
								 
			-0.5f, -0.5f, 0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, 0.0, 1.0,
			-0.5f,  0.5f, 0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, 0.0, 1.0,
			 0.5f, -0.5f, 0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, 0.0, 1.0,
			 0.5f,  0.5f, 0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, 0.0, 1.0,
		};

		uint32_t indices[]
		{
			2, 1, 0, 1, 2, 3,

			4, 5, 6, 7, 6, 5,

			8, 9, 10, 11, 10, 9,

			14, 13, 12, 13, 14, 15,

			18, 17, 16, 17, 18, 19,

			20, 21, 22, 23, 22, 21
		};
		

		float octahedron_vert[]
		{
			-0.5f,  0.0f, -0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, 1.0, -1.0,
			 0.5f,  0.0f, -0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, 1.0, -1.0,
			 0.0f,  0.5f,  0.0f,  0.0, 1.0, 1.0, 0.0,  0.0, 1.0, -1.0,

			-0.5f,  0.0f,  0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, 1.0,  1.0,
			 0.0f,  0.5f,  0.0f,  0.0, 1.0, 1.0, 0.0,  0.0, 1.0,  1.0,
			 0.5f,  0.0f,  0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, 1.0,  1.0,

			-0.5f,  0.0f, -0.5f,  0.0, 1.0, 1.0, 0.0, -1.0, 1.0, 0.0,
			 0.0f,  0.5f,  0.0f,  0.0, 1.0, 1.0, 0.0, -1.0, 1.0, 0.0,
			-0.5f,  0.0f,  0.5f,  0.0, 1.0, 1.0, 0.0, -1.0, 1.0, 0.0,

			 0.5f,  0.0f, -0.5f,  0.0, 1.0, 1.0, 0.0,  1.0, 1.0, 0.0,
			 0.5f,  0.0f,  0.5f,  0.0, 1.0, 1.0, 0.0,  1.0, 1.0, 0.0,
			 0.0f,  0.5f,  0.0f,  0.0, 1.0, 1.0, 0.0,  1.0, 1.0, 0.0,


			-0.5f,  0.0f, -0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, -1.0, -1.0,
			 0.0f, -0.5f,  0.0f,  0.0, 1.0, 1.0, 0.0,  0.0, -1.0, -1.0,
			 0.5f,  0.0f, -0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, -1.0, -1.0,
															
			-0.5f,  0.0f,  0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, -1.0,  1.0,
			 0.5f,  0.0f,  0.5f,  0.0, 1.0, 1.0, 0.0,  0.0, -1.0,  1.0,
			 0.0f, -0.5f,  0.0f,  0.0, 1.0, 1.0, 0.0,  0.0, -1.0,  1.0,
															
			-0.5f,  0.0f, -0.5f,  0.0, 1.0, 1.0, 0.0, -1.0, -1.0, 0.0,
			-0.5f,  0.0f,  0.5f,  0.0, 1.0, 1.0, 0.0, -1.0, -1.0, 0.0,
			 0.0f, -0.5f,  0.0f,  0.0, 1.0, 1.0, 0.0, -1.0, -1.0, 0.0,
															
			 0.5f,  0.0f, -0.5f,  0.0, 1.0, 1.0, 0.0,  1.0, -1.0, 0.0,
			 0.0f, -0.5f,  0.0f,  0.0, 1.0, 1.0, 0.0,  1.0, -1.0, 0.0,
			 0.5f,  0.0f,  0.5f,  0.0, 1.0, 1.0, 0.0,  1.0, -1.0, 0.0,
		};

		uint32_t octahedron_ind[8 * 3];
		for (int i = 0; i < 8 * 3; i++)
		{
			octahedron_ind[i] = i;
		}

		Geometry cube_geo;
		cube_geo.indices = indices;
		cube_geo.indices_count = 36;
		cube_geo.vertices = (uint8_t*)cube_vert;
		cube_geo.vertices_size = sizeof(cube_vert);

		Geometry light_cube_geo;
		light_cube_geo.indices = light_ind;
		light_cube_geo.indices_count = 36;
		light_cube_geo.vertices = (uint8_t*)light_vert;
		light_cube_geo.vertices_size = sizeof(light_vert);

		Geometry octahedron;
		octahedron.indices = octahedron_ind;
		octahedron.indices_count = 8 * 3;
		octahedron.vertices = (uint8_t*)octahedron_vert;
		octahedron.vertices_size = sizeof(octahedron_vert);

		meshes.emplace_back(&diffuse, cube_geo);
		meshes.emplace_back(&diffuse, octahedron);
		meshes.emplace_back(&basicMat, light_cube_geo);

		scene.Add(&meshes[0]);
		scene.Add(&meshes[1]);
		scene.Add(&meshes[2]);

		meshes.back().Move({ -4.0, 0.0, 3.0 });
		meshes[1].Move({-2.0, 0.0, 2.0});

		//Mesh box = scene.AddBasicBox({ 1.0, 1.0, 1.0 }, { 0.0, 1.0, 0.0, 0.0 });
		//box.Move({0.0, 2.0, 0.0});

		MeshLoader loader;
		loader.Load("res/cube.obj", "");

		scene.Add(loader.mesh);
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
		if (glfwGetKey(Context::Get()->window, GLFW_KEY_W) == GLFW_PRESS)
		{
			camera.Move({ camera.dir.x / 100, 0.0, camera.dir.z / 100 });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_S) == GLFW_PRESS)
		{
			camera.Move({ -camera.dir.x / 100, 0.0, -camera.dir.z / 100 });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_A) == GLFW_PRESS)
		{
			camera.Move({ camera.dir.z / 100, 0.0, -camera.dir.x / 100 });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_D) == GLFW_PRESS)
		{
			camera.Move({ -camera.dir.z / 100, 0.0, camera.dir.x / 100 });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			camera.Rotate({ 0.0, 1.0, 0.0 }, 0.005);
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			camera.Rotate({ 0.0, 1.0, 0.0 }, -0.005);
		}

		//camera.SetPosition({ (float)sin(glfwGetTime()), 0.0, (float)cos(glfwGetTime()) });
		diffuse.shader.Bind();
		diffuse.shader.SetUniform("mvp", proj * camera.view);
		basicMat.shader.Bind();
		basicMat.shader.SetUniform("mvp", proj * camera.view);
		Material::BasicMaterial->shader.Bind();
		Material::BasicMaterial->shader.SetUniform("mvp", proj * camera.view);
		Material::LambertMaterial->shader.Bind();
		Material::LambertMaterial->shader.SetUniform("mvp", proj * camera.view);

		//diffuse.shader.SetUniform("diffuseLight.position", sin(glfwGetTime()) * 3, 0.0, sin(glfwGetTime()));
		meshes[0].Rotate({ 1.0, 1.0, 1.0 }, { 0.0, 0.0, 0.0 }, 0.001);
		meshes[1].Rotate({ 0.1, 1.0, 0.0 }, { -2.0, 0.0, 2.0 }, 0.001);

		Render();

		if (glfwWindowShouldClose(Context::Get()->window))
		{
			Detach();
		}
	}
};