#pragma once

#define RIGHT_HANDED

namespace VR
{
	namespace math
	{

		constexpr double PI = 3.14159265359;

		template<typename T>
		struct Tmat2;

		template<typename T>
		struct Tmat3;

		template<typename T>
		struct Tmat4;

		template<typename T>
		struct Tvec2;

		template<typename T>
		struct Tvec3;

		template<typename T>
		struct Tvec4;


		template <typename T = float>
		struct Tvec2 {
			Tvec2(T scale = 0);
			Tvec2(T x, T y);

			template<typename SrcT>
			Tvec2(const Tvec2<SrcT>& vec)
				:x(vec.x), y(vec.y)
			{

			}

			template<typename SrcT>
			Tvec2(const Tvec3<SrcT>& vec)
				: x(vec.x), y(vec.y)
			{

			}

			union
			{
				T x, s, r;
			};

			union
			{
				T y, t, g;
			};

			Tvec2& operator=(const Tvec2& vec);

			Tvec2 operator*(T scale)			const;
			Tvec2 operator*(const Tvec2& vec) const;

			Tvec2 operator/(T scale)			const;
			Tvec2 operator/(const Tvec2& vec) const;

			Tvec2 operator+(const Tvec2& vec) const;
			Tvec2 operator-(const Tvec2& vec) const;
			Tvec2 operator-()				const;


			Tvec2& operator*=(T scale);
			Tvec2& operator*=(const Tvec2& vec);
			Tvec2& operator*=(const Tmat2<T>& matrix);

			Tvec2& operator/=(T scale);
			Tvec2& operator/=(const Tvec2& vec);

			Tvec2& operator+=(const Tvec2& vec);
			Tvec2& operator-=(const Tvec2& vec);


			Tvec2 normalize() const;
			T distance(const Tvec2& vec) const;
			T magnitude() const;
			T cross(const Tvec2& vec) const;
			T dot(const Tvec2& vec) const;
			T cos(const Tvec2& vec) const;
		};

		template<typename T>
		Tvec2<T> normalize(const math::Tvec2<T>& vec);

		template<typename T>
		inline std::ostream& operator<<(std::ostream& stream, const Tvec2<T>& vec)
		{
			stream << "[" << vec.x << " " << vec.y << "]";
			return stream;
		}


		template<typename T = float>
		struct Tvec3
		{
			Tvec3(T scale = 0);
			Tvec3(T x, T y, T z);
			Tvec3(const Tvec2<T>& vec, T z);
			Tvec3(T x, const Tvec2<T>& vec);

			template<typename SrcT>
			Tvec3(const Tvec3<SrcT>& vec)
				:x(vec.x), y(vec.y), z(vec.z)
			{

			}

			Tvec3(const Tvec4<T>& vec)
				:x(vec.x), y(vec.y), z(vec.z)
			{

			}

			union
			{
				T x, s, r;
			};

			union
			{
				T y, t, g;
			};

			union
			{
				T z, p, b;
			};


			Tvec3& operator=(const Tvec3& vec);

			Tvec3 operator*(T k)			const;
			Tvec3 operator*(const Tvec3& vec)	const;
			Tvec3 operator/(T k)			const;
			Tvec3 operator/(const Tvec3& vec)	const;
			Tvec3 operator+(const Tvec3& vec)	const;
			Tvec3 operator-(const Tvec3& vec)	const;
			Tvec3 operator-()				const;

			Tvec3& operator*=(T scale);
			Tvec3& operator*=(const Tvec3& vec);
			Tvec3& operator*=(const Tmat3<T>& matrix);

			Tvec3& operator/=(T scale);
			Tvec3& operator/=(const Tvec3& vec);

			Tvec3& operator+=(const Tvec3& vec);
			Tvec3& operator-=(const Tvec3& vec);

			Tvec3 normalize() const;
			T distance(const Tvec3& vec) const;
			T magnitude() const;
			T dot(const Tvec3& v) const;
			Tvec3 cross(const Tvec3& v) const;
		};

		template<typename T>
		Tvec3<T> normalize(const math::Tvec3<T>& vec);

		template<typename T>
		inline std::ostream& operator<<(std::ostream& stream, const Tvec3<T>& vec)
		{
			stream << "[" << vec.x << " " << vec.y << " " << vec.z << "]";
			return stream;
		}

		template<typename T>
		Tvec3<T> cross(const math::Tvec3<T>& vec1, const math::Tvec3<T>& vec2);


		template<typename T = float>
		struct Tvec4
		{
			Tvec4(T scale = 0);
			Tvec4(T x, T y, T z, T w);

			Tvec4(const Tvec2<T>& vec, T z, T w);
			Tvec4(T x, const Tvec2<T>& vec, T w);
			Tvec4(T x, T y, const Tvec2<T>& vec);
			Tvec4(const Tvec2<T>& vec1, const Tvec2<T>& vec2);

			Tvec4(const Tvec3<T>& vec, T w);
			Tvec4(T x, const Tvec3<T>& vec);

			template<typename SrcT>
			Tvec4(const Tvec4<SrcT>& vec)
				: x(vec.x), y(vec.y), z(vec.z), w(vec.w)
			{

			}


			union
			{
				T x, s, r;
			};

			union
			{
				T y, t, g;
			};

			union
			{
				T z, p, b;
			};

			union
			{
				T w, q, a;
			};


			Tvec4& operator=(const Tvec4& vec);

			Tvec4 operator*(T scale)			const;
			Tvec4 operator*(const Tvec4& vec)	const;
			Tvec4 operator/(T scale)			const;
			Tvec4 operator/(const Tvec4& vec)	const;
			Tvec4 operator+(const Tvec4& vec)	const;
			Tvec4 operator-(const Tvec4& vec)	const;
			Tvec4 operator-() const;

			Tvec4& operator*=(T scale);
			Tvec4& operator*=(const Tvec4& vec);
			Tvec4& operator*=(const Tmat4<T>& matrix);

			Tvec4& operator/=(T scale);
			Tvec4& operator/=(const Tvec4& vec);

			Tvec4& operator+=(const Tvec4& vec);
			Tvec4& operator-=(const Tvec4& vec);

			Tvec4 normalize() const;
			T distance(const Tvec4& vec) const;
			T magnitude() const;
			//float cross(const Tvec4& vec) const;
			T dot(const Tvec4& vec) const;
			T cos(const Tvec4& vec) const;
		};

		template<typename T>
		inline std::ostream& operator<<(std::ostream& stream, const Tvec4<T>& vec)
		{
			stream << "[" << vec.x << " " << vec.y << " " << vec.z << " " << vec.w << "]";
			return stream;
		}


		template<typename T = double>
		struct Tmat2
		{
			Tmat2(T scale = 0);
			Tmat2(const Tvec2<T>& i, const Tvec2<T>& j);

			template<typename SrcT>
			Tmat2(const Tmat2<SrcT>& mat)
				:i(mat.i), j(mat.j)
			{

			}

			union
			{
				Tvec2<T> x, i;
			};

			union
			{
				Tvec2<T> y, j;
			};

			Tmat2& operator=(const Tmat2& mat);

			Tvec2<T> operator*(const Tvec2<T>& vec) const;

			inline T det() const { return x.cross(y); }

			Tmat2 operator*(const Tmat2& matrix) const;

			inline Tmat2& operator*=(const Tmat2& matrix) { return *this = *this * matrix; }
		};

		template<typename T = double>
		struct Tmat3
		{
			Tmat3(T scale = 0);
			Tmat3(const Tvec3<T>& i, const Tvec3<T>& j, const Tvec3<T>& k);

			template<typename SrcT>
			Tmat3(const Tmat3<SrcT>& mat)
				:i(mat.i), j(mat.j), k(mat.k)
			{

			}

			union
			{
				Tvec3<T> x, i;
			};

			union
			{
				Tvec3<T> y, j;
			};

			union
			{
				Tvec3<T> z, k;
			};

			Tmat3& operator=(const Tmat3& mat);

			Tvec3<T> operator*(const Tvec3<T>& vec) const;

			inline T det() const { return x.cross(y).dot(z); }

			Tmat3 operator*(const Tmat3& matrix) const;

			inline Tmat3& operator*=(const Tmat3& matrix) { return *this = *this * matrix; }
		};

		template<typename T = double>
		struct Tmat4
		{
			Tmat4();
			Tmat4(T scale);
			Tmat4(const Tvec4<T>& x, const Tvec4<T>& y, const Tvec4<T>& z, const Tvec4<T>& w);

			template<typename SrcT>
			Tmat4(const Tmat4<SrcT>& mat)
				:i(mat.i), j(mat.j), k(mat.k), l(mat.l)
			{

			}

			union
			{
				Tvec4<T> x, i;
			};

			union
			{
				Tvec4<T> y, j;
			};

			union
			{
				Tvec4<T> z, k;
			};

			union
			{
				Tvec4<T> w, l;
			};

			Tmat4& operator=(const Tmat4& mat);

			Tvec4<T> operator*(const Tvec4<T>& vec) const;
			Tmat4 operator*(const Tmat4& matrix) const;

			T det() const;

			inline const Tmat4& operator*=(const Tmat4& matrix) { *this = *this * matrix; return *this; }
		};

		template<typename T = double>
		struct Tmat3x2
		{
			Tmat3x2(T scale = 0);

			Tmat3x2(const Tvec2<T>& i, const Tvec2<T>& j, const Tvec2<T>& k);

			template<typename SrcT>
			Tmat3x2(const Tmat3x2<SrcT>& mat)
				:i(mat.i), j(mat.j), k(mat.k)
			{

			}

			union
			{
				Tvec2<T> x, i;
			};

			union
			{
				Tvec2<T> y, j;
			};

			union
			{
				Tvec2<T> z, k;
			};

			Tmat3x2& operator=(const Tmat3x2& mat);
		};



		/*template<>
		struct Tvec2<> {

		};*/


		using vec2f = Tvec2<>;
		using vec3f = Tvec3<>;
		using vec4f = Tvec4<>;


		/*template<>
		struct Tvec2<double>
		{

		};*/

		/*template<>
		struct Tvec3<double> {

		};

		template<>
		struct Tvec4<double> {

		};*/

		using vec2d = Tvec2<double>;
		using vec3d = Tvec3<double>;
		using vec4d = Tvec4<double>;


		/*template<>
		struct Tvec2<int> {

		};

		template<>
		struct Tvec3<int> {

		};

		template<>
		struct Tvec4<int> {

		};*/

		using vec2i = Tvec2<int>;
		using vec3i = Tvec3<int>;
		using vec4i = Tvec4<int>;

		using vec2 = Tvec2<>;
		using vec3 = Tvec3<>;
		using vec4 = Tvec4<>;



		/*template<>
		struct Tmat2<float> {

		};

		template<>
		struct Tmat3<float> {

		};

		template<>
		struct Tmat4<float> {

		};

		template<>
		struct Tmat3x2<float> {

		};*/

		using mat2f = Tmat2<float>;
		using mat3f = Tmat3<float>;
		using mat4f = Tmat4<float>;
		using mat3x2f = Tmat3x2<float>;


		/*template<>
		struct Tmat2<> {

		};

		template<>
		struct Tmat3<> {

		};

		template<>
		struct Tmat4<> {

		};*/

		using mat2d = Tmat2<>;
		using mat3d = Tmat3<>;
		using mat4d = Tmat4<>;
		using mat3x2d = Tmat3x2<>;


		/*template<>
		struct Tmat2<int> {

		};

		template<>
		struct Tmat3<int> {

		};

		template<>
		struct Tmat4<int> {

		};*/

		using mat2i = Tmat2<int>;
		using mat3i = Tmat3<int>;
		using mat4i = Tmat4<int>;
		using mat3x2i = Tmat3x2<int>;


		using mat2 = Tmat2<>;
		using mat3 = Tmat3<>;
		using mat4 = Tmat4<>;
		using mat3x2 = Tmat3x2<>;




		mat4 perspective(float fov, float aspect, float near, float far);

		mat4 lookAt(const vec3& eye, const vec3& dir, const vec3& up);

		mat3 rotate(const vec3& axis, float angle);

		mat2 rotate(float angle);


		//Area of triangle
		inline double area(const vec2& A, const vec2& B, const vec2& C)
		{
			return abs((A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y)) / 2);
		}

		//Returns whether the point is inside the triangle
		inline bool IsInside(const vec2& A, const vec2& B, const vec2& C, const vec2& point) {
			return (int)round(10000 * area(A, B, C)) == (int)round(10000 * (area(A, B, point) + area(A, C, point) + area(B, C, point)));
		}

		/// <param name="vertices">: vertices as an array of unsigned chars. If position isn't the first attribute
		/// in vertex, "vertices" should point to x coordinate of the first vertex!</param>
		/// <param name="stride">: the size of one vertex (in bytes)</param>
		/// <param name="indices">: array of indices used to draw the figure</param>
		/// <returns>Whether the point is inside the object defined by given vertices</returns>
		template <typename XType = float, typename YType = XType>
		bool IsInside(vec2 point, const uint8_t* vertices, size_t stride, const unsigned int* indices, size_t ind_count)
		{
			ind_count--;
			while (ind_count >= 2 && ind_count != size_t(-1))
			{
				if (IsInside(
					Tvec2(*(const XType*)(vertices + indices[ind_count] * stride), *(const YType*)(vertices + indices[ind_count] * stride + sizeof(XType))),
					Tvec2(*(const XType*)(vertices + indices[ind_count - 1] * stride), *(const YType*)(vertices + indices[ind_count - 1] * stride + sizeof(XType))),
					Tvec2(*(const XType*)(vertices + indices[ind_count - 2] * stride), *(const YType*)(vertices + indices[ind_count - 2] * stride + sizeof(XType))),
					point))
				{
					return true;
				}

				ind_count -= 3;
			}

			return false;
		}


		/// <summary>
		/// Changes some bits of the dst so that they separetely have same value as data
		/// </summary>
		/// <param name="size_in_bits">: how much bits will be modified </param>
		/// <param name="dst_offset">: offset from the begining of the dst</param>
		void SetBits(uint8_t* dst, size_t size_in_bits, uint8_t data, size_t dst_offset = 0);

		/// <summary>
		/// Changes some bits of the dst so that they separetely have same value as data
		/// </summary>
		/// <param name="size_in_bits">: how much bits will be modified </param>
		/// <param name="dst_offset">: offset from the begining of the dst</param>
		void SetBits(uint16_t* dst, size_t size_in_bits, uint16_t data, size_t dst_offset = 0);

		/// <summary>
		/// Changes some bits of the dst so that they separetely have same value as data
		/// </summary>
		/// <param name="size_in_bits">: how much bits will be modified </param>
		/// <param name="dst_offset">: offset from the begining of the dst</param>
		void SetBits(uint32_t* dst, size_t size_in_bits, uint32_t data, size_t dst_offset = 0);

		/// <summary>
		/// Changes some bits of the dst so that they separetely have same value as data
		/// </summary>
		/// <param name="size_in_bits">: how much bits will be modified </param>
		/// <param name="dst_offset">: offset from the begining of the dst</param>
		void SetBits(uint64_t* dst, size_t size_in_bits, uint64_t data, size_t dst_offset = 0);

		template<typename T>
		inline void Equal(uint8_t* buffer, T data)
		{
			*(T*)buffer = data;
		}
	}
}

