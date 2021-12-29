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

		// Tvec2

		template<typename T>
		Tvec2<T>::Tvec2(T scale)
			:x(scale), y(scale)
		{

		}

		template<typename T>
		Tvec2<T>::Tvec2(T x, T y)
			: x(x), y(y)
		{
		}

		template<typename T>
		Tvec2<T> Tvec2<T>::operator*(T k)	const
		{
			return { x * k, y * k };
		}

		template<typename T>
		Tvec2<T> Tvec2<T>::operator*(const Tvec2<T>& vec) const
		{
			return { x * vec.x, y * vec.y };
		}

		template<typename T>
		Tvec2<T> Tvec2<T>::operator/(T k)		  const
		{
			return { x / k, y / k };
		}

		template<typename T>
		Tvec2<T> Tvec2<T>::operator/(const Tvec2<T>& vec) const
		{
			return { x / vec.x, y / vec.y };
		}

		template<typename T>
		Tvec2<T> Tvec2<T>::operator+(const Tvec2<T>& vec) const
		{
			return { x + vec.x, y + vec.y };
		}

		template<typename T>
		Tvec2<T> Tvec2<T>::operator-(const Tvec2<T>& vec) const
		{
			return { x - vec.x, y - vec.y };
		}

		template<typename T>
		Tvec2<T> Tvec2<T>::operator-()				  const
		{
			return { -x, -y };
		}


		template<typename T>
		Tvec2<T>& Tvec2<T>::operator=(const Tvec2<T>& vec)
		{
			x = vec.x;
			y = vec.y;

			return *this;
		}


		template<typename T>
		Tvec2<T>& Tvec2<T>::operator*=(T scale)
		{
			return *this = *this * scale;
		}

		template<typename T>
		Tvec2<T>& Tvec2<T>::operator*=(const Tvec2& vec)
		{
			return *this = *this * vec;
		}

		template<typename T>
		Tvec2<T>& Tvec2<T>::operator*=(const Tmat2<T>& matrix)
		{
			return *this = matrix * *this;
		}

		template<typename T>
		Tvec2<T>& Tvec2<T>::operator/=(T scale)
		{
			return *this = *this / scale;
		}

		template<typename T>
		Tvec2<T>& Tvec2<T>::operator/=(const Tvec2& vec)
		{
			return *this = *this / vec;
		}

		template<typename T>
		Tvec2<T>& Tvec2<T>::operator+=(const Tvec2& vec)
		{
			return *this = *this + vec;
		}

		template<typename T>
		Tvec2<T>& Tvec2<T>::operator-=(const Tvec2& vec)
		{
			return *this = *this - vec;
		}


		template<typename T>
		Tvec2<T> Tvec2<T>::normalize() const
		{
			return *this / magnitude();
		}

		template<typename T>
		T Tvec2<T>::distance(const Tvec2<T>& vec) const
		{
			float dx = x - vec.x;
			float dy = y - vec.y;

			return sqrt(dx * dx + dy * dy);
		}

		template<typename T>
		T Tvec2<T>::magnitude() const
		{
			return sqrt(x * x + y * y);
		}

		template<typename T>
		T Tvec2<T>::cross(const Tvec2<T>& vec) const
		{
			return vec3(*this, 0).cross(vec3(vec, 0)).z;
		}

		template<typename T>
		T Tvec2<T>::dot(const Tvec2<T>& vec) const
		{
			return x * vec.x + y * vec.y;
		}

		template<typename T>
		T Tvec2<T>::cos(const Tvec2<T>& vec) const
		{
			return dot(vec) / magnitude() / vec.magnitude();
		}


		// Tvec3
		template<typename T>
		Tvec3<T>::Tvec3(T scale)
			:x(scale), y(scale), z(scale)
		{
		}

		template<typename T>
		Tvec3<T>::Tvec3(T x, T y, T z)
			: x(x), y(y), z(z)
		{

		}

		template<typename T>
		Tvec3<T>::Tvec3(const Tvec2<T>& vec, T z)
			: x(vec.x), y(vec.y), z(z)
		{
		}

		template<typename T>
		Tvec3<T>::Tvec3(T x, const Tvec2<T>& vec)
			: x(x), y(vec.x), z(vec.y)
		{
		}


		template<typename T>
		Tvec3<T>& Tvec3<T>::operator=(const Tvec3<T>& vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;

			return *this;
		}


		template<typename T>
		Tvec3<T> Tvec3<T>::operator*(T k) const
		{
			return { x * k, y * k, z * k };
		}

		template<typename T>
		Tvec3<T> Tvec3<T>::operator*(const Tvec3<T>& vec) const
		{
			return { x * vec.x, y * vec.y, z * vec.z };
		}

		template<typename T>
		Tvec3<T> Tvec3<T>::operator/(T k) const
		{
			return { x / k, y / k, z / k };
		}

		template<typename T>
		Tvec3<T> Tvec3<T>::operator/(const Tvec3<T>& vec) const
		{
			return { x / vec.x, y / vec.y, z / vec.z };
		}

		template<typename T>
		Tvec3<T> Tvec3<T>::operator+(const Tvec3<T>& vec) const
		{
			return { x + vec.x, y + vec.y, z + vec.z };
		}

		template<typename T>
		Tvec3<T> Tvec3<T>::operator-(const Tvec3<T>& vec) const
		{
			return { x - vec.x, y - vec.y, z - vec.z };
		}

		template<typename T>
		Tvec3<T> Tvec3<T>::operator-() const
		{
			return { -x, -y, -z };
		}


		template<typename T>
		Tvec3<T>& Tvec3<T>::operator*=(T k)
		{
			x *= k;
			y *= k;

			return *this;
		}

		template<typename T>
		Tvec3<T>& Tvec3<T>::operator*=(const Tmat3<T>& matrix)
		{
			x = matrix.x.x * x + matrix.y.x * y + matrix.z.x * z;
			y = matrix.x.y * x + matrix.y.y * y + matrix.z.y * z;
			z = matrix.x.z * x + matrix.y.z * y + matrix.z.z * z;

			return *this;
		}

		template<typename T>
		Tvec3<T>& Tvec3<T>::operator*=(const Tvec3<T>& vec)
		{
			x *= vec.x;
			y *= vec.y;
			z *= vec.z;

			return *this;
		}

		template<typename T>
		Tvec3<T>& Tvec3<T>::operator/=(T k)
		{
			x *= k;
			y *= k;
			z *= k;

			return *this;
		}

		template<typename T>
		Tvec3<T>& Tvec3<T>::operator/=(const Tvec3<T>& vec)
		{
			x /= vec.x;
			y /= vec.y;
			z /= vec.z;

			return *this;
		}

		template<typename T>
		Tvec3<T>& Tvec3<T>::operator+=(const Tvec3<T>& vec)
		{
			x += vec.x;
			y += vec.y;
			z += vec.z;

			return *this;
		}

		template<typename T>
		Tvec3<T>& Tvec3<T>::operator-=(const Tvec3<T>& vec)
		{
			x -= vec.x;
			y -= vec.y;
			z -= vec.z;

			return *this;
		}

		template<typename T>
		Tvec3<T> Tvec3<T>::normalize() const
		{
			return *this / magnitude();
		}

		template<typename T>
		T Tvec3<T>::distance(const Tvec3<T>& vec) const
		{
			float dx = x - vec.x;
			float dy = z - vec.y;
			float dz = x - vec.z;

			return sqrt(dx * dx + dy * dy + dz * dz);
		}

		template<typename T>
		T Tvec3<T>::magnitude() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		template<typename T>
		T Tvec3<T>::dot(const Tvec3<T>& v) const
		{
			return x * v.x + y * v.y + z * v.z;
		}

		template<typename T>
		Tvec3<T> Tvec3<T>::cross(const Tvec3<T>& v) const {
			return
#ifdef RIGHT_HANDED
			{ z * v.y - y * v.z, x * v.z - z * v.x, y * v.x - x * v.y };
#else
			{ y* v.z - z * v.y, z* v.x - x * v.z, x* v.y - y * v.x };
#endif
		}

		template<typename T>
		Tvec3<T> cross(const Tvec3<T>& vec1, const Tvec3<T>& vec2) {
			return vec1.cross(vec2);
		}

		//vec4

		template<typename T>
		Tvec4<T>::Tvec4(T scale)
			: x(scale), y(scale), z(scale), w(scale)
		{
		}

		template<typename T>
		Tvec4<T>::Tvec4(T x, T y, T z, T w)
			: x(x), y(y), z(z), w(w)
		{

		}

		template<typename T>
		Tvec4<T>::Tvec4(const Tvec2<T>& vec1, const Tvec2<T>& vec2)
			: x(vec1.x), y(vec1.y), z(vec2.x), w(vec2.y)
		{
		}

		template<typename T>
		Tvec4<T>::Tvec4(const Tvec2<T>& vec, T z, T w)
			: x(vec.x), y(vec.y), z(z), w(w)
		{
		}

		template<typename T>
		Tvec4<T>::Tvec4(T x, const Tvec2<T>& vec, T w)
			:x(x), y(vec.x), z(vec.y), w(w)
		{

		}

		template<typename T>
		Tvec4<T>::Tvec4(T x, T y, const Tvec2<T>& vec)
			: x(x), y(y), z(vec.x), w(vec.y)
		{
		}

		template<typename T>
		Tvec4<T>::Tvec4(const Tvec3<T>& vec, T w)
			: x(vec.x), y(vec.y), z(vec.z), w(w)
		{
		}

		template<typename T>
		Tvec4<T>::Tvec4(T x, const Tvec3<T>& vec)
			: x(x), y(vec.x), z(vec.y), w(vec.z)
		{
		}

		template<typename T>
		Tvec4<T> Tvec4<T>::operator*(T k)			const
		{
			return { x * k, y * k, z * k, w * k };
		}

		template<typename T>
		Tvec4<T> Tvec4<T>::operator*(const Tvec4<T>& vec)	const
		{
			return { x * vec.x, y * vec.y, z * vec.z, w * vec.w };
		}

		template<typename T>
		Tvec4<T> Tvec4<T>::operator/(T k)			const
		{
			return { x / k, y / k, z / k, w / k };
		}

		template<typename T>
		Tvec4<T> Tvec4<T>::operator/(const Tvec4<T>& vec)	const
		{
			return { x / vec.x, y / vec.y, z / vec.z, w / vec.w };
		}

		template<typename T>
		Tvec4<T> Tvec4<T>::operator+(const Tvec4<T>& vec)	const
		{
			return { x + vec.x, y + vec.y, z + vec.z, w + vec.w };
		}

		template<typename T>
		Tvec4<T> Tvec4<T>::operator-(const Tvec4<T>& vec)	const
		{
			return { x - vec.x, y - vec.y, z - vec.z, w + vec.w };
		}

		template<typename T>
		Tvec4<T> Tvec4<T>::operator-() const
		{
			return { -x, -y, -z, -w };
		}

		template<typename T>
		Tvec4<T>& Tvec4<T>::operator=(const Tvec4<T>& vec4)
		{
			x = vec4.x;
			y = vec4.y;
			z = vec4.z;
			w = vec4.w;

			return *this;
		}


		template<typename T>
		Tvec4<T>& Tvec4<T>::operator*=(T k)
		{
			return *this = *this * k;
		}

		template<typename T>
		Tvec4<T>& Tvec4<T>::operator*=(const Tvec4<T>& vec)
		{
			return *this = *this * vec;
		}

		template<typename T>
		Tvec4<T>& Tvec4<T>::operator*=(const Tmat4<T>& matrix)
		{
			return *this = matrix * *this;
		}


		template<typename T>
		Tvec4<T>& Tvec4<T>::operator/=(T k)
		{
			return *this = *this / k;
		}

		template<typename T>
		Tvec4<T>& Tvec4<T>::operator/=(const Tvec4<T>& vec)
		{
			return *this = *this / vec;
		}

		template<typename T>
		Tvec4<T>& Tvec4<T>::operator+=(const Tvec4<T>& vec)
		{
			return *this = *this + vec;
		}

		template<typename T>
		Tvec4<T>& Tvec4<T>::operator-=(const Tvec4<T>& vec)
		{
			return *this = *this - vec;
		}



		template<typename T>
		Tvec4<T> Tvec4<T>::normalize() const
		{
			return *this / magnitude();
		}

		template<typename T>
		T Tvec4<T>::distance(const Tvec4<T>& vec) const
		{
			float dx = x - vec.x;
			float dy = y - vec.y;
			float dz = z - vec.z;
			float dw = w - vec.w;
			return sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
		}

		template<typename T>
		T Tvec4<T>::magnitude() const
		{
			return sqrt(x * x + y * y + z * z + w * w);
		}

		/*float Tvec4<T>::cross(const Tvec4<T>& vec) const
		{
			return 0.0f;
		}*/

		template<typename T>
		T Tvec4<T>::dot(const Tvec4<T>& vec) const
		{
			return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
		}

		template<typename T>
		T Tvec4<T>::cos(const Tvec4<T>& vec) const
		{
			return dot(vec) / magnitude() / vec.magnitude();
		}


		// Tmat2

		template<typename T>
		Tmat2<T>::Tmat2(T scale)
			:i(0), j(0)
		{
			x.x = scale;
			y.y = scale;
		}

		template<typename T>
		Tmat2<T>::Tmat2(const Tvec2<T>& i, const Tvec2<T>& j)
			: x(i), y(j)
		{

		}

		template<typename T>
		Tmat2<T>& Tmat2<T>::operator=(const Tmat2<T>& mat)
		{
			i = mat.i;
			j = mat.j;

			return *this;
		}


		template<typename T>
		Tvec2<T> Tmat2<T>::operator*(const Tvec2<T>& vec) const
		{
			return i * vec.x + j * vec.y;
		}

		template<typename T>
		Tmat2<T> Tmat2<T>::operator*(const Tmat2<T>& matrix) const
		{
			Tmat2<T> res;

			res.x = *this * matrix.x;
			res.y = x * matrix.y.x + y * matrix.y.y;

			return res;
		}


		//Tmat3

		template<typename T>
		Tmat3<T>::Tmat3(T scale)
			:i(0), j(0), k(0)
		{
			x.x = scale;
			y.y = scale;
			z.z = scale;
		}

		template<typename T>
		Tmat3<T>::Tmat3(const Tvec3<T>& x, const Tvec3<T>& y, const Tvec3<T>& z)
			:x(x), y(y), z(z)
		{
		}

		template<typename T>
		Tmat3<T>& Tmat3<T>::operator=(const Tmat3<T>& mat)
		{
			i = mat.i;
			j = mat.j;
			k = mat.k;

			return *this;
		}

		template<typename T>
		Tvec3<T> Tmat3<T>::operator*(const Tvec3<T>& vec) const
		{
			return i * vec.x + j * vec.y + k * vec.z;
		}

		template<typename T>
		Tmat3<T> Tmat3<T>::operator*(const Tmat3<T>& matrix) const
		{
			Tmat3<T> res;
			res.x = x * matrix.x.x + y * matrix.x.y + z * matrix.x.z;
			res.y = x * matrix.y.x + y * matrix.y.y + z * matrix.y.z;
			res.z = x * matrix.z.x + y * matrix.z.y + z * matrix.z.z;

			return res;
		}


		//Tmat4


		template<typename T>
		Tmat4<T>::Tmat4()
			:i(0), j(0), k(0), l(0)
		{
			
		}

		template<typename T>
		Tmat4<T>::Tmat4(T scale)
			:i(0), j(0), k(0), l(0)
		{
			x.x = scale;
			y.y = scale;
			z.z = scale;
			w.w = scale;
		}

		template<typename T>
		Tmat4<T>::Tmat4(const Tvec4<T>& x, const Tvec4<T>& y, const Tvec4<T>& z, const Tvec4<T>& w)
			: x(x), y(y), z(z), w(w)
		{
		}

		template<typename T>
		Tmat4<T>& Tmat4<T>::operator=(const Tmat4<T>& mat)
		{
			i = mat.i;
			j = mat.j;
			k = mat.k;
			l = mat.l;

			return *this;
		}

		template<typename T>
		Tvec4<T> Tmat4<T>::operator*(const Tvec4<T>& vec) const
		{
			return i * vec.x + j * vec.y + k * vec.z + l * vec.w;
		}

		template<typename T>
		Tmat4<T> Tmat4<T>::operator*(const Tmat4<T>& matrix) const
		{
			Tmat4<T> res;
			res.x = x * matrix.x.x + y * matrix.x.y + z * matrix.x.z + w * matrix.x.w;
			res.y = x * matrix.y.x + y * matrix.y.y + z * matrix.y.z + w * matrix.y.w;
			res.z = x * matrix.z.x + y * matrix.z.y + z * matrix.z.z + w * matrix.z.w;
			res.w = x * matrix.w.x + y * matrix.w.y + z * matrix.w.z + w * matrix.w.w;

			return res;
		}

		template<typename T>
		T Tmat4<T>::det() const {
			Tmat3<T> m1 = {
				{y.y, y.z, y.w},
				{z.y, z.z, z.w},
				{w.y, w.z, w.w}
			};

			Tmat3<T> m2 = {
				{x.y, x.z, x.w},
				{z.y, z.z, z.w},
				{w.y, w.z, w.w}
			};

			Tmat3<T> m3 = {
				{x.y, x.z, x.w},
				{y.y, y.z, y.w},
				{w.y, w.z, w.w}
			};

			Tmat3<T> m4 = {
				{x.y, x.z, x.w},
				{y.y, y.z, y.w},
				{z.y, z.z, z.w}
			};

			return i.x * m1.det() - j.x * m2.det() + k.x * m3.det() - l.x * m4.det();
		}


		//Tmat3x2


		template<typename T>
		Tmat3x2<T>::Tmat3x2(const Tvec2<T>& i, const Tvec2<T>& j, const Tvec2<T>& k)
			:i(i), j(j), k(k)
		{

		}

		template<typename T>
		Tmat3x2<T>::Tmat3x2(T scale)
			:i(0), j(0), k(0)
		{
			x.x = scale;
			y.y = scale;
		}

		template<typename T>
		Tmat3x2<T>& Tmat3x2<T>::operator=(const Tmat3x2<T>& mat)
		{
			i = mat.i;
			j = mat.j;
			k = mat.k;

			return *this;
		}

		template<typename T>
		Tvec2<T> normalize(const math::Tvec2<T>& vec)
		{
			return vec.normalize();
		}

		template<typename T>
		Tvec3<T> normalize(const math::Tvec3<T>& vec)
		{
			return vec.normalize();
		}


		template<typename T>
		Tvec4<T> normalize(const math::Tvec4<T>& vec)
		{
			return vec.normalize();
		}

		mat4 perspective(float fov, float aspect, float near, float far)
		{
			Tmat4 res(1.0f);
			res.x.x = 1.0f / aspect / tan(fov / 2);
			res.y.y = 1.0f / tan(fov / 2);
			res.z.z = -(far + near) / (far - near);
			res.z.w = -1;
			res.w.z = -(2.0f * far * near) / (far - near);
			return res;
		}

		mat4 lookAt(const vec3& eye, const vec3& dir, const vec3& up)
		{
			Tmat4 res(1);

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

			/*return Tmat3(
				Tvec3(0, 0, 1),
				Tvec3(0, 1, 0),
				Tvec3(-1, 0, 0)
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


		//Some dirty stuff here

#define CROSS_4 
#define CROSS_3	vec.cross(vec);
#define CROSS_2	vec.cross(vec);
#define CROSS(DEFINE) CROSS_##DEFINE

#define __DefUseVecGeneral(SIZE) 		   	\
		template<typename T>			   	\
		void __UseVec##SIZE##General() {	\
			Tvec##SIZE##<T> vec;		   	\
											\
			CROSS(SIZE)						\
			vec.distance(vec);			   	\
			vec.dot(vec);				   	\
			vec.magnitude();			   	\
			vec.normalize();			   	\
			normalize(vec);			   		\
										   	\
			vec = -vec;						\
			vec *= 1;					   	\
			vec *= Tmat##SIZE##<T>();		\
			vec *= vec;					   	\
			vec * 1;					   	\
			Tmat##SIZE##<T>() * vec;		\
			vec * vec;						\
			vec += vec;					   	\
			vec -= vec;					   	\
			vec /= vec;					   	\
			vec + vec;					   	\
			vec - vec;					   	\
			vec / vec;					   	\
		}

		__DefUseVecGeneral(2);
		__DefUseVecGeneral(3);
		__DefUseVecGeneral(4);

#define __DefUseMatGeneral(SIZE) 		   	\
		template<typename T>				\
		void __UseMat##SIZE##General() {	\
			Tmat##SIZE##<T> mat(T(1));		\
			Tmat##SIZE##<T> mat1;		\
			mat = mat;						\
		}

		__DefUseMatGeneral(2);
		__DefUseMatGeneral(3);
		__DefUseMatGeneral(4);
		__DefUseMatGeneral(3x2);

		template<typename T>
		void __UseVec2() {
			Tvec2<T> v(Tvec3<T>(0));

			Tvec2<T> v1(1, 2);

			v.cross(v);
		}

		template<typename T>
		void __UseVec3() {
			Tvec3<T> v(Tvec4<T>(0));

			Tvec3<T> v1(Tvec2<T>(0), T(0));
			Tvec3<T> v2(T(0), Tvec2<T>(0));

			Tvec3<T> v3(1, 2, 3);

			v.cross(v);
			cross(v, v);
		}

		template<typename T>
		void __UseVec4() {
			Tvec4<T> v(Tvec3<T>(0), T(0));
			Tvec4<T> v1(T(0), Tvec3<T>(0));

			Tvec4<T> v2(Tvec2<T>(0), Tvec2<T>(0));
			Tvec4<T> v3(Tvec2<T>(0), T(0), T(0));
			Tvec4<T> v4(T(0), Tvec2<T>(0), T(0));
			Tvec4<T> v5(T(0), T(0), Tvec2<T>(0));

			Tvec4<T> v6(1, 2, 3, 4);
		}

		template<typename T>
		void __UseMat2() {
 			Tmat2<T> m(Tvec2<T>(0), Tvec2<T>(0));
			m.det();
			m * m;
			m *= m;
		}

		template<typename T>
		void __UseMat3() {
			Tmat3<T> m(Tvec3<T>(0), Tvec3<T>(0), Tvec3<T>(0));
			m.det();
			m* m;
			m *= m;
		}

		template<typename T>
		void __UseMat4() {
			Tmat4<T> m(Tvec4<T>(0), Tvec4<T>(0), Tvec4<T>(0), Tvec4<T>(0));
			m.det();
			m* m;
			m *= m;
		}

		template<typename T>
		void __UseMat3x2() {
			Tmat3x2<T> m(Tvec2<T>(0), Tvec2<T>(0), Tvec2<T>(0));
		}

		void __UseMath() {
			__UseVec2General<float>();
			__UseVec3General<float>();
			__UseVec4General<float>();
					 
			__UseVec2General<double>();
			__UseVec3General<double>();
			__UseVec4General<double>();
					 
			__UseVec2General<int>();
			__UseVec3General<int>();
			__UseVec4General<int>();
					 
			__UseMat2General<float>();
			__UseMat3General<float>();
			__UseMat4General<float>();
			__UseMat3x2General<float>();

			__UseMat2General<double>();
			__UseMat3General<double>();
			__UseMat4General<double>();
			__UseMat3x2General<double>();

			__UseMat2General<int>();
			__UseMat3General<int>();
			__UseMat4General<int>();
			__UseMat3x2General<double>();


			__UseVec2<float>();
			__UseVec3<float>();
			__UseVec4<float>();

			__UseVec2<double>();
			__UseVec3<double>();
			__UseVec4<double>();

			__UseVec2<int>();
			__UseVec3<int>();
			__UseVec4<int>();

			__UseMat2<float>();
			__UseMat3<float>();
			__UseMat4<float>();
			__UseMat3x2<float>();

			__UseMat2<double>();
			__UseMat3<double>();
			__UseMat4<double>();
			__UseMat3x2<double>();

			__UseMat2<int>();
			__UseMat3<int>();
			__UseMat4<int>();
			__UseMat3x2<int>();

			Tmat4<double> mat;
		}
	}
}