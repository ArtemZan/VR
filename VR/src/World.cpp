#include "pch.h"
#include "VR.h"

namespace VR
{
	World* World::currentWorld;

	World::World()
	{

	}

	void World::OnWindowResize(int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void World::OnWindowClose()
	{
		Detach();
	}


	void World::Run()
	{
		currentWorld = this;
		link = -1;

		GLCall(glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a));


		/*glfwSetMouseButtonCallback(Context::Get()->m_window.m_window, [](GLFWwindow* window, int button, int action, int mode) {});

		glfwSetWindowSizeCallback(Context::Get()->m_window.m_window, [](GLFWwindow* window, int width, int height) {
			World::currentWorld->WindowResized(width, height);
			});*/

		std::cout << "Attaching\n";
		OnAttach();

		m_attached = true;

		m_timer.Update();
		/*m_fixedTimer.Update();

		physicsUpdate = std::thread([this]() {
			while (m_attached)
			{
				OnPhysicsUpdate(m_fixedTimer.Update());
			}
		});*/

		while (m_attached)
		{
			Update();
		}

		OnDetach();
	}


	void World::Detach()
	{
		m_attached = false;

		if(physicsUpdate.joinable())
			physicsUpdate.join();

		RemoveHandler(this);
	}

	void World::Update()
	{
		float dt = m_timer.Update();

		m_updateNow = false;

		OnUpdate(dt);

		if (m_updateNow)
		{
			glfwPollEvents();
		}
		else
		{
			glfwWaitEvents();
		}

		//std::cout << "Update\n";

		/*std::this_thread::sleep_for(std::chrono::microseconds(1'000'000 / 60'000 - int(dt * 1000)));
		if (dt > 1'000.0 / 60.0)
		{
			std::cout << "FPS: " << 1000.0 / dt << std::endl;
		}*/
	}
}