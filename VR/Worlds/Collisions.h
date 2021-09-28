#pragma once

using namespace VR;

struct Collisions : public World
{
private:
	Camera2D camera;

	Mesh2D button;
	Mesh2D rect;

	std::vector<Mesh2D> lines;

	std::vector<math::vec2> points;

	Mesh2D curve;

	Mesh2D bezier;

	float time = 0;


	const float amplitude = rand() % 100 / 100.f;
	const float freq = (rand() % 100 - 50) / 10 + 5;


	void OnAttach() override
	{
		AddHandler(this);
		m_scene.Render();
	}

	void OnDetach() override
	{
	}

	void OnMouseDown(int bc, int mods) override
	{
		//m_scene.Delete(button);

		if (button.IsHovered(camera.View()))
		{
			link = 0;
			Detach();
		}
	}

	void OnWindowResize(int w, int h) override
	{
		glViewport(0, 0, w, h);
		SetAspectRatio();
	}

	void OnUpdate(float dTime) override
	{
		IO* io = IO::Get();

		time += dTime / 1000.0;

		const int points_count = points.size();


		for (int i = 0; i < points_count; i++)
		{
			points[i].y = sin(time * 2.0 + math::PI * freq * float(i) / points_count) * amplitude;
		}

		curve.Curve(points, 0.002, 0);

		m_scene.Render();

		MustUpdate();
	}

	void OnScroll(const math::vec2& scroll) override
	{
		if (camera.Pos().z - scroll.y > 0)
		{
			camera.Move({ 0.0, 0.0, -scroll.y });
		}

		SetAspectRatio();
	}

	void SetAspectRatio()
	{
		IO* io = IO::Get();
		math::vec2 wSize = io->WindowSize();

		camera.SetAspectRatio(wSize.x / wSize.y);

		button.GetMaterial().SetShaderUniform("transform", camera.View());

		m_scene.Render();
	}

public:

	Collisions()
		:camera(1.0, {}, fit_types::SCREEN)
	{
		camera.SetPosition({ 0.0, 0.0, 1.0 });

		SetAspectRatio();

		button.SetColor({ 0.0, 1.0, 0.0, 1.0 });
		button.Rect(0.1f);
		button.MoveTo(math::vec2( -0.9, 0.9 ));
		m_scene.Add(button);

		/*constexpr int lines_count = 100;

		for (int i = 0; i < lines_count; i++)
		{
			lines.emplace_back();
			lines.back().SetColor({ float(i) / lines_count, 1.f - float(i) / lines_count, 0.5, 0.0 });
			lines.back().Line(
				{ 2.f * float(i) / lines_count - 1, sin(float(i) / lines_count * 10)}, 
				{ 2.f * float(i + 1.f) / lines_count - 1, sin(float(i + 1) / lines_count * 10) }, 0.002, 0, 1);
		}

		for (Mesh2D& line : lines)
		{
			m_scene.Add(&line);
		}*/

		constexpr int points_count = 1000;

		const float amplitude = rand() % 100 / 100.f;
		const float freq = (rand() % 100 - 50) / 10 + 5;

		points.reserve(points_count);

		for (int i = 0; i < points_count; i++)
		{
			points.emplace_back(2.f * float(i) / points_count - 1, sin(math::PI * freq * float(i) / points_count) * amplitude);
		}

		curve.SetColor({ 1.f, 1.f, 0.5, 0.0 });
		curve.Curve(points, 0.002, 0);
		m_scene.Add(curve);

		bezier.SetColor({ 1.0, 0.0, 0.0, 0.0 });

		std::vector<math::vec2> bezier_points;
		bezier_points.emplace_back(-0.5, 0);
		bezier_points.emplace_back(0, 0.5);
		bezier_points.emplace_back(0.5, 0);
		bezier_points.emplace_back(0, -0.5);
		bezier_points.emplace_back(-0.5, 0);
		bezier.BezierCurve(bezier_points, 0.005, 100, 0);
		m_scene.Add(bezier);

		/*for (Mesh2D& line : lines)
		{
			m_scene.Add(&line);
		}*/




		//rect.Rect({ 2.0, 2.0 });
		//rect.MoveTo(0);
		//rect.Line(math::vec2(-1, -1), { 1.f, 1.f }, 0.01, 0.01f);
		//rect.SetColor({ 1.0, 0.0, 1.0, 1.0 });
		//m_scene.Add(&rect);
	}
};