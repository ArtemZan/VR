#include "pch.h"
#include "VR.h"

namespace VR
{
	IO* IO::m_io;

	IO::IO()
	{
		glfwGetWindowSize(Context::m_window.m_window, &windowSize.width, &windowSize.height);
	}

	IO::~IO()
	{
		if (m_io)
		{
			delete m_io;
		}
	}

	void IO::Init()
	{
		if (m_io == nullptr)
		{
			m_io = new IO;
		}

		Events::AddHandler(m_io);
	}

	IO* IO::Get()
	{
		if (m_io == nullptr)
		{
			std::cout << "Error: attempt to access IO before IO::Init()\n";
		}

		return m_io;
	}

	void IO::OnMouseDown(GLint button, GLint mods)
	{
	}

	void IO::OnMouseMove(const math::vec2& pos)
	{
		mousePos = pos;
	}

	void IO::OnMouseUp(GLint button, GLint mods)
	{
	}

	void IO::OnScroll(const math::vec2& offset)
	{
	}

	void IO::OnKeyDown(GLint key, GLint mods)
	{
	}

	void IO::OnKeyUp(GLint key, GLint mods)
	{
	}

	void IO::OnChar(GLuint character)
	{
	}

	void IO::OnWindowClose()
	{
	}

	void IO::OnWindowResize(int x, int y)
	{
		windowSize = math::vec2i(x, y);
	}

	void IO::OnWindowMove(int x, int y)
	{
	}

}