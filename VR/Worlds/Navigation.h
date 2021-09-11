#pragma once
#include "VR.h"

using namespace VR;

class Navigation : public World
{
	GUIMaterial btnMat;
	std::list<Mesh> meshes;

	struct Button
	{
		Button(math::vec2 pos, math::vec2 size)
			:pos(pos), size(size)
		{

		}
		math::vec2 pos;
		math::vec2 size;
	};

	std::vector<Button> buttons;

public:
	int link = -1;

	Navigation()
	{
		btnMat.color = { 0.0, 1.0, 0.0, 0.0 };
		AddButton({ 0.1, 0.1 }, { -0.9, 0.9 }, &btnMat);

		btnMat.color = {0.2, 0.8, 0.0, 0.0};
		AddButton({ 0.1, 0.1 }, { -0.7, 0.9 }, &btnMat);

		btnMat.color = { 0.4, 0.6, 0.0, 0.0 };
		AddButton({ 0.1, 0.1 }, { -0.5, 0.9 }, &btnMat);

		btnMat.color = { 0.6, 0.4, 0.0, 0.0 };
		AddButton({ 0.1, 0.1 }, { -0.3, 0.9 }, &btnMat);

		btnMat.color = { 0.8, 0.2, 0.0, 0.0 };
		AddButton({ 0.1, 0.1 }, { -0.1, 0.9 }, &btnMat);
	}

	~Navigation()
	{
	}

	void OnAttach() override
	{
		AddHandler(this);

		Render();
	}

	void OnMouseDown(int button, int mods) override
	{
		std::cout << "Mouse down\n";

		IO* io = IO::Get();

		for (int i = 0; i < meshes.size(); i++)
		{
			math::vec2 mPos = io->MousePos();
			
			math::vec2i wSize = io->WindowSize();
			mPos.x -= wSize.width / 2;
			mPos.x /= wSize.width / 2;
			mPos.y = wSize.height / 2 - mPos.y;
			mPos.y /= wSize.height / 2;

			bool inside = false;


			if (buttons[i].pos.x < mPos.x &&
				buttons[i].pos.x + buttons[i].size.x > mPos.x &&
				buttons[i].pos.y < mPos.y &&
				buttons[i].pos.y + buttons[i].size.y > mPos.y)
			{
				link = i;
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

	void AddButton(const math::vec2& size, const math::vec2& pos, Material* material)
	{
		meshes.emplace_back(*material, Geometry());
		buttons.emplace_back(pos, size);

		m_scene.AddBox(size, material, &meshes.back());
		meshes.back().Move(pos + size / 2.0f);
	}
};

