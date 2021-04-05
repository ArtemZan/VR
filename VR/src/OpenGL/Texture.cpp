#include "pch.h"
#include "../VR.h"

namespace VR
{
	namespace gl
	{
		Texture::Texture(const char* filepath)
			: m_width(0), m_height(0), m_BPP(0), m_glID(0)
		{
			stbi_set_flip_vertically_on_load(1);

			//Pretty stupid
			std::string _filepath = std::string("..\\..\\..\\Unleashed\\res\\Textures\\") + filepath;
			std::ifstream file(_filepath);
			if (file.fail())
				_filepath = std::string("res\\Textures\\") + filepath;
			file.close();

			//Stbi library allows us to read image files
			unsigned char* buffer = stbi_load(_filepath.c_str(), &m_width, &m_height, &m_BPP, 4);

			if (buffer == nullptr)
			{
				std::cout << "Couldn't load texture \"" << filepath << "\"\n";
			}

			//Creates new GL texture
			GLCall(glGenTextures(1, &m_glID));

			//Tells GL to use this texture and apply parameters to it
			GLCall(glBindTexture(GL_TEXTURE_2D, m_glID));

			//Set some parameters
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

			//Sets source and some properties
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));

			stbi_image_free(buffer);
		}

		Texture::Texture(const unsigned char* src, size_t bpp, size_t width, size_t height)
			:m_BPP(bpp), m_height(height), m_width(width), m_glID(0)
		{
			//memcpy(m_buffer, src, width * height * bpp);

			//Creates new GL texture
			GLCall(glGenTextures(1, &m_glID));

			//Tells GL to use this texture and apply parameters to it
			GLCall(glBindTexture(GL_TEXTURE_2D, m_glID));

			//Set some parameters
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

			//Sets source and some properties
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, src));

			//Unbind texture (not compVRory but why not)
			GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		}

		Texture::Texture(const Texture& texture)
			:m_BPP(texture.m_BPP), m_height(texture.m_height), m_width(texture.m_width), m_glID(texture.m_glID)
		{
			texture.m_deleteTexture = false;

			//memcpy(m_buffer, texture.m_buffer, m_width * m_height * m_BPP);

			/*GLCall(glGenTextures(1, &m_glID));
			GLCall(glBindTexture(GL_TEXTURE_2D, m_glID));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer));
			GLCall(glBindTexture(GL_TEXTURE_2D, 0));*/
		}

		Texture::~Texture()
		{
			if (m_deleteTexture)
			{
				GLCall(glDeleteTextures(1, &m_glID));
			}
		}

		void Texture::Bind(unsigned int slot) const
		{
			GLCall(glBindTextureUnit(slot, m_glID));
		}
	}
}