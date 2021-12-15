#include "pch.h"
#include "VR.h"
#include "Math.h"

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
		// vec2

		vec2::vec2(float scale)
			:x(scale), y(scale)
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

		vec2::vec2(const vec2i& vec)
			:x(vec.x), y(vec.y)
		{
		}

		vec2::vec2(const vec3& vec)
			:x(vec.x), y(vec.y)
		{
		}

		void vec2::operator=(const vec2& vec)
		{
			x = vec.x;
			y = vec.y;
		}


		vec2 vec2::operator*(const mat2& matrix) const
		{
			vec2 res = *this;
			res *= matrix;
			return res;
		}

		void vec2::operator*=(float k)
		{
			x *= k;
			y *= k;
		}

		void vec2::operator*=(const vec2& vec)
		{
			x *= vec.x;
			y *= vec.y;
		}

		void vec2::operator*=(const mat2& matrix)
		{
			*this = matrix.x * x + matrix.y * y;
		}

		void vec2::operator/=(float k)
		{
			x /= k;
			y /= k;
		}

		void vec2::operator/=(const vec2& vec)
		{
			x /= vec.x;
			y /= vec.y;
		}

		void vec2::operator+=(const vec2& vec)
		{
			x += vec.x;
			y += vec.y;
		}

		void vec2::operator-=(const vec2& vec)
		{
			x -= vec.x;
			y -= vec.y;
		}

		void vec2::normalize()
		{
			float l = sqrt(x * x + y * y);
			x /= l;
			y /= l;
		}

		float vec2::cross(const vec2& vec) const
		{
			return vec3(*this, 0).cross(vec3(vec, 0)).z;
		}

		float vec2::cos(const vec2& vec) const
		{
			float l = magnitude();
			if (l < 1e-9)
				return -1;

			float l1 = vec.magnitude();
			if (l1 < 1e-9)
				return -1;

			return dot(vec) / magnitude() / vec.magnitude();
		}

		vec2 normalize(const vec2& vec)
		{
			vec2 res = vec;
			res.normalize();
			return res;
		}


		//vec2i
		vec2i::vec2i()
			:x(0), y(0)
		{
		}

		vec2i::vec2i(int x, int y)
			:x(x), y(y)
		{
		}

		vec2i::vec2i(const vec2i& vec)
			:x(vec.x), y(vec.y)
		{
		}

		vec2i::vec2i(const vec2& vec)
		{
		}

		void vec2i::operator=(const vec2i& vec)
		{
			x = vec.x;
			y = vec.y;
		}



		vec3::vec3(float scale)
			:x(scale), y(scale), z(scale)
		{
		}

		vec3::vec3(float x, float y, float z)
			: x(x), y(y), z(z)
		{

		}

		vec3::vec3(const vec2& vec, float z)
			:x(vec.x), y(vec.y), z(z)
		{
		}

		vec3::vec3(float x, const vec2& vec)
			:x(x), y(vec.x), z(vec.y)
		{
		}

		vec3::vec3(const vec3& vec3)
			: x(vec3.x), y(vec3.y), z(vec3.z)
		{

		}

		vec3::vec3(const vec4& vec)
			:x(vec.x), y(vec.y), z(vec.z)
		{
		}

		vec3& vec3::operator=(const vec3& vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;

			return *this;
		}

		vec3 vec3::operator*(const mat3& matrix) const
		{
			vec3 res;
			res.x = matrix.x.x * x + matrix.y.x * y + matrix.z.x * z;
			res.y = matrix.x.y * x + matrix.y.y * y + matrix.z.y * z;
			res.z = matrix.x.z * x + matrix.y.z * y + matrix.z.z * z;
			return res;
		}

		void vec3::operator*=(float k)
		{
			x *= k;
			y *= k;
		}

		void vec3::operator*=(const mat3& matrix)
		{
			x = matrix.x.x * x + matrix.y.x * y + matrix.z.x * z;
			y = matrix.x.y * x + matrix.y.y * y + matrix.z.y * z;
			z = matrix.x.z * x + matrix.y.z * y + matrix.z.z * z;
		}

		void vec3::operator*=(const vec3& vec)
		{
			x *= vec.x;
			y *= vec.y;
			z *= vec.z;
		}

		void vec3::operator/=(float k)
		{
			x *= k;
			y *= k;
			z *= k;
		}

		void vec3::operator/=(const vec3& vec)
		{
			x /= vec.x;
			y /= vec.y;
			z /= vec.z;
		}

		void vec3::operator+=(const vec3& vec)
		{
			x += vec.x;
			y += vec.y;
			z += vec.z;
		}

		void vec3::operator-=(const vec3& vec)
		{
			x -= vec.x;
			y -= vec.y;
			z -= vec.z;
		}


		void vec3::normalize()
		{
			float l = sqrt(x * x + y * y + z * z);
			x /= l;
			y /= l;
			z /= l;
		}

		vec3 normalize(const vec3& vec)
		{
			vec3 res = vec;
			res.normalize();
			return res;
		}

		vec4::vec4()
			: x(0), y(0), z(0), w(0)
		{
		}

		vec4::vec4(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w)
		{

		}

		vec4::vec4(const vec2& vec1, const vec2& vec2)
			:x(vec1.x), y(vec1.y), z(vec2.x), w(vec2.y)
		{
		}

		vec4::vec4(const vec2& vec, float z, float w)
			: x(vec.x), y(vec.y), z(z), w(w)
		{
		}

		vec4::vec4(float x, float y, const vec2& vec)
			:x(x), y(y), z(vec.x), w(vec.y)
		{
		}

		vec4::vec4(const vec3& vec, float w)
			:x(vec.x), y(vec.y), z(vec.z), w(w)
		{
		}

		vec4::vec4(float x, const vec3& vec)
			:x(x), y(vec.x), z(vec.y), w(vec.z)
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
			res.x = x * matrix.x.x + y * matrix.y.x + z * matrix.z.x + w * matrix.w.x;
			res.y = x * matrix.x.y + y * matrix.y.y + z * matrix.z.y + w * matrix.w.y;
			res.z = x * matrix.x.z + y * matrix.y.z + z * matrix.z.z + w * matrix.w.z;
			res.w = x * matrix.x.w + y * matrix.y.w + z * matrix.z.w + w * matrix.w.w;
			return res;
		}

		vec4 vec4::operator*(float k) const
		{
			return vec4(x * k, y * k, z * k, w * k);
		}

		void vec4::normalize()
		{
			float l = sqrt(x * x + y * y + z * z + w * w);
			x /= l;
			y /= l;
			z /= l;
			w /= l;
		}

		vec4 normalize(const vec4& vec)
		{
			vec4 res = vec;
			res.normalize();
			return res;
		}

		mat2::mat2()
		{
		}

		mat2::mat2(float scale)
		{
			x.x = scale;
			y.y = scale;
		}

		mat2::mat2(vec2 i, vec2 j)
			: x(i), y(j)
		{
			
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

		mat3::mat3(const vec3& x, const vec3& y, const vec3& z)
			:x(x), y(y), z(z)
		{
		}

		mat3 mat3::operator*(const mat3& matrix) const
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

		mat4::mat4(const vec4& x, const vec4& y, const vec4& z, const vec4& w)
			:x(x), y(y), z(z), w(w)
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


		mat3x2::mat3x2()
		{

		}

		mat3x2::mat3x2(float scale)
		{
			x.x = scale;
			y.y = scale;
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
			mat4 res(1);

			const vec3 u = normalize(up);
			const vec3 d = normalize(-dir);

#ifdef RIGHT_HANDED
			const vec3 side(cross(d, up));
#else
			const vec3 side(-cross(d, up));
#endif

			res.x.x = side.x;
			res.y.x = side.y;
			res.z.x = side.z;
			res.x.y = u.x;
			res.y.y = u.y;
			res.z.y = u.z;
			res.x.z = d.x;
			res.y.z = d.y;
			res.z.z = d.z;
			res.w.x = -dot(side, eye);
			res.w.y = -dot(u, eye);
			res.w.z = -dot(d, eye);

			return res;
		}

		//Angle is in radians
		mat3 rotate(const vec3& axis, float angle)
		{
			const vec3 u = normalize(axis);

			const double c = cos(angle);
			const double s = sin(angle);

			vec3 i = vec3(
				c + u.x * u.x * (1 - c),
				u.y * u.x * (1 - c) + u.z * s,
				u.z * u.x * (1 - c) - u.y * s
			);

			vec3 j = vec3(
				u.x * u.y * (1 - c) - u.z * s,
				c + u.y * u.y * (1 - c),
				u.z * u.y * (1 - c) + u.x * s
			);

			vec3 k = vec3(
				u.x * u.z * (1 - c) + u.y * s,
				u.z * u.y * (1 - c) - u.x * s,
				c + u.z * u.z * (1 - c)
			);

			/*return mat3(
				vec3(0, 0, 1),
				vec3(0, 1, 0),
				vec3(-1, 0, 0)
			);*/

			return mat3(i, j, k);
		}

		mat2 rotate(float angle)
		{
			mat2 res;

			res.x.x = cos(angle);
			res.x.y = sin(angle);
			res.y.x = -sin(angle);
			res.y.y = cos(angle);

			return res;
		}


	}
}