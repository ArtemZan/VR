#include "pch.h"
#include "VR.h"

namespace VR
{
	Window::Window(const WindowParameters& params)
		:params(params)
	{
		
	}

	Window::~Window()
	{

	}

	void Window::Create()
	{
		m_window = glfwCreateWindow(params.width, params.height, params.title, nullptr, nullptr);

		if (m_window == nullptr)
		{
			std::cout << "Couldn't create window!\n";
		}

		glfwMakeContextCurrent(m_window);
	}
}