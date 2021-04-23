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
