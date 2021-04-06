#include "pch.h"
#include "VR.h"

namespace VR
{
	namespace gl
	{

		VertexBuffer::VertexBuffer(size_t size)
		{
			GLCall(glGenBuffers(1, &m_glID));
			Bind();
			GLCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
			m_staticDraw = false;
		}

		VertexBuffer::VertexBuffer(const void* data, size_t size)
		{
			GLCall(glGenBuffers(1, &m_glID));
			Bind();
			GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
			m_staticDraw = true;
		}

		VertexBuffer::VertexBuffer(const VertexBuffer& buffer)
		{
			memcpy(this, &buffer, sizeof(VertexBuffer));
			buffer.m_deleteBuffer = false;
		}

		VertexBuffer::~VertexBuffer()
		{
			if (m_deleteBuffer)
			{
				GLCall(glDeleteBuffers(1, &m_glID));
			}
		}

		void VertexBuffer::Resize(size_t new_size)
		{
			//GLCall(glDeleteBbuffers(1, &m_glID));
			//GLCall(glGenBuffers(1, &m_glID));
			Bind();
			GLCall(glBufferData(GL_ARRAY_BUFFER, new_size, nullptr, GL_DYNAMIC_DRAW));
		}
	}

}
