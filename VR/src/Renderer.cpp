#include "pch.h"
#include "Renderer.h"

namespace VR
{
	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::Run()
	{
		while (!glfwWindowShouldClose(Context::Get()->window))
		{
			Update();
		}
	}

	void Renderer::Render(const Scene& scene, const Camera& camera)
	{
		GLCall(glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		for (const Scene::Objects& objects : scene.objects)
		{
			
		}
		//GLCall(glDrawElements(GL_TRIANGLES, m_indices->size(), GL_UNSIGNED_INT, m_indices->data()));


		glfwSwapBuffers(Context::Get()->window);
	}

	void Renderer::Update()
	{
		OnUpdate(m_timer.Update());

		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}