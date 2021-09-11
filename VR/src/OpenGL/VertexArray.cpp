#include "pch.h"
#include "VR.h"

namespace VR
{
	namespace gl
	{
		VertexArray::VertexArray()
		{
			GLCall(glGenVertexArrays(1, &m_glID));
			Bind();
		}

		VertexArray::VertexArray(const VertexArray& va)
		{
			memcpy(this, &va, sizeof(VertexArray));
			va.m_deleteBuffer = false;
		}

		VertexArray::~VertexArray()
		{
			if (m_deleteBuffer)
			{
				GLCall(glDeleteVertexArrays(1, &m_glID));
			}
		}

		void VertexArray::AddBuffer(const AttribLayout& layout) const
		{
			const auto& attrib = layout.GetAttributes();
			size_t offset = 0;
			for (int i = 0; i < attrib.size(); i++)
			{
				GLCall(glEnableVertexArrayAttrib(m_glID, i));
				GLCall(glVertexAttribPointer(i, attrib[i].count, attrib[i].type, GL_FALSE, layout.GetStride(), (const void*)offset));
				offset += attrib[i].Size();
			}
		}
	}
}