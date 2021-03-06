#pragma once

using namespace VR;

class TestWorld1 : public World
{
	GUIMaterial btnMat;
	BasicMaterial basicMat;
	BasicMaterial lightMat;
	LambertMaterial diffuse;
	LambertMaterial monkeyMat;

	math::mat4 proj;
	math::mat4 mvp;

	std::vector<Mesh> meshes;

public:
	TestWorld1()
		:mvp(1.0), basicMat({ 1.0, 1.0, 0.0, 0.0 }), lightMat({1.0, 1.0, 1.0, 1.0})
	{
			int width, height;
			glfwGetWindowSize(Context::Get()->window, &width, &height);
			proj = math::perspective(1.0, (float)width / height, 0.01, 100.0f);
			m_camera.SetPosition({ -7.0, 0.0, 0.0 });
			m_camera.SetRotation({ 5.0, 0.0, 0.0 });

			diffuse.shader->Bind();
			diffuse.shader->SetUniform("mvp", math::mat4(1.0f));
			diffuse.shader->SetUniform("ambientLightColor", 0.1, 0.1, 0.1);
			diffuse.shader->SetUniform("diffuseLight.color", 0.9, 0.9, 0.9);
			diffuse.shader->SetUniform("diffuseLight.position", -4.0, 0.0, 3.0);


			MeshLoader loader;
			loader.Load("res/monkey.obj", &monkeyMat);
			meshes.push_back(loader.mesh);
			m_scene.Add(&meshes.back());
			monkeyMat = loader.mat;
			meshes.back().Move({ -5.0, 0.0, 0.0 });
			monkeyMat.shader->Bind();
			monkeyMat.shader->SetUniform("mvp", math::mat4(1.0f));
			monkeyMat.shader->SetUniform("ambientLightColor", 0.1, 0.1, 0.1);
			monkeyMat.shader->SetUniform("diffuseLight.color", 0.9, 0.9, 0.9);
			monkeyMat.shader->SetUniform("diffuseLight.position", -4.0, 0.0, 3.0);

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

			Geometry btn_geo;
			btn_geo.indices = btn_indices;
			btn_geo.indices_count = 6;
			btn_geo.vertices = (uint8_t*)btn_vert;
			btn_geo.vertices_size = sizeof(btn_vert);

			Mesh button(&btnMat, btn_geo);
			m_scene.Add(button);


			float cube_vert[] =
			{
				-0.5f, -0.5f, -0.5f,  -1.0, 0.0, 0.0,
				-0.5f, -0.5f,  0.5f,  -1.0, 0.0, 0.0,
				-0.5f,  0.5f, -0.5f,  -1.0, 0.0, 0.0,
				-0.5f,  0.5f,  0.5f,  -1.0, 0.0, 0.0,

				 0.5f, -0.5f, -0.5f,  1.0, 0.0, 0.0,
				 0.5f, -0.5f,  0.5f,  1.0, 0.0, 0.0,
				 0.5f,  0.5f, -0.5f,  1.0, 0.0, 0.0,
				 0.5f,  0.5f,  0.5f,  1.0, 0.0, 0.0,

				-0.5f, -0.5f, -0.5f,  0.0, -1.0, 0.0,
				-0.5f, -0.5f,  0.5f,  0.0, -1.0, 0.0,
				 0.5f, -0.5f, -0.5f,  0.0, -1.0, 0.0,
				 0.5f, -0.5f,  0.5f,  0.0, -1.0, 0.0,

				-0.5f,  0.5f, -0.5f,  0.0, 1.0, 0.0,
				-0.5f,  0.5f,  0.5f,  0.0, 1.0, 0.0,
				 0.5f,  0.5f, -0.5f,  0.0, 1.0, 0.0,
				 0.5f,  0.5f,  0.5f,  0.0, 1.0, 0.0,

				-0.5f, -0.5f, -0.5f,  0.0, 0.0, -1.0,
				-0.5f,  0.5f, -0.5f,  0.0, 0.0, -1.0,
				 0.5f, -0.5f, -0.5f,  0.0, 0.0, -1.0,
				 0.5f,  0.5f, -0.5f,  0.0, 0.0, -1.0,

				-0.5f, -0.5f,  0.5f,  0.0, 0.0, 1.0,
				-0.5f,  0.5f,  0.5f,  0.0, 0.0, 1.0,
				 0.5f, -0.5f,  0.5f,  0.0, 0.0, 1.0,
				 0.5f,  0.5f,  0.5f,  0.0, 0.0, 1.0,
			};

			uint32_t indices[]
			{
				0, 1, 2, 3, 2, 1,

				6, 5, 4, 5, 6, 7,

				10, 9, 8, 9, 10, 11,

				14, 13, 12, 13, 14, 15,

				16, 17, 18, 19, 18, 17,

				22, 21, 20, 21, 22, 23
			};


			float octahedron_vert[]
			{
				-0.5f,  0.0f, -0.5f,  0.0, 1.0, -1.0,
				 0.0f,  0.5f,  0.0f,  0.0, 1.0, -1.0,
				 0.5f,  0.0f, -0.5f,  0.0, 1.0, -1.0,

				 0.5f,  0.0f,  0.5f,  0.0, 1.0,  1.0,
				 0.0f,  0.5f,  0.0f,  0.0, 1.0,  1.0,
				-0.5f,  0.0f,  0.5f,  0.0, 1.0,  1.0,

				-0.5f,  0.0f,  0.5f, -1.0, 1.0, 0.0,
				 0.0f,  0.5f,  0.0f, -1.0, 1.0, 0.0,
				-0.5f,  0.0f, -0.5f, -1.0, 1.0, 0.0,

				 0.0f,  0.5f,  0.0f,  1.0, 1.0, 0.0,
				 0.5f,  0.0f,  0.5f,  1.0, 1.0, 0.0,
				 0.5f,  0.0f, -0.5f,  1.0, 1.0, 0.0,


				 0.5f,  0.0f, -0.5f,  0.0, -1.0, -1.0,
				 0.0f, -0.5f,  0.0f,  0.0, -1.0, -1.0,
				-0.5f,  0.0f, -0.5f,  0.0, -1.0, -1.0,

				 0.0f, -0.5f,  0.0f,  0.0, -1.0,  1.0,
				 0.5f,  0.0f,  0.5f,  0.0, -1.0,  1.0,
				-0.5f,  0.0f,  0.5f,  0.0, -1.0,  1.0,

				 0.0f, -0.5f,  0.0f, -1.0, -1.0, 0.0,
				-0.5f,  0.0f,  0.5f, -1.0, -1.0, 0.0,
				-0.5f,  0.0f, -0.5f, -1.0, -1.0, 0.0,

				 0.5f,  0.0f,  0.5f,  1.0, -1.0, 0.0,
				 0.0f, -0.5f,  0.0f,  1.0, -1.0, 0.0,
				 0.5f,  0.0f, -0.5f,  1.0, -1.0, 0.0,
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

			Geometry octahedron;
			octahedron.indices = octahedron_ind;
			octahedron.indices_count = 8 * 3;
			octahedron.vertices = (uint8_t*)octahedron_vert;
			octahedron.vertices_size = sizeof(octahedron_vert);

			meshes.emplace_back(&diffuse, octahedron);
			m_scene.Add(&meshes.back());
			meshes.back().Move({ 0.0, 0.0, 2.0 });

			meshes.emplace_back();
			m_scene.AddBox({ 0.5, 0.5, 0.5 }, &lightMat, &meshes.back());
			meshes.back().Move({ -4.0, 0.0, 3.0 });

			meshes.emplace_back();
			m_scene.AddBox({ 1.0, 1.0, 1.0 }, &basicMat, &meshes.back());
			meshes.back().Move({0.0, 2.0, 0.0});
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
			//meshes.back().Move({ -0.001, 0.0, 0.0 });
			//std::cout << (int*)scene.batches[2].vertices.data() << " " << scene.batches[2].vertices.size() << std::endl;
			Input(dTime);

			for (Scene::Batch& batch : m_scene.batches)
			{
				if (batch.materialType != MATERIAL_TYPE::_2D)
				{
					batch.shader->Bind();
					batch.shader->SetUniform("mvp", proj * m_camera.view);

				}
			}

			//meshes[0].Rotate({ 0.0, 1.0, 0.0 }, { -5.0, 0.0, 0.0 }, 0.0005 * dTime);

			Render();

			if (glfwWindowShouldClose(Context::Get()->window))
			{
				Detach();
			}
	}

	void Input(float dTime)
	{
		if (glfwGetKey(Context::Get()->window, GLFW_KEY_W) == GLFW_PRESS)
		{
			m_camera.Move({ m_camera.dir.x / 100 * dTime, 0.0, m_camera.dir.z / 100 * dTime });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_S) == GLFW_PRESS)
		{
			m_camera.Move({ -m_camera.dir.x / 100 * dTime, 0.0, -m_camera.dir.z / 100 * dTime });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_A) == GLFW_PRESS)
		{
			m_camera.Move({ m_camera.dir.z / 100 * dTime, 0.0, -m_camera.dir.x / 100 * dTime });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_D) == GLFW_PRESS)
		{
			m_camera.Move({ -m_camera.dir.z / 100 * dTime, 0.0, m_camera.dir.x / 100 * dTime });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			m_camera.Rotate({ 0.0, 1.0, 0.0 }, 0.005 * dTime);
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			m_camera.Rotate({ 0.0, 1.0, 0.0 }, -0.005 * dTime);
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			m_camera.Move({ 0.0, 0.005f * dTime, 0.0 });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			m_camera.Move({ 0.0, -0.005f * dTime, 0.0 });
		}
	}
};