#include "pch.h"
#include "Context.h"

namespace VR
{
	Context* Context::context;

	Context::Context(int window_width, int window_height, const char* title)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		if (glfwInit() == GLFW_FALSE)
		{
			std::cout << "Couldn't init glfw\n";
		}

		window = glfwCreateWindow(window_width, window_height, title, nullptr, nullptr);

		if (window == nullptr)
		{
			std::cout << "Couldn't create window!\n";
		}

		glfwMakeContextCurrent(window);

		if (GLenum err = glewInit())
		{
			std::cout << "Failed to initialize glew: " << glewGetErrorString(err) << "\n";
		}

		GLCall(glEnable(GL_DEPTH_TEST));

		GLCall(glEnable(GL_CULL_FACE));
		GLCall(glCullFace(GL_FRONT));

		//GLCall(glEnable(GL_BLEND));
		//GLCall(glBlendFunc())
	}

	Context::~Context()
	{
		glfwTerminate();
	}
}