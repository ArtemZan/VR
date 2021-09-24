#pragma once
#include "VR.h"

using namespace VR;

class Navigation : public World
{
	std::vector<Mesh2D> buttons;

	Camera2D camera;

public:
	Navigation()
	{
		AddButton(math::vec2(0.1, 0.1), math::vec2(-0.9, 0.9), { 1.0, 1.0, 0.0, 0 });

		AddButton(math::vec2(0.1, 0.1), math::vec2(-0.7, 0.9), { 0.0f, 0.6f, 0.4f, 0.f });

		for (Mesh2D& b : buttons)
		{
			m_scene.Add(&b);
		}
	}

	~Navigation()
	{
	}

	void OnAttach() override
	{
		AddHandler(this);

		camera.SetPosition({ 0.0, 0.0, 1.0 });
		SetAspectRatio();
	}

	void OnDetach() override
	{
		std::cout << "Detached\n";
	}


	void SetAspectRatio()
	{
		IO* io = IO::Get();
		math::vec2 wSize = io->WindowSize();

		camera.SetAspectRatio(wSize.x / wSize.y);

		for (Mesh2D& button : buttons)
		{
			button.material.SetShaderUniform("transform", camera.View());
		}


		Render();
	}

	void OnMouseDown(int button, int mods) override
	{
		std::cout << "Mouse down\n";

		IO* io = IO::Get();

		for (int i = 0; i < buttons.size(); i++)
		{
			if (buttons[i].IsHovered(camera.View()))
			{
				link = i + 1;
				std::cout << "Detaching...\n";
				Detach();
				break;
			}
		}
	}

	void OnWindowResize(int width, int height) override
	{
		glViewport(0, 0, width, height);
		SetAspectRatio();
	}

	void OnUpdate(float dTime) override
	{
		
	}

	void AddButton(const math::vec2& size, const math::vec2& pos, const math::vec4& color)
	{
		buttons.emplace_back();

		buttons.back().Rect(size);
		buttons.back().SetColor(color);
		buttons.back().Move(pos);
	}
};

