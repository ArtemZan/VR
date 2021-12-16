#pragma once

using namespace VR;

class Pendulum : public World
{
	Mesh2D rect;
	Mesh2D string;
	Mesh2D Fstring;
	Mesh2D gravity;
	Mesh2D force;
	Camera2D camera;

	math::vec2 pos = { -1.0, -0.0 };
	math::vec2 v;
	math::vec2 a = {0.0, -1.0};

public:
	Pendulum()
		:camera(1, { 0, 0, 2 }, fit_types::CENTER)
	{		
		rect->GetGeometry().CreateRect(math::vec2( 1.0, 1.0 ));
		rect->SetColor(math::vec4(0.0, 1.0, 0.0, 1.0));
		rect->MoveTo(pos);

		force->GetGeometry().CreateLine({ 0.0, 0.0 }, rect->GetPos(), 0.1, 0, 1);
		Fstring->GetGeometry().CreateLine({ 0.0, 0.0 }, rect->GetPos(), 0.1, 0, 1);
		gravity->GetGeometry().CreateLine({ 0.0, 0.0 }, rect->GetPos(), 0.1, 0, 1);

		string->GetGeometry().CreateLine({ 0.0, 0.0 }, rect->GetPos(), 0.01, 0, 1);

		m_scene.Add(force);
		//m_scene.Add(Fstring);
		m_scene.Add(string);
		//m_scene.Add(gravity);
		m_scene.Add(rect);
	}

	void OnAttach() override
	{
		AddHandler(this);
		SetCamera();

		SetClearColor({ 0.3, 0.1, 0.2, 1.0 });
	}

	void SetCamera()
	{
		const IO* io = IO::Get();

		const math::vec2 wSize = io->WindowSize();

		camera.SetAspectRatio(wSize.x / wSize.y);
		string->GetMaterial().SetShaderUniform("transform", camera.View());
		force->GetMaterial().SetShaderUniform("transform", camera.View());
		rect->GetMaterial().SetShaderUniform("transform", camera.View());
	}

	void OnUpdate(float dTime) override
	{
		SetCamera();
		m_scene.Render();

		MustUpdate();

		rect->MoveTo(pos);

		math::vec2 Fs = math::normalize(-pos) * (math::vec2(0, -1).dot(math::normalize(pos)) + v.dot(v));
		math::vec2 G = math::vec2(0.0, -1.0);

		string->GetGeometry().CreateLine({ 0.0, 0.0 }, pos, 0.01, 0, 1);
		string->SetColor({1.0, 1.0, 1.0, 1.0});

		/*gravity->GetGeometry().CreateLine(pos, pos + G, 0.01, 0, 1);
		gravity->SetColor({ 0.0, 0.0, 1.0, 1.0 });

		Fstring->GetGeometry().CreateLine(pos, pos + Fs, 0.01, 0, 1);
		Fstring->SetColor({ 0.0, 0.0, 1.0, 1.0 });*/

		force->GetGeometry().CreateLine(pos, pos + Fs + G, 0.01, 0, 1);
		force->SetColor({ 1.0, 1.0, 0.0, 1.0 });




	}

	void OnPhysicsUpdate(float dTime) override {
		dTime /= 10000;

		math::vec2 Fs = math::normalize(-pos) * (math::vec2(0, -1).dot(math::normalize(pos)) + v.dot(v));
		math::vec2 G = math::vec2(0.0, -1.0);

		a = G + Fs;
		v += a * dTime;
		pos += v * dTime;
	}
};