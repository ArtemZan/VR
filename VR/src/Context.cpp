#include "pch.h"
#include "VR.h"

namespace VR
{
	Context* Context::context;
	Window Context::m_window;

	Context::Context(int window_width, int window_height, const char* window_title)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		if (glfwInit() == GLFW_FALSE)
		{
			std::cout << "Couldn't init glfw\n";
		}

		m_window.params.width = window_width;
		m_window.params.height = window_height;
		m_window.params.title = window_title;
		m_window.Create();
		window = m_window.m_window;

		Events::Init();
		IO::Init();

		if (GLenum err = glewInit())
		{
			std::cout << "Failed to initialize glew: " << glewGetErrorString(err) << "\n";
		}

		GLCall(glEnable(GL_DEPTH_TEST));

		//GLCall(glEnable(GL_CULL_FACE));
		//GLCall(glCullFace(GL_BACK));

		//GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));

		GLCall(glDisable(GL_BLEND));
		//GLCall(glBlendFunc())
	}

	Context::~Context()
	{
		Material::shaders.clear();
		glfwTerminate(); //SOMETIMES doesn't link?
	}
}