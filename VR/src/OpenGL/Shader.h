#pragma once

namespace VR
{
	namespace gl
	{
		//Reads shader file and creates a GL program
		class Shader
		{
		public:
			Shader(const char* filepath);

			Shader(const Shader& shader);

			~Shader();

			//Tells GL to use this program
			void Bind() const;

			//Tells GL to use default program
			static void Unbind();


			inline unsigned int GetID() const { return m_glID; }


			void SetUniform(const char* name, float x, float y);
			void SetUniform(const char* name, float v);
			void SetUniform(const char* name, const int* data, size_t count);
			void SetUniform(const char* name, glm::mat4x4 matrix);

		private:
			//Creates and compiles shader
			unsigned int CompileShader(unsigned int type, const std::string& source) const;

			//Reads shader file, creates program, attaches compiled shaders, 
			//compiles and links program and returns GL id of this new program
			unsigned int CreateProgram(const char* filepath) const;

			//Returns GL location (id) of the uniform. 
			//This location is used to set the value of the uniform
			GLint GetUniformLocation(const char* name);

		private:
			mutable bool					m_deleteProgram = true;
			unsigned int					m_glID;
			std::map<const char*, GLint>	m_uniformsLocaitons;
		};

	}
}