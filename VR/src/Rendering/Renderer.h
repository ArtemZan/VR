#pragma once
#include "../VR.h"

namespace VR
{
	class Renderer
	{
	public:
		Renderer(int window_width, int window_height, const char* title);
		~Renderer();

		void Run();

	protected:
		inline void SetIndicesPtr(std::vector<unsigned int>* indices_ptr) { m_indices = indices_ptr; }
		inline void SetClearColor(math::vec4 color) { m_clearColor = color; }

		inline void GetWindowSize(int* width, int* height) const { glfwGetWindowSize(m_window, width, height); }

		virtual void OnUpdate(float dTime) = 0;

	private:
		void Update();

	private:
		GLFWwindow* m_window;
		Timer m_timer;
		std::vector<unsigned int>* m_indices;
		math::vec4 m_clearColor;
	};
}