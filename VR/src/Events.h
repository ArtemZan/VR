#pragma once

namespace VR
{
	class Events
	{
		friend class Context;

	protected:
		Events();
		~Events();

	public:
		virtual void OnMouseDown(GLint button, GLint mods) {};
		virtual void OnMouseUp(GLint button, GLint mods) {};
		virtual void OnMouseMove(math::vec2 pos) {};
		virtual void OnScroll(math::vec2 offset) {};

		virtual void OnKeyDown(GLint key, GLint mods) {};
		virtual void OnKeyUp(GLint key, GLint mods) {};
		virtual void OnChar(GLuint character) {};

		virtual void OnWindowClose() {};
		virtual void OnWindowResize(int x, int y) {};
		virtual void OnWindowMove(int x, int y) {};


		virtual void OnDrop(const char** paths, size_t count) {}


		static void AddHandler(Events* handler);
		static void RemoveHandler(Events* handler);
		static void RemoveAllHandlers();

	private:
		static std::set<Events*> m_handlers;
		static std::set<Events*> m_nextHandlers;

		static void OnEvent();
		static void Init();
	};
}
