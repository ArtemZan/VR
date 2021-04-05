#pragma once

//Executes given code (usually GL function) and calls
//__debugbreak() and prints error, file and line of code to console if error occurred
#define GLCall(glFunction) while(glGetError());\
glFunction;\
if(VR::gl::CheckForErrors(__FILE__, __LINE__, #glFunction)) __debugbreak()

namespace VR
{
	namespace gl
	{
		static const char* ErrorsMessages[]
		{
			"An unacceptable value is specified for an enumerated argument",
			"A numeric argument is out of range",
			"The specified operation is not allowed in the current state",
			"The framebuffer object is not complete",
			"There is not enough memory left to execute the command",
			"An attempt has been made to perform an operation that would cause an internal stack to underflow",
			"An attempt has been made to perform an operation that would cause an internal stack to overflow"
		};

		static bool CheckForErrors(const char* filepath, size_t line, const char* function)
		{
			if (GLenum e = glGetError())
			{
				int i = strlen(filepath);
				while (filepath[--i] != '\\');
				std::cout << filepath + i << " line " << line << " " << function << " : " << ErrorsMessages[e - GL_INVALID_ENUM];
				return true;
			}
			return false;
		}
	}
}