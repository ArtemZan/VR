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

	void World::Render()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		for (Scene::Batch& batch : m_scene.batches)
		{
			batch.meshes[0]->material.BindShader();
			batch.meshes[0]->material.SetShaderUniforms();

			batch.vb.Bind();
			batch.vb.Data(batch.vertices.size(), batch.vertices.data());
			for (int i = 0; i < batch.vertices.size(); i+=4)
			{
				if (i % batch.meshes[0]->material.GetVertexSize() == 0)
				{
					std::cout << std::endl;
				}
				std::cout << std::setw(5) << *(float*)(&batch.vertices[i]) << " ";
			}
			batch.va.Bind();
			batch.va.AddBuffer(batch.meshes[0]->material.GetLayout());
			GLCall(glDrawElements(GL_TRIANGLES, batch.indices.size(), GL_UNSIGNED_INT, batch.indices.data()));
		}

		glfwSwapBuffers(Context::Get()->m_window.m_window);

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