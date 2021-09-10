#pragma once

using namespace VR;

float G1 = 1e-3;

class Gravitation : public World
{
	struct Object : public Object2D
	{
		Object()
		{

		}

		float m;
		float r;
		math::vec2 v;
		math::vec2 a;
	};

	static constexpr int n = 25;
	std::array<float, (n + 1) * 2> vert;
	std::array<uint32_t, n * 3> ind;
	Geometry geo;
	_2DMaterial mat;

	std::vector<Object> objects;
	math::mat3 view;
	float scale = 0.1;

	Timer timer;

public:

	Gravitation()
		:view(1.0f)
	{
		SetView();

		for (int i = 0; i < n; i++)
		{
			vert[i * 2] = cos(float(i) / float(n) * 3.14159 * 2);
			vert[i * 2 + 1] = sin(float(i) / float(n) * 3.14159 * 2);
		}
		vert[n * 2] = 0.0f;
		vert[n * 2 + 1] = 0.0f;

		for (int i = 0; i < n; i++)
		{
			ind[i * 3] = n;
			ind[i * 3 + 1] = i;
			ind[i * 3 + 2] = i + 1;
		}
		ind[n * 3 - 1] = 0;

		geo.vertices = (uint8_t*)vert.data();
		geo.vertices_size = sizeof(vert);
		geo.indices = ind.data();
		geo.indices_count = n * 3;

		mat.color = { 1.0, 1.0, 1.0, 0.0 };

		srand(glfwGetTime() * 1000.0);

		objects.reserve(5);
		for (int i = 0; i < 5; i++)
		{
			float r = float(rand() % 10) / 10.0f + 0.2;
			float x = float(rand() % 100) / 5.0f - 10.0f;
			float y = float(rand() % 100) / 5.0f - 10.0f;
			float m = pow(r, 2);
			float vx = (float(rand() % 1000) * 1e-6f - 5e-7f) / m;
			float vy = (float(rand() % 1000) * 1e-6f - 5e-7f) / m;
			mat.color = {1.0, 1.0, 0.0, 0.0};//{ (r - 0.2f) * 10.0f, 0.01f / (r - 0.2f), 0.0f, 1.0f };
			AddObject({ r, r }, { x, y }, m, { vx, vy });
		}
	}

	void SetView()
	{
		IO* io = IO::Get();
		math::vec2i wSize = io->WindowSize();
		view.x.x = wSize.height / wSize.width * scale;
		view.y.y = scale;
		mat.shader->Bind();
		mat.shader->SetUniform("view", view);
	}

	void OnWindowResize(int width, int height) override
	{
		SetView();
	}

	void OnKeyDown(int key)
	{
		if (key == GLFW_KEY_DOWN)
		{
			for (Object& o : objects)
			{
				o.v *= 0.9;
			}
			//G1 *= 0.99;
		}
		
		if (key == GLFW_KEY_UP)
		{
			for (Object& o : objects)
			{
				o.v *= 1.1;
			}
			//G1 *= 1.01;
		}
	}

	void OnAttach()
	{
		AddHandler(this);

		mat.shader->Bind();
		mat.shader->SetUniform("view", view);

		glfwSetWindowUserPointer(Context::Get()->window, this);
		glfwSetKeyCallback(Context::Get()->window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			Gravitation* w = (Gravitation*)glfwGetWindowUserPointer(window);
			if (action == GLFW_PRESS)
				w->OnKeyDown(key);
			});
	}

	void OnUpdate(float dTime) override
	{
		//time += dTime;
		//if (time > 500.0 && objects.size() < 10)
		//{
		//	//AddObject({ 0.3f, 0.3f }, { -10.0, -5.0 }, 100.0f, { 0.01, 0.015 });
		//	time = 0;
		//}
		

		Render();
	}

	void OnPhysicsUpdate(float dTime) override
	{
		//std::cout << timer.Update() << std::endl;
		constexpr int k = 1;

		dTime /= float(k);
		for (int i = 0; i < k; i++)
		{
			for (int o1 = 0; o1 < objects.size(); o1++)
			{
				math::vec2 a;
				for (int o2 = 0; o2 < objects.size(); o2++)
				{
					if (o1 == o2)
						continue;

					Object& obj1 = objects[o1];
					Object& obj2 = objects[o2];

					float d2 = pow(obj2.pos.distance(obj1.pos), 2);
					if (d2 < 0.001)
						continue;
					
					float dist = obj1.pos.distance(obj2.pos);
					if (obj1.r + obj2.r > dist)
					{
						//std::cout << objects[o1].r + objects[o2].r << " " << objects[o1].pos.distance(objects[o2].pos) << std::endl;
						//objects[o2].Move(objects[o2].v * -dTime);

						constexpr float energyLossK = 0.5f;

						math::vec2 dir = obj2.pos - obj1.pos;
						math::vec2 dirNorm = math::normalize(obj2.pos - obj1.pos);

						if (obj1.v.magnitude() != 0.0f)
						{
							if (obj1.m > obj2.m)
							{
								objects[o1].v -= dirNorm * sqrt(obj2.m * pow(obj2.v.magnitude() * (1 - energyLossK) * obj1.v.cos(dir), 2) / obj1.m);// *pow(obj2.v.magnitude() / obj1.v.magnitude(), 2);
							}
							else
							{
								objects[o1].v -= dirNorm * obj1.v.magnitude() * obj1.v.cos(dir) * (2 - energyLossK);
							}
						}
						//obj1.Move(obj1.v * -2 * dTime);

						//objects[o2].v -= dirNorm * -1 * objects[o2].v.magnitude() * objects[o2].v.cos(dir * -1) * 2.0;
					}
					else
					{
						//if(objects[o1].r + objects[o2].r + 0.1 < dist)
						a -= math::normalize(objects[o2].pos - objects[o1].pos) * objects[o2].m / d2 * G1;
					}
				}

				a = {0.0, -1e-5};

				math::vec2 j = (a - objects[o1].a) / dTime;
				math::vec2 dPos = j / 6.0 * pow(dTime, 3) + objects[o1].a / 2.0 * pow(dTime, 2) + objects[o1].v * dTime; //d(t) = j / 6.0 * t^3 + a0 / 2.0 * t^2 + v0 * t + d0
				objects[o1].Move(dPos);
				objects[o1].v += j / 2.0 * pow(dTime, 2) + objects[o1].a * dTime; //v(t) = j / 2.0 * t^2 + a0 * t + v0
				objects[o1].a = a;		//a(t) = j * t + a0


				if (objects[o1].pos.y > 10.0)
				{
					objects[o1].v.x *= 1.0;
					objects[o1].v.y *= -1.0;
					objects[o1].MoveTo({ objects[o1].pos.x, 10.0f });
				}

				if (objects[o1].pos.y < -10.0)
				{
					objects[o1].v.x *= 1.0;
					objects[o1].v.y *= -1.0;
					objects[o1].MoveTo({ objects[o1].pos.x, -10.0f });

					//if (objects[o1].v.magnitude() < 1e-3)
					//	objects[o1].v = { 0.0, 0.0 };
				}

				if (objects[o1].pos.x > 15.0)
				{
					objects[o1].v.x *= -1.0;
					objects[o1].v.y *= 1.0;
					objects[o1].MoveTo({ 15.0, objects[o1].pos.y });
				}

				if (objects[o1].pos.x < -15.0)
				{
					objects[o1].v.x *= -1.0;
					objects[o1].v.y *= 1.0;
					objects[o1].MoveTo({ -15.0, objects[o1].pos.y });
				}
			}
		}
	}

	void AddObject(math::vec2 size, math::vec2 pos, float mass, math::vec2 speed = { 0.0f, 0.0f })
	{
		Object& o = objects.emplace_back();
		o.mesh.geometry = geo;
		o.mesh.material = &mat;
		m_scene.Add(&objects.back().mesh);
		o.Scale(size);
		o.Move(pos);
		o.m = mass;
		o.v = speed;
		o.r = size.x;
	}
};