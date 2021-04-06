#pragma once
#include "VR.h"

namespace VR
{
	class Renderer
	{
	public:
		void Run();

	protected:
		Renderer();
		~Renderer();
		
		//inline void SetIndicesPtr(std::vector<unsigned int>* indices_ptr) { m_indices = indices_ptr; }
		inline void SetClearColor(math::vec4 color) { m_clearColor = color; }

		inline void GetWindowSize(int* width, int* height) const { glfwGetWindowSize(Context::Get()->window, width, height); }

		virtual void OnUpdate(float dTime) = 0;

		void Render(const Scene& scene, const Camera& camera);

	private:
		void Update();

	private:
		Timer m_timer;
		math::vec4 m_clearColor;
	};
}