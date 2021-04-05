#include "pch.h"
#include "../VR.h"

//modified bits should be set to 0 before calling this function
#define DefineSetBits(type)																	\
void SetBits(type* dst, size_t size_in_bits, type data, size_t dst_offset)					\
{																							\
	type x = pow(2, size_in_bits);															\
	for (int i = 0; i < size_in_bits; i++)													\
	{																						\
		x >>= 1;																			\
																							\
		*dst |= ((data & x) * (type)pow(2, sizeof(type) * 8 - dst_offset - size_in_bits));	\
	}																						\
																							\
}

namespace VR
{
	namespace math
	{
		vec2::vec2()
			:x(0), y(0)
		{
		}

		vec2::vec2(float x, float y)
			:x(x), y(y)
		{

		}

		vec2::vec2(vec2& vec2)
			:x(vec2.x), y(vec2.y)
		{

		}

		vec2::vec2(vec2&& vec2)
			: x(vec2.x), y(vec2.y)
		{

		}


		vec3::vec3()
			:x(0), y(0), z(0)
		{
		}

		vec3::vec3(float x, float y, float z)
			: x(x), y(y), z(z)
		{

		}

		vec3::vec3(vec3& vec3)
			: x(vec3.x), y(vec3.y), z(vec3.z)
		{

		}

		vec3::vec3(vec3&& vec3)
			: x(vec3.x), y(vec3.y), z(vec3.z)
		{

		}


		vec4::vec4()
			: x(0), y(0), z(0), w(0)
		{
		}

		vec4::vec4(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w)
		{

		}

		vec4::vec4(const vec4& vec4)
			: x(vec4.x), y(vec4.y), z(vec4.z), w(vec4.w)
		{

		}

		void vec4::operator=(const vec4& vec4)
		{
			x = vec4.x;
			y = vec4.y;
			z = vec4.z;
			w = vec4.w;
		}

		const vec4& vec4::operator*(const mat4& matrix) const
		{
			// TODO: insert return statement here
		}


		mat4::mat4()
		{
		}

		mat4::mat4(float scale)
		{
			x.x = scale;
			y.y = scale;
			z.z = scale;
			w.w = scale;
		}

		const mat4& mat4::operator*(const mat4& matrix)
		{
			mat4 res;
		}

	}
}