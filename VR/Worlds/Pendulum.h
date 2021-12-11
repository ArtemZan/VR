#pragma once

using namespace VR;

class Pendulum : public World
{
	Mesh2D rect;
	Mesh2D string;
	Mesh2D force;
	Camera2D camera;


	math::vec2 v;
	math::vec2 a;

public:
	Pendulum()
		:camera(1, { 0, 0, 5 }, fit_types::CENTER)
	{
		rect.SetColor(math::vec4(0.0, 1.0, 0.0, 0.0));
		rect.Square(0.5);
		rect.MoveTo({ -0.6, -0.8 });

		string.SetColor({ 0.0, 0.0, 0.0, 1.0 });
		string.Line({ 0.0, 0.0 }, rect.Pos(), 0.1, 0, 1);

		force.SetColor({ 1.0, 0.0, 0.0, 1.0 });
		force.Line({ 0.0, 0.0 }, rect.Pos(), 0.1, 0, 1);

		m_scene.Add(force);
		//m_scene.Add(string);
		m_scene.Add(rect);
	}

	void OnAttach() override
	{
		AddHandler(this);
		SetCamera();
		
		SetClearColor({ 1, 1, 1, 1.0 });
	}

	void SetCamera()
	{
		const IO* io = IO::Get();

		const math::vec2 wSize = io->WindowSize();

		camera.SetAspectRatio(wSize.x / wSize.y);
		rect.GetMaterial().SetShaderUniform("transform", camera.View());
		force.GetMaterial().SetShaderUniform("transform", camera.View());
	}

	void OnUpdate(float dTime) override
	{				
		SetCamera();
		m_scene.Render();

		MustUpdate();

		//string.Line({ 0.0, 0.8 }, rect.Pos(), 0.01, 0, 1);
		force.Line(rect.Pos(), rect.Pos() + a, 0.01, 0, 3);

		math::vec2 pos = rect.Pos();

		for (int i = 0; i < 1; i++)
		{
			math::vec3 cross = math::cross(math::normalize(math::vec3(pos, 0)), math::vec3(0.f, -1.f, 0));
			float sin = -cross.z;
			a = math::vec2(0, -1.0);
			a += math::normalize(-pos) * (a.dot(math::normalize(pos)) * pos.magnitude());
			v += a * dTime * 0.001;
			pos += v * dTime * 0.001;

			//std::cout << sin << std::endl;
		}

		//std::cout << a << " " << v << " " << pos << std::endl;

		rect.MoveTo(pos);
	}

	void OnPhysicsUpdate(float dTime) override {
	}
};