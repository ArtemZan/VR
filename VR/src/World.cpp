#include "pch.h"
#include "VR.h"

namespace VR
{
	World* World::currentWorld;

	void World::WindowResized(int width, int height)
	{
		glViewport(0, 0, width, height);
		m_wWidth = width;
		m_wHeight = height;
		OnWindowResize();
	}

	World::World()
	{
		int width, height;
		glfwGetWindowSize(Context::Get()->window, &width, &height);
		m_wWidth = width;
		m_wHeight = height;
	}

	void World::Run()
	{
		currentWorld = this;

		GLCall(glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a));


		glfwSetMouseButtonCallback(Context::Get()->window, [](GLFWwindow* window, int button, int action, int mode) {});

		glfwSetWindowSizeCallback(Context::Get()->window, [](GLFWwindow* window, int width, int height) {
			World::currentWorld->WindowResized(width, height);
			});

		OnAttach();

		m_attached = true;

		m_timer.Update();
		m_fixedTimer.Update();

		physicsUpdate = std::thread([this]() {
			while (m_attached)
			{
				OnPhysicsUpdate(m_fixedTimer.Update());
			}
		});

		while (m_attached)
		{
			Update();
		}
	}

	void World::Render()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		for (const Scene::Batch& batch : m_scene.batches)
		{
			batch.shader->Bind();

			batch.vb.Bind();
			batch.vb.Data(batch.vertices.size(), batch.vertices.data());
			/*for (int i = 0; i < batch.vertices.size(); i+=4)
			{
				std::cout << *(float*)(&batch.vertices[i]) << std::endl;
			}*/
			batch.va.Bind();
			batch.va.AddBuffer(batch.attribLayout);
			GLCall(glDrawElements(GL_TRIANGLES, batch.indices.size(), GL_UNSIGNED_INT, batch.indices.data()));
		}

		glfwSwapBuffers(Context::Get()->window);

	}

	void World::Detach()
	{
		m_attached = false;

		if(physicsUpdate.joinable())
			physicsUpdate.join();
	}

	void World::Update()
	{
		float dt = m_timer.Update();

		OnUpdate(dt);

		glfwPollEvents();

		if (glfwWindowShouldClose(Context::Get()->window))
			Detach();

		std::this_thread::sleep_for(std::chrono::microseconds(1'000'000 / 60'000 - int(dt * 1000)));
		if (dt > 1'000.0 / 60.0)
		{
			std::cout << "FPS: " << 1000.0 / dt << std::endl;
		}
	}
}