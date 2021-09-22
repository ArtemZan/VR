#pragma once

using namespace VR;

constexpr float G = 6.6708e-11;

class Monkeys : public World
{
	math::mat4 proj;
	math::mat4 view;
	math::mat4 mvp;

	Material2D btnMat;
	Object2D button;

	Object3D light;

	Object3D zero;


	struct Monkey : public Object3D
	{
		math::mat4 mvp;
		Camera camera;
		bool listen = false;
		bool mouse_down = false;

		Monkey(const Material& mat)
			:Object3D(mat)
		{

		}

		void OnMouseMove(const math::vec2& mp) override
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

				math::vec3 side = normalize(camera.dir).cross(math::vec3({ 0.0, 1.0, 0.0 }));

				math::vec3 pos = Pos();

				float dist = camera.dir.dot(pos - camera.pos);

				mesh.MoveTo(camera.pos + (normalize(camera.dir) + math::vec3(fmp.x * side.x, fmp.y * ws.y / ws.x, fmp.x * side.z)) * dist);  
			}
		}

		void OnMouseDown(int button, int mods) override
		{
			if (listen)
			{
				if (!mouse_down && IsHovered(mvp))
				{
					mouse_down = true;


					//std::cout << "Hover!\n";
					mesh.SetColor({ 0.0, 1.0, 0.0, 0.0 });
				}
				else
				{
					mouse_down = false;
					//std::cout << "---\n";
					mesh.SetColor({ 0.3, 0.2, 0.0, 0.0 });
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
		:button(btnMat)
	{

		IO* io = IO::Get();
		math::vec2i wSize = io->WindowSize();

		proj = math::perspective(1.f, float(wSize.width) / wSize.height, 1.0, 1000.0f);

		m_camera.SetPosition(math::vec3(0.0, 0.0, 10));
		m_camera.SetRotation(math::vec3(0.0, 0.0, -1.0));



		button.mesh.material.SetColor({ 1.0, 1.0, 0.0, 1.0 });

		button.Rect({ 0.1, 0.1 });
		button.MoveTo({ -0.9, 0.9 });
		m_scene.Add(&button.mesh);

		monkeys.reserve(5);


		loader.Load("res/monkey.obj");

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
		monkeys.back().Move({ 5.0, 0.0, 2.0 });
		m_scene.Add(&monkeys.back().mesh);
		
		mat.SetColor({ 1.0, 1.0, 0.2, 0.0 });
		monkeys.emplace_back(monkeys.back());
		monkeys.back().MoveTo({ 0.0, 0.0, -2.0 });
		monkeys.back().Scale(3);
		m_scene.Add(&monkeys.back().mesh);


		mat.SetColor({ 0.3, 0.2, 0.0, 0.0 });
		monkeys.emplace_back(monkeys.back());
		monkeys.back().SetSize(1);
		monkeys.back().MoveTo({ -5.0, 0.0, 2.0 });
		m_scene.Add(&monkeys.back().mesh);



		light.mesh.material.SetColor({ 1.0, 1.0, 1.0, 1.0 });
		light.Box(0.5);
		m_scene.Add(&light.mesh);

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

	void OnMouseDown(GLint button, GLint mods) override
	{
		IO* io = IO::Get();

		math::vec2 mPos = io->MousePos();
		math::vec2i wSize = io->WindowSize();


		double mX = mPos.x, mY = mPos.y;
		int width = wSize.width, height = wSize.height;
		mX -= width / 2;
		mX /= width / 2;
		mY = height / 2 - mY;
		mY /= height / 2;

		math::vec2 btnPos = this->button.Pos();
		math::vec2 btnSize = this->button.Size();

		if (btnPos.x - btnSize.x / 2 < mX &&
			btnPos.x + btnSize.x / 2 > mX &&
			btnPos.y - btnSize.y / 2 < mY &&
			btnPos.y + btnSize.y / 2 > mY)
		{
			link = 0;
			Detach();
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

		mvp = proj * m_camera.view;


		math::vec3 lp(sin(time / 700) * 5, sin(time / 700 + 1.67) * 3, sin(time / 1400) * 5);

		for (Monkey& m : monkeys)
		{
			m.mesh.material.SetShaderUniform("mvp", mvp);
			m.mesh.material.SetShaderUniform("diffuseLight.position", lp);
			m.mvp = mvp;
			m.camera = m_camera;
		}

		light.mesh.material.SetShaderUniform("mvp", mvp);
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

		Render();
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
			m_camera.Move({ m_camera.dir.x * dTime * 1e-3f * speed, 0.0, m_camera.dir.z * dTime * 1e-3f * speed });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_S) == GLFW_PRESS)
		{
			m_camera.Move({ -m_camera.dir.x * dTime * 1e-3f * speed, 0.0, -m_camera.dir.z * dTime * 1e-3f * speed });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_A) == GLFW_PRESS)
		{
			m_camera.Move({ m_camera.dir.z * dTime * 1e-3f * speed, 0.0, -m_camera.dir.x * dTime * 1e-3f * speed });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_D) == GLFW_PRESS)
		{
			m_camera.Move({ -m_camera.dir.z * dTime * 1e-3f * speed, 0.0, m_camera.dir.x * dTime * 1e-3f * speed });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			m_camera.Rotate({ 0.0, 1.0, 0.0 }, 0.003 * dTime);
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			float k = -0.003 * dTime;
			m_camera.Rotate({ 0.0, 1.0, 0.0 }, k);
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			m_camera.Move({ 0.0, 1e-3f * speed * dTime, 0.0 });
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			m_camera.Move({ 0.0, -1e-3f * speed * dTime, 0.0 });
		}
	}
};

