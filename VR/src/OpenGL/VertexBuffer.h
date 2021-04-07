#pragma once

namespace VR
{
	namespace gl
	{
		//Manipulating vertices data
		class VertexBuffer
		{
		public:
			//"Dynamic" constructor (sets only size, data is given later, on update)
			VertexBuffer(size_t size);

			//"Static" constructor (sets size and data that can't be changed)
			VertexBuffer(const void* data, size_t size);

			//Copy constructor
			VertexBuffer(const VertexBuffer& buffer);

			~VertexBuffer();

			//Tells GL to use and modify this data buffer
			inline void Bind() const
			{
				GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_glID));
			}

			//Tells GL not to use any data buffer ( maybe useless :)  )
			static inline void Unbind()
			{
				GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
			}

			//Sets data in the buffer (only if we have "dynamic" buffer)
			inline void Data(size_t size, const void* data) const
			{
				if (!m_staticDraw)
					GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
			}

			inline void Resize(size_t new_size) const
			{
				if (!m_staticDraw)
				{
					Bind();
					GLCall(glBufferData(GL_ARRAY_BUFFER, new_size, nullptr, GL_DYNAMIC_DRAW));
				}
			}

			void Resize(size_t size);

		private:
			mutable bool m_deleteBuffer = true;
			GLuint	m_glID;
			bool	m_staticDraw;
		};

	}
}

