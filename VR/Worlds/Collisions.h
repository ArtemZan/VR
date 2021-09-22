#pragma once

using namespace VR;

struct Collisions : public World
{
private:
	Object2D button;

	Object2D line;
	Object2D box;


	void OnAttach() override
	{
		AddHandler(this);
		Render();
	}

	void OnDetach() override
	{
	}

	void OnMouseDown(int bc, int mods) override
	{
		if (button.IsHovered())
		{
			link = 0;
			Detach();
		}
	}

	void OnUpdate(float dTime) override
	{


		//MustUpdate();
	}

public:

	Collisions()
	{
		button.mesh.SetColor({ 0.0, 1.0, 0.0, 1.0 });
		button.Rect(0.1f);
		button.MoveTo({ -0.9, 0.9 });
		m_scene.Add(&button.mesh);

		line.mesh.SetColor({ 1.0, 0.8, 0.6, 0.0 });
		line.Line({ 0, 0.0 }, { 0.5, 0.5 }, 0.02, 0.1, 5);
		line.Move({ -0.5, -0.5 });
		m_scene.Add(&line.mesh);
	}
};