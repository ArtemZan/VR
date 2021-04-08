#pragma once
class Renderer;

namespace VR
{
	class World
	{
	public:
		void Run();

	protected:
		World();

		inline void SetClearColor(math::vec4 color) 
		{ 
			m_clearColor = color;
			GLCall(glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a));
		}

		void Render();

		inline void Detach() { m_attached = false; }

		virtual void OnUpdate(float dTime) = 0;
		virtual void OnAttach() {};

		Scene scene;
		Camera camera;

	private:
		void Update();

		bool m_attached = false;
		Timer m_timer;
		math::vec4 m_clearColor;
	};
}
