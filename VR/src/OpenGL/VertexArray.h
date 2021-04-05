#pragma once

namespace VR
{
	namespace gl
	{
		//Sets attributes arrays in GL : see https://www.khronos.org/opengl/wiki/Vertex_Specification#Vertex_Array_Object
		class VertexArray
		{
		public:
			VertexArray();
			~VertexArray();

			//Tells GL to use and modify this VA
			inline void Bind() const 
			{ 
				GLCall(glBindVertexArray(m_glID)); 
			}

			//Tells Gl not to use or modify any VA
			static inline void Unbind() 
			{ 
				GLCall(glBindVertexArray(0)); 
			}

			//Sets attributes pointers to current (bound) vertex buffer
			void AddBuffer(const AttribLayout& layout) const;
		private:
			GLuint m_glID;
		};

	}
}