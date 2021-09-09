#pragma once

namespace VR
{
	class Context
	{
		Context(int window_width, int window_height, const char* title);
		~Context();

	public:
		static void Create(int window_width, int window_height, const char* title)
		{
			if (!context)
			{
				context = new Context(window_width, window_height, title);
			}
		}

		static void Destroy() { delete context; }

		static inline Context* const Get()
		{
			return context;
		}

		GLFWwindow* window;

	private:
		static Context* context;

		//Setings
		bool cull_face;
		GLint culled_face;
	};
}