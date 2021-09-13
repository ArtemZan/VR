#pragma once

using namespace VR;

constexpr float G = 6.6708e-11;

class SolarSystem : public World
{
	math::mat4 proj;
	math::mat4 view;
	math::mat4 mvp;

	GUIMaterial btnMat;
	Object2D button;

	Object3D light;


	struct Body
	{
		Body(const math::vec3& pos, const math::vec3& velocity, float diameter, float mass, const Object3D& object)
			:pos(pos), v(velocity), diameter(diameter), mass(mass), object(object)
		{

		}
		math::vec3 pos; // 1e6 km
		math::vec3 v;	// 1e6 km/s
		math::vec3 a;	// 1e6 km/s2
		float diameter; // 1e6 km
		float mass;		// 1e18 kg
		Object3D object;
	};

	std::vector<Body> objects;

	MeshLoader loader;

	float timeWarp = 1.0;
public:

	SolarSystem()
		:button(btnMat)
	{

		IO* io = IO::Get();
		math::vec2i wSize = io->WindowSize();

		proj = math::perspective(1.f, float(wSize.width) / wSize.height, 1.0, 1000.0f);

		m_camera.SetPosition(math::vec3(0.0, 0.0, 50));
		m_camera.SetRotation(math::vec3(0.0, 0.0, -1.0));



		button.mesh.material.SetColor({ 1.0, 1.0, 0.0, 1.0 });

		button.Rect({ 0.1, 0.1 });
		button.MoveTo({ -0.9, 0.9 });
		m_scene.Add(&button.mesh);

		//objects.reserve(5);


		loader.Load("res/monkey.obj");

		Material mat = loader.GetMaterial();
		const std::vector<float>& vertices = loader.GetVertices();
		const std::vector<uint32_t>& indices = loader.GetIndices();

		mat.SetShaderUniform("ambientLightColor", math::vec3(0.3, 0.3, 0.0));
		mat.SetShaderUniform("diffuseLight.color", math::vec3(1.0, 1.0, 1.0));
		mat.SetShaderUniform("diffuseLight.position", math::vec3(5.0, 2.0, 3.0));
		mat.SetShaderUniform("mvp", proj);

		mat.SetColor({ 1.0, 1.0, 1.0, 0.0 });

		Object3D myobj(mat);
		
		objects.push_back(Body(math::vec3(0.0, 0.0, 0.0), math::vec3(0.0, 0.0, 0.0), 0.695 * 2, 1'988'500e6, myobj));
		objects.back().object.Shape((uint8_t*)vertices.data(), vertices.size() * 4, indices.data(), indices.size());
		//objects.back().object.Scale(math::vec3(1));
		m_scene.Add(&objects.back().object.mesh);

		light.mesh.material.SetColor({ 1.0, 1.0, 1.0, 1.0 });
		light.Cube(0.5);
		light.MoveTo(math::vec3(5.0, 2.0, 3.0));
		m_scene.Add(&light.mesh);

		
		//loader.Load("res/sphere.obj", &planetMat);

		//AddObject(loader.mesh, { 0.3, 0.3, 0.3, 0.0 }, { 57.9, 0.0, 0.005 }, 328'500, 4.879e-3, { 0.0, 0.0, 0.0 });
		//AddObject(loader.mesh, { 0.3, 0.3, 0.3, 0.0 }, { 57.9, 0.0, -0.005 }, 328'500, 4.879e-3, {0.0, 0.0, 0.0 });
		//AddObject(loader.mesh, { 0.3, 0.3, 0.3, 0.0 }, { 57.9, 0.0, 0.0 }, 328'500, 4.879e-2, { 0.0, 0.0, -47.4e-6 });
		//AddObject(loader.mesh, { 0.9, 0.6, 0.4, 0.0 }, { 108.2, 0.0, 0.0 }, 4'870'000, 12.104e-2, { 0.0, 0.0, -35.0e-6 });
		//AddObject(loader.mesh, { 0.3, 0.6, 0.9, 0.0 }, { 149.6, 0.0, 0.0 }, 5'970'000, 12.756e-2, { 0.0, 0.0, -29.8e-6 });
		//AddObject(loader.mesh, { 0.3, 0.3, 0.3, 0.0 }, { 149.6f, (float)sin(5.0 / 180.0 * 3.14) * 0.362f, -(float)cos(5.0 / 180.0 * 3.14) * 0.362f }, 73'420.0f, 1.737e-2, { -1.082e-6f, 0.0f, -29.8e-6f });

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
		
		//planetMat.shader->Bind();
		//planetMat.shader->SetUniform("ambientLightColor", 0.1, 0.1, 0.1);
		//planetMat.shader->SetUniform("diffuseLight.color", 1.0, 1.0, 0.8);
	}

	~SolarSystem()
	{
	}

	void OnAttach() override
	{
		AddHandler(this);
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

		std::cout << "Mouse down in solar system (" << mX << " : " << mY << ")\n";

		math::vec2 btnPos = this->button.Pos();
		math::vec2 btnSize = this->button.Size();

		if (btnPos.x - btnSize.x / 2 < mX &&
			btnPos.x + btnSize.x / 2 > mX &&
			btnPos.y - btnSize.y / 2 < mY &&
			btnPos.y + btnSize.y / 2 > mY)
		{
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
		Input(dTime);

		mvp = proj * m_camera.view;

		//planetMat.shader->Bind();
		//planetMat.shader->SetUniform("diffuseLight.position", 0.0, 0.0, 0.0);

		//sunMat.shader->Bind();
		//sunMat.shader->SetUniform("mvp", mvp);
		//planetMat.shader->Bind();
		//planetMat.shader->SetUniform("mvp", mvp);
		for (Body& body : objects)
		{
			body.object.mesh.material.SetShaderUniform("mvp", mvp);
		}

		light.mesh.material.SetShaderUniform("mvp", mvp);

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

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_M) == GLFW_PRESS 
			&& (glfwGetKey(Context::Get()->window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS
			|| glfwGetKey(Context::Get()->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS))
		{
			m_camera.SetPosition(objects[1].pos * 1e3);
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_V) == GLFW_PRESS 
			&& (glfwGetKey(Context::Get()->window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS
			|| glfwGetKey(Context::Get()->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS))
		{
			m_camera.SetPosition(objects[2].pos * 1e3);
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_E) == GLFW_PRESS 
			&& (glfwGetKey(Context::Get()->window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS
			|| glfwGetKey(Context::Get()->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS))
		{
			m_camera.SetPosition(objects[3].pos * 1e3);
		}
		
		if (glfwGetKey(Context::Get()->window, GLFW_KEY_EQUAL) == GLFW_PRESS)
		{
			timeWarp *= 2.0;
		}

		if (glfwGetKey(Context::Get()->window, GLFW_KEY_MINUS) == GLFW_PRESS)
		{
			timeWarp /= 2.0;
		}
	}

	void AddObject(const Mesh& mesh, const math::vec4 color, const math::vec3& position, float mass, float diameter, const math::vec3& velocity = {})
	{
		/*objects.emplace_back(position, velocity, diameter, mass, mesh);
		planetMat.color = color;
		m_scene.Add(&objects.back().mesh);
		objects.back().mesh.Scale(math::vec3(1.0, 1.0, 1.0) * diameter * 0.5 * 1e3, { 0.0, 0.0, 0.0 });
		objects.back().mesh.Move(position * 1e3);*/
	}
};

