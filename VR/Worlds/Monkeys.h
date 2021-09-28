#pragma once

using namespace VR;

constexpr float G = 6.6708e-11;

class Monkeys : public World
{
	Camera3D camera;

	math::mat4 proj;
	math::mat4 mvp;

	Material2D btnMat;
	Mesh2D button;

	Mesh3DColor light;


	struct Monkey : public Mesh3D, Events
	{
		bool listen = false;
		bool mouse_down = false;

		Monkey(const Material& mat)
			:Mesh3D(mat)
		{
			AddHandler(this);
		}

		Monkey(const Monkey& monkey)
			:Mesh3D(monkey)
		{
			AddHandler(this);
		}

		~Monkey()
		{
			RemoveHandler(this);
		}

		void OnMouseMove(const Camera3D& camera, const math::vec2& mp)
		{
			if (mouse_down)
			{
				IO* io = IO::Get();
				math::vec2 fmp = io->MousePos();
				math::vec2 ws = io->WindowSize();
				fmp /= ws;
				fmp *= 2;
				fmp.x -= 1;
				fmp.y = 1 - fmp.y;

#ifdef RIGHT_HANDED
				math::vec3 side = -normalize(camera.Dir()).cross(math::vec3({ 0.0, 1.0, 0.0 }));
#endif
				math::vec3 pos = Pos();

				float dist = camera.Dir().dot(pos - camera.Pos());

				MoveTo(camera.Pos() + (normalize(camera.Dir()) + math::vec3(fmp.x * side.x, fmp.y * ws.y / ws.x, fmp.x * side.z)) * dist);  
			}
		}

		void OnMouseDown(const math::mat4& mvp, int button)
		{

			if (listen)
			{
				if (!mouse_down && IsHovered(mvp))
				{
					mouse_down = true;


					//std::cout << "Hover!\n";
					SetColor({ 0.0, 1.0, 0.0, 0.0 });
				}
				else
				{
					mouse_down = false;
					//std::cout << "---\n";
					SetColor({ 0.3, 0.2, 0.0, 0.0 });
				}
			}
			
		}
	};

	std::vector<Monkey> monkeys;

	friend struct Monkey;

	MeshLoader loader;

	float time = 0;
public:

	Monkeys()
		:camera(1.f, 0, 1.0, 1000.0f, { 0.0, 0.0, 10 }, { 0.0, 0.0, -1.0 })
	{

		IO* io = IO::Get();
		math::vec2i wSize = io->WindowSize();

		camera.SetAspectRatio(float(wSize.width) / wSize.height);

		button.SetColor({ 0.0, 1.0, 0.0, 1.0 });

		button.Rect({ 0.1, 0.1 });
		button.MoveTo({ -0.9, 0.9 });
		m_scene.Add(button);

		monkeys.reserve(5);

		loader.Load("res/cube.obj");

		Material mat = loader.GetMaterial();
		const std::vector<float>& vertices = loader.GetVertices();
		const std::vector<uint32_t>& indices = loader.GetIndices();

		mat.SetShaderUniform("ambientLightColor", math::vec3(0.3, 0.3, 0.0));
		mat.SetShaderUniform("diffuseLight.color", math::vec3(1.0, 1.0, 1.0));
		mat.SetShaderUniform("diffuseLight.position", math::vec3(5.0, 2.0, 3.0));
		mat.SetShaderUniform("mvp", proj);

		mat.SetColor({ 0.3, 0.2, 0.0, 0.0 });
		monkeys.emplace_back(mat);
		monkeys.back().Shape((uint8_t*)vertices.data(), vertices.size() * 4, indices.data(), indices.size());
		//monkeys.back().Cube(1);
		monkeys.back().Move({ 5.0, 0.0, 2.0 });
		monkeys.back().CreateNormals();
		//monkeys.back().ShadeSmooth();
		m_scene.Add(monkeys.back());
		
		mat.SetColor({ 1.0, 1.0, 0.2, 0.0 });
		monkeys.emplace_back(monkeys.back());
		monkeys.back().MoveTo({ 0.0, 0.0, -2.0 });
		monkeys.back().Scale(3);
		m_scene.Add(monkeys.back());


		mat.SetColor({ 0.3, 0.2, 0.0, 0.0 });
		monkeys.emplace_back(monkeys.back());
		monkeys.back().SetScale(1);
		monkeys.back().MoveTo({ -5.0, 0.0, 2.0 });
		m_scene.Add(monkeys.back());



		light.GetMaterial().SetColor({ 1.0, 1.0, 1.0, 1.0 });
		light.Box(0.5);
		m_scene.Add(light);

		//zero.mesh.material.SetColor({ 1.0, 0.0, 1.0, 1.0 });
		//zero.Box({0.1, 10, 0.1});
		//m_scene.Add(&zero.mesh);
	}

	~Monkeys()
	{
	}

	void OnAttach() override
	{
		AddHandler(this);


		for (Monkey& monkey : monkeys)
		{
			monkey.listen = true;
		}
	}

	void OnDetach() override
	{
		
	}

	void OnMouseDown(GLint btn_code, GLint mods) override
	{
		for (Monkey& m : monkeys)
		{
			m.OnMouseDown(mvp, btn_code);
		}

		if (button.IsHovered(math::mat3x2(1.0)))
		{
			link = 0;
			Detach();
		}
	}

	void OnMouseMove(const math::vec2& pos) override
	{
		for (Monkey& m : monkeys)
		{
			m.OnMouseMove(camera, pos);
		}
	}

	void OnWindowResize(int width, int height)
	{
		IO* io = IO::Get();
		math::vec2i wSize = io->WindowSize();

		proj = math::perspective(1.f, float(wSize.width) / wSize.height, 0.0, 1000.0f);
		glViewport(0, 0, width, height);
	}

	void OnUpdate(float dTime) override
	{
		time += dTime;

		Input(dTime);

		mvp = camera.Proj() * camera.View();


		math::vec3 lp(sin(time / 700) * 5, sin(time / 700 + 1.67) * 3, sin(time / 1400) * 5);

		for (Monkey& m : monkeys)
		{
			m.GetMaterial().SetShaderUniform("mvp", mvp);
			m.GetMaterial().SetShaderUniform("diffuseLight.position", lp);
		}

		light.GetMaterial().SetShaderUniform("mvp", mvp);
		light.MoveTo(lp);



		//for (int i = 0; i < objects.size(); i++)
		//{
		//	math::vec3 dPos;
		//	Object& object = objects[i];
		//	math::vec3 a;
		//	for (int t = 0; t < timeWarp; t++)
		//	{
		//		for (int j = 0; j < objects.size(); j++)
		//		{
		//			if (i == j) continue;
		//			math::vec3 d = objects[j].pos - object.pos;

		//			float r2 = d.x * d.x + d.y * d.y + d.z * d.z;
		//			if (r2 > 1e-6)
		//				a = normalize(d) * (objects[j].mass * 1e18 * G / r2 / 1e18);
		//			else
		//				a = object.a;
		//		}
		//		a *= 1e-9; // 1e6 km
		//		//a = {(float)sin(glfwGetTime()), 0.0, 0.0};
		//		object.pos += (((a + object.a) / 6.0 + object.a / 2.0f) * dTime / 1000.0 + object.v) * dTime / 1000.0;
		//		dPos += (((a + object.a) / 6.0 + object.a / 2.0f) * dTime / 1000.0 + object.v) * dTime / 1000.0;
		//		object.v += ((a - object.a) / 2.0 + object.a) * dTime / 1000.0;
		//		object.a = a;
		//	}
		//	object.mesh.Move(dPos * 1e3/*to simulation units*/);
		//}

		m_scene.Render();
		MustUpdate();
	}


	void Input(float dTime)
	{
		float speed;//1e6 km/s

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS
			|| glfwGetKey(Context::Get()->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			speed = 20.0f;
		}
		else
		{
			speed = 5.0f;
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_W) == GLFW_PRESS)
		{
			camera.Move({ camera.Dir().x * dTime * 1e-3f * speed, 0.0, camera.Dir().z * dTime * 1e-3f * speed });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_S) == GLFW_PRESS)
		{
			camera.Move({ -camera.Dir().x * dTime * 1e-3f * speed, 0.0, -camera.Dir().z * dTime * 1e-3f * speed });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_A) == GLFW_PRESS)
		{
			camera.Move({ camera.Dir().z * dTime * 1e-3f * speed, 0.0, -camera.Dir().x * dTime * 1e-3f * speed });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_D) == GLFW_PRESS)
		{
			camera.Move({ -camera.Dir().z * dTime * 1e-3f * speed, 0.0, camera.Dir().x * dTime * 1e-3f * speed });
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
			camera.Move({ 0.0, 1e-3f * speed * dTime, 0.0 });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			camera.Move({ 0.0, -1e-3f * speed * dTime, 0.0 });
		}
	}
};

