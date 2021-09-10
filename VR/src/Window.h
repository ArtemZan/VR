#pragma once

namespace VR
{
	struct WindowParameters
	{
		int width = 960;
		int height = 540;
		const char* title = "Window";
	};

	class Window
	{
		friend class Context;
	public:

		Window(const WindowParameters& params = {});
		~Window();

		void Create();

		WindowParameters params;

		GLFWwindow* m_window;
	private:
	};
}