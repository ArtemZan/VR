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
			: x(vec.x), y(vec.y)
		{
		}

		vec2::vec2(const vec2d& vec)
			: x(vec.x), y(vec.y)
		{
		}

		vec2::vec2(const vec3& vec)
			: x(vec.x), y(vec.y)
		{
		}

		vec2 vec2::operator*(float k)		  const
		{
			return { x * k, y * k };
		}

		vec2 vec2::operator*(const vec2& vec) const
		{
			return { x * vec.x, y * vec.y };
		}

		vec2 vec2::operator/(float k)		  const
		{
			return { x / k, y / k };
		}

		vec2 vec2::operator/(const vec2& vec) const
		{
			return { x / vec.x, y / vec.y };
		}

		vec2 vec2::operator+(const vec2& vec) const
		{
			return { x + vec.x, y + vec.y };
		}

		vec2 vec2::operator-(const vec2& vec) const
		{
			return { x - vec.x, y - vec.y };
		}

		vec2 vec2::operator-()				  const
		{
			return { -x, -y };
		}

		vec2& vec2::operator*=(const mat2& matrix)
		{
			*this = matrix * vec2d(*this);
			return *this;
		}

		void vec2::operator=(const vec2& vec)
		{
			x = vec.x;
			y = vec.y;
		}


		vec2 vec2::normalize() const
		{
			return *this / magnitude();
		}

		float vec2::distance(const vec2& vec) const
		{
			float dx = x - vec.x;
			float dy = y - vec.y;

			return sqrt(dx * dx + dy * dy);
		}

		float vec2::magnitude() const
		{
			return sqrt(x * x + y * y);
		}

		float vec2::cross(const vec2& vec) const
		{
			return vec3(*this, 0).cross(vec3(vec, 0)).z;
		}

		float vec2::dot(const vec2& vec) const
		{
			return x * vec.x + y * vec.y;
		}

		float vec2::cos(const vec2& vec) const
		{
			return dot(vec) / magnitude() / vec.magnitude();
		}



		//vec2i
		vec2i::vec2i()
			:x(0), y(0)
		{
		}

		vec2i::vec2i(int x, int y)
			: x(x), y(y)
		{
		}

		vec2i::vec2i(const vec2i& vec)
			: x(vec.x), y(vec.y)
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

		// vec2d

		vec2d::vec2d(double scale)
			:x(scale), y(scale)
		{
		}

		vec2d::vec2d(double x, double y)
			: x(x), y(y)
		{
		}

		vec2d::vec2d(const vec2d& vec)
			: x(x), y(y)
		{
		}

		vec2d::vec2d(const vec2& vec)
			: x(vec.x), y(vec.y)
		{
		}

		vec2d vec2d::operator*(double k)		  const
		{
			return { x * k, y * k };
		}

		vec2d vec2d::operator*(const vec2d& vec) const
		{
			return { x * vec.x, y * vec.y };
		}

		vec2d vec2d::operator/(double k)		  const
		{
			return { x / k, y / k };
		}

		vec2d vec2d::operator/(const vec2d& vec) const
		{
			return { x / vec.x, y / vec.y };
		}

		vec2d vec2d::operator+(const vec2d& vec) const
		{
			return { x + vec.x, y + vec.y };
		}

		vec2d vec2d::operator-(const vec2d& vec) const
		{
			return { x - vec.x, y - vec.y };
		}

		vec2d vec2d::operator-()				  const
		{
			return { -x, -y };
		}

		void vec2d::operator=(const vec2d& vec)
		{
			x = vec.x;
			y = vec.y;
		}


		vec2d vec2d::normalize() const
		{
			return *this / magnitude();
		}

		double vec2d::distance(const vec2d& vec) const
		{
			double dx = x - vec.x;
			double dy = y - vec.y;

			return sqrt(dx * dx + dy * dy);
		}

		double vec2d::magnitude() const
		{
			return sqrt(x * x + y * y);
		}

		double vec2d::cross(const vec2d& vec) const
		{
			return vec3(*this, 0).cross(vec3(vec, 0)).z;
		}

		double vec2d::dot(const vec2d& vec) const
		{
			return x * vec.x + y * vec.y;
		}

		double vec2d::cos(const vec2d& vec) const
		{
			return dot(vec) / magnitude() / vec.magnitude();
		}


		// vec3

		vec3::vec3(float scale)
			:x(scale), y(scale), z(scale)
		{
		}

		vec3::vec3(float x, float y, float z)
			: x(x), y(y), z(z)
		{

		}

		vec3::vec3(const vec2& vec, float z)
			: x(vec.x), y(vec.y), z(z)
		{
		}

		vec3::vec3(float x, const vec2& vec)
			: x(x), y(vec.x), z(vec.y)
		{
		}

		vec3::vec3(const vec3& vec3)
			: x(vec3.x), y(vec3.y), z(vec3.z)
		{

		}

		vec3::vec3(const vec4& vec)
			: x(vec.x), y(vec.y), z(vec.z)
		{
		}

		vec3& vec3::operator=(const vec3& vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;

			return *this;
		}


		vec3 vec3::operator*(float k) const
		{
			return { x * k, y * k, z * k };
		}

		vec3 vec3::operator*(const vec3& vec) const
		{
			return { x * vec.x, y * vec.y, z * vec.z };
		}

		vec3 vec3::operator/(float k) const
		{
			return { x / k, y / k, z / k };
		}

		vec3 vec3::operator/(const vec3& vec) const
		{
			return { x / vec.x, y / vec.y, z / vec.z };
		}

		vec3 vec3::operator+(const vec3& vec) const
		{
			return { x + vec.x, y + vec.y, z + vec.z };
		}

		vec3 vec3::operator-(const vec3& vec) const
		{
			return { x - vec.x, y - vec.y, z - vec.z };
		}

		vec3 vec3::operator-() const
		{
			return { -x, -y, -z };
		}


		/*void vec3::operator*=(float k)
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
		}*/

		vec3 vec3::normalize() const
		{
			return *this / magnitude();
		}

		float vec3::distance(const vec3& vec) const
		{
			float dx = x - vec.x;
			float dy = z - vec.y;
			float dz = x - vec.z;

			return sqrt(dx * dx + dy * dy + dz * dz);
		}

		float vec3::magnitude() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		float vec3::dot(const vec3& v) const
		{
			return x * v.x + y * v.y + z * v.z;
		}

#ifdef RIGHT_HANDED
		vec3 vec3::cross(const vec3& v) const { return { z * v.y - y * v.z, x * v.z - z * v.x, y * v.x - x * v.y }; }
#else
		vec3 vec3::cross(const vec3& v) const { return { y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x }; }
#endif

		// vec3d

		vec3d::vec3d(double scale)
			:x(scale), y(scale), z(scale)
		{
		}

		vec3d::vec3d(double x, double y, double z)
			: x(x), y(y), z(z)
		{

		}

		vec3d::vec3d(const vec2d& vec, double z)
			: x(vec.x), y(vec.y), z(z)
		{
		}

		vec3d::vec3d(double x, const vec2d& vec)
			: x(x), y(vec.x), z(vec.y)
		{
		}

		vec3d::vec3d(const vec3d& vec3)
			: x(vec3.x), y(vec3.y), z(vec3.z)
		{

		}

		vec3d::vec3d(const vec3& vec3)
			: x(vec3.x), y(vec3.y), z(vec3.z)
		{

		}

		vec3d::vec3d(const vec4d& vec)
			: x(vec.x), y(vec.y), z(vec.z)
		{
		}

		vec3d& vec3d::operator=(const vec3d& vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;

			return *this;
		}


		vec3d vec3d::operator*(double k) const
		{
			return { x * k, y * k, z * k };
		}

		vec3d vec3d::operator*(const vec3d& vec) const
		{
			return { x * vec.x, y * vec.y, z * vec.z };
		}

		vec3d vec3d::operator/(double k) const
		{
			return { x / k, y / k, z / k };
		}

		vec3d vec3d::operator/(const vec3d& vec) const
		{
			return { x / vec.x, y / vec.y, z / vec.z };
		}

		vec3d vec3d::operator+(const vec3d& vec) const
		{
			return { x + vec.x, y + vec.y, z + vec.z };
		}

		vec3d vec3d::operator-(const vec3d& vec) const
		{
			return { x - vec.x, y - vec.y, z - vec.z };
		}

		vec3d vec3d::operator-() const
		{
			return { -x, -y, -z };
		}

		vec3d vec3d::normalize() const
		{
			return *this / magnitude();
		}

		double vec3d::distance(const vec3d& vec) const
		{
			float dx = x - vec.x;
			float dy = z - vec.y;
			float dz = x - vec.z;

			return sqrt(dx * dx + dy * dy + dz * dz);
		}

		double vec3d::magnitude() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		double vec3d::dot(const vec3d& v) const
		{
			return x * v.x + y * v.y + z * v.z;
		}

#ifdef RIGHT_HANDED
		vec3d vec3d::cross(const vec3d& v) const { return { z * v.y - y * v.z, x * v.z - z * v.x, y * v.x - x * v.y }; }
#else
		vec3d vec3d::cross(const vec3d& v) const { return { y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x }; }
#endif

		//vec4

		vec4::vec4()
			: x(0), y(0), z(0), w(0)
		{
		}

		vec4::vec4(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w)
		{

		}

		vec4::vec4(const vec2& vec1, const vec2& vec2)
			: x(vec1.x), y(vec1.y), z(vec2.x), w(vec2.y)
		{
		}

		vec4::vec4(const vec2& vec, float z, float w)
			: x(vec.x), y(vec.y), z(z), w(w)
		{
		}

		vec4::vec4(float x, float y, const vec2& vec)
			: x(x), y(y), z(vec.x), w(vec.y)
		{
		}

		vec4::vec4(const vec3& vec, float w)
			: x(vec.x), y(vec.y), z(vec.z), w(w)
		{
		}

		vec4::vec4(float x, const vec3& vec)
			: x(x), y(vec.x), z(vec.y), w(vec.z)
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


		vec4 vec4::operator*(float k)			const
		{
			return { x * k, y * k, z * k, w * k };
		}

		vec4 vec4::operator*(const vec4& vec)	const
		{
			return { x * vec.x, y * vec.y, z * vec.z, w * vec.w };
		}

		vec4 vec4::operator/(float k)			const
		{
			return { x / k, y / k, z / k, w / k };
		}

		vec4 vec4::operator/(const vec4& vec)	const
		{
			return { x / vec.x, y / vec.y, z / vec.z, w / vec.w };
		}

		vec4 vec4::operator+(const vec4& vec)	const
		{
			return { x + vec.x, y + vec.y, z + vec.z, w + vec.w };
		}

		vec4 vec4::operator-(const vec4& vec)	const
		{
			return { x - vec.x, y - vec.y, z - vec.z, w + vec.w };
		}

		vec4 vec4::operator-() const
		{
			return { -x, -y, -z, -w };
		}

		vec4 vec4::normalize() const
		{
			return *this / magnitude();
		}

		float vec4::distance(const vec4& vec) const
		{
			float dx = x - vec.x;
			float dy = y - vec.y;
			float dz = z - vec.z;
			float dw = w - vec.w;
			return sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
		}

		float vec4::magnitude() const
		{
			return sqrt(x * x + y * y + z * z + w * w);
		}

		/*float vec4::cross(const vec4& vec) const
		{
			return 0.0f;
		}*/

		float vec4::dot(const vec4& vec) const
		{
			return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
		}

		float vec4::cos(const vec4& vec) const
		{
			return dot(vec) / magnitude() / vec.magnitude();
		}


		// mat2

		mat2::mat2()
		{
		}

		mat2::mat2(const mat2& mat)
			: i(mat.i), j(mat.j)
		{

		}

		mat2::mat2(double scale)
		{
			x.x = scale;
			y.y = scale;
		}

		mat2::mat2(const vec2d& i, const vec2d& j)
			: x(i), y(j)
		{

		}

		const mat2& mat2::operator*(const mat2& matrix)
		{
			mat2 res;

			res.x = *this * matrix.x;
			res.y = x * matrix.y.x + y * matrix.y.y;

			return res;
		}


		// mat2f

		mat2f::mat2f()
		{

		}

		mat2f::mat2f(const mat2f& mat)
			:i(mat.i), j(mat.j)
		{
		}

		mat2f::mat2f(const mat2& mat)
			: i(mat.i), j(mat.j)
		{
		}


		//mat3

		mat3::mat3()
		{
		}

		mat3::mat3(const mat3f& mat)
			:i(mat.i), j(mat.j), k(mat.k)
		{
		}

		mat3::mat3(const mat3& mat)
			: i(mat.i), j(mat.j), k(mat.k)
		{
		}

		mat3::mat3(double scale)
		{
			x.x = scale;
			y.y = scale;
			z.z = scale;
		}

		mat3::mat3(const vec3d& x, const vec3d& y, const vec3d& z)
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


		//mat3f

		mat3f::mat3f()
		{
		}

		mat3f::mat3f(const mat3f& mat)
			:i(mat.i), j(mat.j), k(mat.k)
		{
		}

		mat3f::mat3f(const mat3& mat)
			: i(mat.i), j(mat.j), k(mat.k)
		{
		}


		//mat4

		mat4::mat4()
		{
		}

		mat4::mat4(const mat4f& mat)
			:i(mat.i), j(mat.j), k(mat.k), l(mat.l)
		{
		}

		mat4::mat4(const mat4& mat)
			: i(mat.i), j(mat.j), k(mat.k), l(mat.l)
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

		mat4& mat4::operator=(const mat4& mat)
		{
			i = mat.i;
			j = mat.j;
			k = mat.k;
			l = mat.l;
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

		// mat4f

		mat4f::mat4f()
		{
		}

		mat4f::mat4f(const mat4f& mat)
			:i(mat.i), j(mat.j), k(mat.k), l(mat.l)
		{
		}

		mat4f::mat4f(const mat4& mat)
			: i(mat.i), j(mat.j), k(mat.k), l(mat.l)
		{
		}

		//mat3x2


		mat3x2::mat3x2()
		{

		}

		mat3x2::mat3x2(float scale)
		{
			x.x = scale;
			y.y = scale;
		}

		vec2 normalize(const math::vec2& vec)
		{
			return vec.normalize();
		}

		vec2d normalize(const math::vec2d& vec)
		{
			return vec.normalize();
		}

		vec3 normalize(const math::vec3& vec)
		{
			return vec.normalize();
		}

		vec3d normalize(const math::vec3d& vec)
		{
			return vec.normalize();
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

			const vec3 u = up.normalize();
			const vec3 d = -dir.normalize();

#ifdef RIGHT_HANDED
			const vec3 side(d.cross(up));
#else
			const vec3 side(-d.cross(up)); // Or leave same?
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
			res.w.x = -side.dot(eye);
			res.w.y = -u.dot(eye);
			res.w.z = -d.dot(eye);

			return res;
		}

		//Angle is in radians
		mat3 rotate(const vec3& axis, float angle)
		{
			const vec3 u = axis.normalize();

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