#pragma once

namespace VR
{
	struct Object3D
	{
		Mesh mesh;
		math::vec3 pos;
		math::vec3 scale;

		inline void Move(const math::vec3& bias)
		{
			mesh.Move(bias);
			pos += bias;
		}

		inline void MoveTo(const math::vec3& new_pos)
		{
			mesh.Move(new_pos - pos);
			pos = new_pos;
		}

		inline void Scale(const math::vec3& scale)
		{
			mesh.Scale(scale, pos);
			this->scale *= scale;
		}
	};

	struct Object2D
	{
		Mesh mesh;
		math::vec2 pos;
		math::vec2 scale;

		Object2D()
			:scale({1.0, 1.0})
		{

		}

		inline void Move(const math::vec2& bias)
		{
			mesh.Move(bias);
			pos += bias;
		}

		inline void MoveTo(const math::vec2& new_pos)
		{
			mesh.Move(new_pos - pos);
			pos = new_pos;
		}

		inline void Scale(const math::vec2& scale)
		{
			mesh.Scale(scale, pos);
			this->scale *= scale;
		}
	};


	class World
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

		virtual void OnUpdate(float dTime) = 0;
		virtual void OnPhysicsUpdate(float dTime) {};
		virtual void OnAttach() {}
		virtual void OnWindowResize() {}

		Scene m_scene;
		Camera m_camera;

		float m_wWidth;
		float m_wHeight;

	private:
		void Update();
		bool m_attached = false;
		
		Timer m_timer;
		Timer m_fixedTimer;
		
		math::vec4 m_clearColor;

		std::thread physicsUpdate;
		std::mutex physicsUpdateMutex;
	};
}
