#pragma once

namespace VR
{
	namespace gl
	{
		// Class to define layout of data (attributes) in vertices
		class AttribLayout
		{
			//Attribute properties
			struct VertexAttrib
			{
				VertexAttrib(size_t count, GLenum type);
				size_t count;
				GLenum type;
			};

			std::vector<VertexAttrib>	m_attributes;
			size_t						m_stride;
		public:
			AttribLayout();
			~AttribLayout();

			template <typename T>
			void Push(size_t count)
			{
				static_assert(0, "AttribLayout::Push : Undefined type");
			}

			//Adds attribute with {count} elements of type uint32_t to the layout
			template <>
			void Push<uint32_t>(size_t count);

			//Adds attribute with {count} elements of type uint16_t to the layout
			template <>
			void Push<uint16_t>(size_t count);

			//Adds attribute with {count} elements of type uint8_t to the layout
			template <>
			void Push<uint8_t>(size_t count);

			//Adds attribute with {count} elements of type uint32_t to the layout
			template <>
			void Push<int32_t>(size_t count);

			//Adds attribute with {count} elements of type uint16_t to the layout
			template <>
			void Push<int16_t>(size_t count);

			//Adds attribute with {count} elements of type uint8_t to the layout
			template <>
			void Push<int8_t>(size_t count);

			//Adds attribute with {count} elements of type float to the layout
			template <>
			void Push<float>(size_t count);


			inline const std::vector<VertexAttrib>& GetAttributes() const { return m_attributes; }
			inline size_t GetStride() const { return m_stride; }
		};
	}
}

