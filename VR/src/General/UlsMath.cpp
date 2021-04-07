#include "pch.h"
#include "VR.h"

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
			: x(x), y(y)
		{

		}

		vec2::vec2(const vec2& vec2)
			: x(vec2.x), y(vec2.y)
		{

		}

		void vec2::operator=(const vec2& vec)
		{
			x = vec.x;
			y = vec.y;
		}

		vec2 vec2::operator*(const mat2& matrix) const
		{
			vec2 res;
			res.x = matrix.x.x * x + matrix.y.x * y;
			res.y = matrix.x.y * x + matrix.y.y * y;
			return res;
		}

		vec2 vec2::operator*(float k) const
		{
			return vec2(x * k, y * k);
		}

		vec2 vec2::operator+(const vec2& vec) const
		{
			return vec2(x + vec.x, y + vec.y);
		}


		vec3::vec3()
			:x(0), y(0), z(0)
		{
		}

		vec3::vec3(float x, float y, float z)
			: x(x), y(y), z(z)
		{

		}

		vec3::vec3(const vec3& vec3)
			: x(vec3.x), y(vec3.y), z(vec3.z)
		{

		}

		void vec3::operator=(const vec3& vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
		}

		vec3 vec3::operator*(const mat3& matrix) const
		{
			vec3 res;
			res.x = matrix.x.x * x + matrix.y.x * y + matrix.z.x * z;
			res.y = matrix.x.y * x + matrix.y.y * y + matrix.z.y * z;
			res.z = matrix.x.z * x + matrix.y.z * y + matrix.z.z * z;
			return res;
		}

		vec3 vec3::operator*(float k) const
		{
			return vec3(x * k, y * k, z * k);
		}

		inline vec3 vec3::operator+(const vec3& vec) const
		{
			return vec3(x + vec.x, y + vec.y, z + vec.z);
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

		vec4 vec4::operator+(const vec4& vec) const
		{
			vec4 res;
			res.x = x + vec.x;
			res.y = y + vec.y;
			res.z = z + vec.z;
			res.w = w + vec.w;
			return res;
		}

		vec4 vec4::operator*(const mat4& matrix) const
		{
			vec4 res;
			res.x = x * matrix.x.x + y * matrix.y.x + z * matrix.z.x + w * matrix.z.x;
			res.y = x * matrix.x.y + y * matrix.y.y + z * matrix.z.y + w * matrix.z.x;
			res.z = x * matrix.x.z + y * matrix.y.z + z * matrix.z.z + w * matrix.z.x;
			res.w = x * matrix.x.w + y * matrix.y.w + z * matrix.z.w + w * matrix.z.x;
			return res;
		}

		vec4 vec4::operator*(float k) const
		{
			return vec4(x * k, y * k, z * k, w * k);
		}



		mat2::mat2()
		{
		}

		mat2::mat2(float scale)
		{
			x.x = scale;
			y.y = scale;
		}

		const mat2& mat2::operator*(const mat2& matrix)
		{
			mat2 res;

			res.x = x * matrix.x.x + y * matrix.x.y;
			res.y = x * matrix.y.x + y * matrix.y.y;

			return res;
		}


		mat3::mat3()
		{
		}

		mat3::mat3(float scale)
		{
			x.x = scale;
			y.y = scale;
			z.z = scale;
		}

		const mat3& mat3::operator*(const mat3& matrix)
		{
			mat3 res;
			res.x = x * matrix.x.x + y * matrix.x.y + z * matrix.x.z;
			res.y = x * matrix.y.x + y * matrix.y.y + z * matrix.y.z;
			res.z = x * matrix.z.x + y * matrix.z.y + z * matrix.z.z;
			return res;
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

		mat4 mat4::operator*(const mat4& matrix) const
		{
			mat4 res;
			res.x = x * matrix.x.x + y * matrix.x.y + z * matrix.x.z + w * matrix.x.w;
			res.y = x * matrix.y.x + y * matrix.y.y + z * matrix.y.z + w * matrix.y.w;
			res.z = x * matrix.z.x + y * matrix.z.y + z * matrix.z.z + w * matrix.z.w;
			res.w = x * matrix.w.x + y * matrix.w.y + z * matrix.w.z + w * matrix.w.w;
			return res;
		}


		mat4 perspective(float fov, float aspect, float near, float far)
		{
			mat4 res(1.0f);
			res.x.x = 1.0f / aspect / tan(fov / 2);
			res.y.y = 1.0f / tan(fov / 2);
			res.z.z = -(far + near) / (far - near);
			res.z.w = -1;
			res.w.z = -(2.0f * far * near) / (far - near);
			return res;
		}

		mat4 lookAt(const vec3& eye, const vec3& dir, const vec3& up)
		{
			mat4 res;
			vec3 target = eye + dir;
			glm::mat4 glmRes = glm::lookAt(glm::vec3(eye.x, eye.y, eye.z), glm::vec3(0.0, 0.0, 0.0), glm::vec3(up.x, up.y, up.z));
			memcpy(&res, &glmRes, sizeof(mat4));
			return res;
		}

}
}