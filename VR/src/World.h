#pragma once

namespace VR
{



	class World : public Events
	{
	public:
		void Run();

		static World* currentWorld;

		void WindowResized(int width, int height);

		

	protected:
		World();

		inline void SetClearColor(math::vec4 color) 
		{ 
			m_clearColor = color;
			GLCall(glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a));
		}

		void Render();

		void Detach();
		inline void MustUpdate() { m_updateNow = true; }

		virtual void OnUpdate(float dTime) = 0;
		virtual void OnPhysicsUpdate(float dTime) {};
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnWindowResize(int width, int height) override;
		virtual void OnWindowClose() override;

		Scene m_scene;
		Camera m_camera;

	private:
		void Update();

		bool m_attached = false;
		bool m_updateNow = true;
		
		Timer m_timer;
		Timer m_fixedTimer;
		
		math::vec4 m_clearColor;

		std::thread physicsUpdate;
		std::mutex physicsUpdateMutex;
	};
}
