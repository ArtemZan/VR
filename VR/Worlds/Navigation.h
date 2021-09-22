#pragma once
#include "VR.h"

using namespace VR;

class Navigation : public World
{
	std::vector<Object2D> buttons;

public:
	Navigation()
	{
		AddButton(math::vec2(0.1, 0.1), math::vec2(-0.9, 0.9), { 0.f, 1.f, 0.f, 0.f });

		AddButton(math::vec2(0.1, 0.1), math::vec2(-0.7, 0.9), { 0.0f, 0.6f, 0.4f, 0.f });

		for (Object2D& b : buttons)
		{
			m_scene.Add(&b.mesh);
		}
	}

	~Navigation()
	{
	}

	void OnAttach() override
	{
		AddHandler(this);

		Render();
	}

	void OnDetach() override
	{
		std::cout << "Detached\n";
	}


	void OnMouseDown(int button, int mods) override
	{
		std::cout << "Mouse down\n";

		IO* io = IO::Get();

		for (int i = 0; i < buttons.size(); i++)
		{
			math::vec2 mPos = io->MousePos();
			
			math::vec2i wSize = io->WindowSize();
			mPos.x -= wSize.width / 2;
			mPos.x /= wSize.width / 2;
			mPos.y = wSize.height / 2 - mPos.y;
			mPos.y /= wSize.height / 2;

			bool inside = false;

			math::vec2 btnPos = buttons[i].Pos();
			math::vec2 btnSize = buttons[i].Size();
			if (btnPos.x - btnSize.x / 2 < mPos.x &&
				btnPos.x + btnSize.x / 2 > mPos.x &&
				btnPos.y - btnSize.x / 2 < mPos.y &&
				btnPos.y + btnSize.y / 2 > mPos.y)
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
		Render();
	}

	void OnUpdate(float dTime) override
	{
		
	}

	void AddButton(const math::vec2& size, const math::vec2& pos, const math::vec4& color)
	{
		buttons.emplace_back();

		buttons.back().mesh.SetColor(color);
		buttons.back().Rect(size);
		buttons.back().Move(pos);
	}
};

