#include "pch.h"
#include "VR.h"

namespace VR
{
	namespace gl
	{
		AttribLayout::AttribLayout()
		{
			m_stride = 0;
		}

		AttribLayout::~AttribLayout()
		{

		}

		size_t AttribLayout::GetOffset(size_t pos) const
		{
			if (pos == 0 || pos >= m_attributes.size())
				return 0;

			size_t offset = 0;

			while (pos--)
				offset += m_attributes[pos].Size();

			return offset;
		}

		template <>
		void AttribLayout::Push<uint32_t>(size_t count)
		{
			m_attributes.emplace_back(count, GL_UNSIGNED_INT);
			m_stride += count * 4;
		}

		template <>
		void AttribLayout::Push<uint16_t>(size_t count)
		{
			m_attributes.emplace_back(count, GL_UNSIGNED_SHORT);
			m_stride += count * 2;
		}

		template <>
		void AttribLayout::Push<uint8_t>(size_t count)
		{
			m_attributes.emplace_back(count, GL_UNSIGNED_BYTE);
			m_stride += count * 1;
		}

		template <>
		void AttribLayout::Push<int32_t>(size_t count)
		{
			m_attributes.emplace_back(count, GL_INT);
			m_stride += count * 4;
		}

		template <>
		void AttribLayout::Push<int16_t>(size_t count)
		{
			m_attributes.emplace_back(count, GL_SHORT);
			m_stride += count * 2;
		}

		template <>
		void AttribLayout::Push<int8_t>(size_t count)
		{
			m_attributes.emplace_back(count, GL_BYTE);
			m_stride += count * 1;
		}

		template <>
		void AttribLayout::Push<float>(size_t count)
		{
			m_attributes.emplace_back(count, GL_FLOAT);
			m_stride += count * 4;
		}

		VertexAttrib::VertexAttrib(size_t count, GLenum type)
			:count(count), type(type)
		{

		}

		size_t VertexAttrib::SizeOfType() const
		{
			switch (type)
			{
			case GL_SHORT:
			case GL_UNSIGNED_SHORT: return 2;
			case GL_BYTE:
			case GL_UNSIGNED_BYTE:	return 1;
			default:				return 4; //float, int32_t and uint32_t
			}
		}
	}
}