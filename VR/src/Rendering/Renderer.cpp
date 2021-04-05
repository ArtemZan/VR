#include "pch.h"
#include "Renderer.h"

namespace VR
{
	Renderer::Renderer(int window_width, int window_height, const char* title)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		if (glfwInit() == GLFW_FALSE)
		{
			std::cout << "Couldn't init glfw\n";
		}

		m_window = glfwCreateWindow(window_width, window_height, title, nullptr, nullptr);

		if (m_window == nullptr)
		{
			std::cout << "Couldn't create window!\n";
		}

		glfwMakeContextCurrent(m_window);

		if (GLenum err = glewInit())
		{
			std::cout << "Failed to initialize glew: " << glewGetErrorString(err) << "\n";
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
	}

	Renderer::~Renderer()
	{
		glfwTerminate();
	}

	void Renderer::Run()
	{
		while (!glfwWindowShouldClose(m_window))
		{
			Update();
		}
	}

	void Renderer::Update()
	{
		GLCall(glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		OnUpdate(m_timer.Update());
		if (m_indices != nullptr)
		{
			GLCall(glDrawElements(GL_TRIANGLES, m_indices->size(), GL_UNSIGNED_INT, m_indices->data()));
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(20));

		glfwSwapBuffers(m_window);

		glfwPollEvents();
	}
}