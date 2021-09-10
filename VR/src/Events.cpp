#include "pch.h"
#include "VR.h"
#include "Events.h"
#include "Context.h"

namespace VR
{
	std::set<Events*> Events::m_handlers;
	std::set<Events*> Events::m_nextHandlers;

	Events::Events()
	{
	}

	Events::~Events()
	{
		for (auto i = m_handlers.begin(); i != m_handlers.end(); i++)
		{
			if (*(i.operator->()) == this)
			{
				m_handlers.erase(i);
				break;
			}
		}
	}

	void Events::AddHandler(Events* handler)
	{
		m_nextHandlers.insert(handler);
	}

	void Events::RemoveHandler(Events* handler)
	{
		m_nextHandlers.erase(handler);
	}

	void Events::RemoveAllHandlers()
	{
		m_nextHandlers.clear();
	}

	void Events::OnEvent()
	{
		m_handlers = m_nextHandlers;
	}

	void Events::Init()
	{
		GLFWwindow* window = Context::m_window.m_window;

#define StartEvent OnEvent();\
		for (Events* handler : Events::m_handlers)

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, GLint button, GLint action, GLint mods) {
			StartEvent
			{
				switch (action)
				{
				case GLFW_PRESS:
				{
					handler->OnMouseDown(button, mods);
					break;
				}
				case GLFW_RELEASE:
				{
					handler->OnMouseUp(button, mods);
					break;
				}
				}
			}
		}
		);
		
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
			StartEvent
			{
				handler->OnMouseMove({(float)x, (float)y});
			}
			});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double x, double y) {
			StartEvent
			{
				handler->OnScroll({ (float)x, (float)y });
			}
			});

		glfwSetKeyCallback(window, [](GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods) {
			StartEvent
			{
				switch (action)
				{
				case GLFW_PRESS:
				{
					handler->OnKeyDown(key, mods);
					break;
				}
				case GLFW_RELEASE:
				{
					handler->OnKeyUp(key, mods);
					break;
				}
				}
			}
			});

		glfwSetCharCallback(window, [](GLFWwindow* window, GLuint character) {
			StartEvent
			{
				handler->OnChar(character);
			}
			});


		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
			StartEvent
			{
				handler->OnWindowClose();
			}
			});

		glfwSetWindowPosCallback(window, [](GLFWwindow* window, int x, int y) {
			StartEvent
			{
				handler->OnWindowMove(x, y);
			}
			});

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int x, int y) {
			StartEvent
			{
				handler->OnWindowResize(x, y);
			}
			});
		

		glfwSetDropCallback(window, [](GLFWwindow* window, GLint count, const char** paths) {
			StartEvent
			{
				handler->OnDrop(paths, count);
			}
			});
	}
}