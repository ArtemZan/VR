#pragma once

namespace VR
{
	namespace gl
	{
		//Reads texture file and creates GL texture
		class Texture
		{
		public:
			//Reads texture file
			Texture(const char* filepath);

			//Uses given data to create texture
			Texture(const unsigned char* src, size_t bpp, size_t width, size_t height);

			//Copy constructor
			Texture(const Texture& texture);

			//Texture(const Texture& texture);
			~Texture();

			//Tells GL to set this texture on given slot
			void Bind(unsigned int slot = 0) const;

			inline unsigned int GetID() const { return m_glID; }
			inline int GetBPP()			const { return m_BPP; }
			inline int GetWidth()		const { return m_width; }
			inline int GetHeight()		const { return m_height; }
		
		private:
			mutable bool	m_deleteTexture = true;
			int				m_BPP;
			int				m_width;
			int				m_height;
			GLuint			m_glID;
		};
	}
}
