#include "pch.h"
#include "VR.h"

namespace VR
{
	namespace gl
	{
		Shader::Shader(const char* filepath)
		{
			m_glID = CreateProgram(filepath);
		}

		Shader::Shader(const Shader& shader)
			:m_glID(shader.m_glID), m_uniformsLocaitons(shader.m_uniformsLocaitons)
		{
			shader.m_deleteProgram = false;
		}

		Shader::~Shader()
		{
			if (m_deleteProgram)
			{
				GLCall(glDeleteProgram(m_glID));
			}
		}

		void Shader::Bind() const
		{
			GLCall(glUseProgram(m_glID));
		}

		void Shader::Unbind()
		{
			GLCall(glUseProgram(0));
		}

		void Shader::SetUniform(const char* name, float x, float y)
		{
			GLCall(glUniform2f(GetUniformLocation(name), x, y));
		}

		void Shader::SetUniform(const char* name, float x, float y, float z)
		{
			GLCall(glUniform3f(GetUniformLocation(name), x, y, z));
		}

		void Shader::SetUniform(const char* name, float v)
		{
			GLCall(glUniform1f(GetUniformLocation(name), v));
		}

		void Shader::SetUniform(const char* name, const int* data, size_t count)
		{
			GLCall(glUniform1iv(GetUniformLocation(name), count, data));
		}

		void Shader::SetUniform(const char* name, const math::mat4& matrix)
		{
			GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, false, &matrix.x.x));
		}

		unsigned int Shader::CompileShader(unsigned int type, const std::string& source) const
		{
			GLCall(unsigned int shader = glCreateShader(type));
			const char* src = source.c_str();
			GLCall(glShaderSource(shader, 1, &src, 0));
			GLCall(glCompileShader(shader));

			int status;
			//Get compile status
			GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &status));

			if(status == GL_FALSE)
			{
				//Something went wrong

				int msgLength;
				GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &msgLength));
				char* message = new char[msgLength];
				GLCall(glGetShaderInfoLog(shader, msgLength, &msgLength, message));
				std::cout << "Failed to compile " << (type == GL_FRAGMENT_SHADER ? "fragment" : "vertex") << " shader: " << message << "\n";
				delete[] message;

				GLCall(glDeleteShader(shader));
				return 0;
			}

			return shader;
		}

		unsigned int Shader::CreateProgram(const char* filepath) const
		{
			//Pretty  stupid
			std::ifstream file(std::string("..\\..\\..\\Unleashed\\res\\Shaders\\") + filepath);
			if (file.fail())
				file = std::ifstream(std::string("res\\Shaders\\")  + filepath);

			std::stringstream fragment;
			std::stringstream vertex;
			std::string line;
			bool reading_fragment_shader = 0;
			while (std::getline(file, line))
			{
				//"#shader" in our shader file means "new shader"
				if (line.find("#shader") != std::string::npos)
				{
					//"#shader vertex" means "begin of vertex shader"
					if (line.find("vertex") != std::string::npos)
					{
						reading_fragment_shader = false;
					}
					else
					{
						//"#shader fragment" means "begin of fragment shader"
						if (line.find("fragment") != std::string::npos)
						{
							reading_fragment_shader = true;
						}
					}
				}
				else
				{
					if (reading_fragment_shader)
					{
						fragment << line << '\n';
					}
					else
					{
						vertex << line << '\n';
					}
				}
			}



			unsigned int fshader = CompileShader(GL_FRAGMENT_SHADER, fragment.str());
			unsigned int vshader = CompileShader(GL_VERTEX_SHADER, vertex.str());

			GLCall(unsigned int program = glCreateProgram());

			//Attach vertex and fragment shader to create a program
			GLCall(glAttachShader(program, fshader));
			GLCall(glAttachShader(program, vshader));

			//Link vertex shader with fragment shader
			GLCall(glLinkProgram(program));

			//Shaders can be detached and deleted since 
			//we have linked them into one program
			GLCall(glDetachShader(program, vshader));
			GLCall(glDetachShader(program, fshader));

			GLCall(glDeleteShader(fshader));
			GLCall(glDeleteShader(vshader));

			GLint linked = 0;
			//Get linking status
			GLCall(glGetProgramiv(program, GL_LINK_STATUS, &linked));
			if (linked == GL_FALSE)
			{
				//Something went wrong
				int msgLength;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &msgLength);
				char* message = new char[msgLength];
				GLCall(glGetProgramInfoLog(program, msgLength, &msgLength, message));
				std::cout << "Failed to link program: " << message << "\n";
				delete[] message;

				GLCall(glDeleteProgram(program));
				return 0;
			}

			GLCall(glValidateProgram(program));

			GLint valid;
			//Check whether the program can execute
			glGetProgramiv(program, GL_VALIDATE_STATUS, &valid);
			if (valid == GL_FALSE)
			{
				//Something went wrong
				int msgLength;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &msgLength);
				char* message = new char[msgLength];
				GLCall(glGetProgramInfoLog(program, msgLength, &msgLength, message));
				std::cout << "Failed to validate program: " << message << "\n";
				delete[] message;

				GLCall(glDeleteProgram(program));

				GLCall(glDeleteShader(fshader));
				GLCall(glDeleteShader(vshader));
				return 0;
			}

			return program;
		}

		GLint Shader::GetUniformLocation(const char* name)
		{
			//We could just call glGetUniformLocation but it is bad for performance 
			//so we call it only once - the first time when we use this uniform. If we have
			//found the location of the uniform before, just take it from m_uniformsLocations

			GLint location;

			if (m_uniformsLocaitons.find(name) == m_uniformsLocaitons.end())
			{
				GLCall(location = glGetUniformLocation(m_glID, name));
				if (location == -1)
				{
					std::cout << "Uniform not found!\n";
					return -1;
				}
				m_uniformsLocaitons[name] = location;
				return location;
			}
			else
			{
				return m_uniformsLocaitons[name];
			}
		}
	}
}