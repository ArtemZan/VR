#pragma once

namespace VR
{
	class IO : private Events
	{
	private:
		IO();
		~IO();

		void OnMouseDown(GLint button, GLint mods) override;
		void OnMouseMove(const math::vec2& pos) override;
		void OnMouseUp(GLint button, GLint mods) override;
		void OnScroll(const math::vec2& offset) override;

		void OnKeyDown(GLint key, GLint mods) override;
		void OnKeyUp(GLint key, GLint mods) override;
		void OnChar(GLuint character) override;

		void OnWindowClose() override;
		void OnWindowResize(int x, int y) override;
		void OnWindowMove(int x, int y) override;

		static IO* m_io;

		math::vec2 mousePos;
		math::vec2i windowSize;
	public:

		inline math::vec2 MousePos() const { return mousePos; }
		inline math::vec2i WindowSize() const { return windowSize; }

		static void Init();

		static IO* Get();
	};

}

