#pragma once

#define RIGHT_HANDED

namespace VR
{
	namespace math
	{

		constexpr double PI = 3.14159265359;

		struct mat2;
		struct mat3;
		struct mat4;

		struct vec2;
		struct vec3;
		struct vec4;
		struct vec2d;
		struct vec3d;
		struct vec4d;
		struct vec2i;
		struct vec3i;
		struct vec4i;

#define SET_OPERATOR(OPERATOR, ARG_TYPE, ARG) inline auto& operator##OPERATOR##=(ARG_TYPE ARG) { *this = *this OPERATOR ARG; return *this; }

		struct vec2
		{
			vec2(float scale = 0);
			vec2(float x, float y);
			vec2(const vec2& vec);

			vec2(const vec2i& vec);

			vec2(const vec2d& vec);

			vec2(const vec3& vec);


			union
			{
				float x, s, r;
			};

			union
			{
				float y, t, g;
			};


			void operator=(const vec2& vec);

			vec2 operator*(float k)			const;
			vec2 operator*(const vec2& vec) const;

			vec2 operator/(float k)			const;
			vec2 operator/(const vec2& vec) const;

			vec2 operator+(const vec2& vec) const;
			vec2 operator-(const vec2& vec) const;
			vec2 operator-()				const;

			SET_OPERATOR(*, float, k);
			SET_OPERATOR(*, const vec2&, vec);
			vec2& operator*=(const mat2& matrix);
			SET_OPERATOR(/ , float, k);
			SET_OPERATOR(/ , const vec2&, vec);
			SET_OPERATOR(+, const vec2&, vec);
			SET_OPERATOR(-, const vec2&, vec);

			vec2 normalize() const;
			float distance(const vec2& vec) const;
			float magnitude() const;
			float cross(const vec2& vec) const;
			float dot(const vec2& vec) const;
			float cos(const vec2& vec) const;
		};

		vec2 normalize(const math::vec2& vec);

		inline std::ostream& operator<<(std::ostream& stream, const vec2& vec)
		{
			stream << "[" << vec.x << " " << vec.y << "]";
			return stream;
		}


		struct vec2i
		{
			vec2i();
			vec2i(int x, int y);
			vec2i(const vec2i& vec);
			vec2i(const vec2& vec);

			union
			{
				int x, s, r, width;
			};
			union
			{
				int y, t, g, height;
			};

			void operator=(const vec2i& vec);

			inline vec2i operator+(const vec2i& vec) const { return { x + vec.x, y + vec.y }; }
			inline vec2i operator-(const vec2i& vec) const { return { x - vec.x, y - vec.y }; }
			inline vec2 operator-() { return { -x, -y }; }

			SET_OPERATOR(+, const vec2i&, vec);
			SET_OPERATOR(-, const vec2i&, vec);
		};

		inline std::ostream& operator<<(std::ostream& stream, const vec2i& vec)
		{
			stream << "[" << vec.x << " " << vec.y << "]";
			return stream;
		}


		struct vec2d
		{
			vec2d(double scale = 0);
			vec2d(double x, double y);
			vec2d(const vec2d& vec);
			vec2d(const vec2& vec);

			union
			{
				double x, s, r;
			};
			union
			{
				double y, t, g;
			};

			void operator=(const vec2d& vec);

			vec2d operator*(double k) const;
			vec2d operator*(const vec2d& vec) const;

			vec2d operator/(double k) const;
			vec2d operator/(const vec2d& vec) const;
			vec2d operator+(const vec2d& vec) const;
			vec2d operator-(const vec2d& vec) const;
			vec2d operator-() const;

			SET_OPERATOR(*, double, k);
			SET_OPERATOR(*, const vec2d&, vec);
			inline vec2d& operator*=(const mat2& matrix) { *this = matrix * *this; return *this; }
			SET_OPERATOR(/ , double, k);
			SET_OPERATOR(/ , const vec2d&, vec);
			SET_OPERATOR(+, const vec2d&, vec);
			SET_OPERATOR(-, const vec2d&, vec);

			vec2d normalize() const;
			double distance(const vec2d& vec) const;
			double magnitude() const;
			double cross(const vec2d& vec) const;
			double dot(const vec2d& vec) const;
			double cos(const vec2d& vec) const;
		};

		vec2d normalize(const math::vec2d& vec);

		inline std::ostream& operator<<(std::ostream& stream, const vec2d& vec)
		{
			stream << "[" << vec.x << " " << vec.y << "]";
			return stream;
		}


		struct vec3
		{
			vec3(float scale = 0);
			vec3(float x, float y, float z);
			vec3(const vec2& vec, float z);
			vec3(float x, const vec2& vec);
			vec3(const vec3& vec);
			vec3(const vec3d& vec);

			vec3(const vec4& vec);

			union
			{
				float x, s, r;
			};
			union
			{
				float y, t, g;
			};
			union
			{
				float z, p, b;
			};


			vec3& operator=(const vec3& vec);

			vec3 operator*(float k)			const;
			vec3 operator*(const vec3& vec)	const;
			vec3 operator/(float k)			const;
			vec3 operator/(const vec3& vec)	const;
			vec3 operator+(const vec3& vec)	const;
			vec3 operator-(const vec3& vec)	const;
			vec3 operator-()				const;

			SET_OPERATOR(*, float, k);
			SET_OPERATOR(*, const vec3&, vec);
			inline vec3d operator*=(const mat3& mat) { *this = mat * vec3d(*this); }
			SET_OPERATOR(/ , float, k);
			SET_OPERATOR(/ , const vec3&, vec);
			SET_OPERATOR(+, const vec3&, vec);
			SET_OPERATOR(-, const vec3&, vec);

			vec3 normalize() const;
			float distance(const vec3& vec) const;
			float magnitude() const;
			float dot(const vec3& v) const;
			vec3 cross(const vec3& v) const;
		};

		vec3 normalize(const math::vec3& vec);

		inline std::ostream& operator<<(std::ostream& stream, const vec3& vec)
		{
			stream << "[" << vec.x << " " << vec.y << " " << vec.z << "]";
			return stream;
		}


		struct vec3d
		{
			vec3d(double scale = 0);
			vec3d(double x, double y, double z);
			vec3d(const vec2d& vec, double z);
			vec3d(double x, const vec2d& vec);
			vec3d(const vec3d& vec);
			vec3d(const vec3& vec);

			vec3d(const vec4d& vec);

			union
			{
				double x, s, r;
			};
			union
			{
				double y, t, g;
			};
			union
			{
				double z, p, b;
			};


			vec3d& operator=(const vec3& vec);

			vec3d operator*(double k)			const;
			vec3d operator*(const vec3d& vec)	const;
			vec3d operator/(double k)			const;
			vec3d operator/(const vec3d& vec)	const;
			vec3d operator+(const vec3d& vec)	const;
			vec3d operator-(const vec3d& vec)	const;
			vec3d operator-() const;

			SET_OPERATOR(*, double, k);
			SET_OPERATOR(*, const vec3&, vec);
			inline vec3d operator*=(const mat3& mat) { *this = mat * *this; }
			SET_OPERATOR(/ , double, k);
			SET_OPERATOR(/ , const vec3d&, vec);
			SET_OPERATOR(+, const vec3d&, vec);
			SET_OPERATOR(-, const vec3d&, vec);

			double dot(const vec3d& v) const;
#ifdef RIGHT_HANDED
			inline vec3d cross(const vec3d& v) const { return { z * v.y - y * v.z, x * v.z - z * v.x, y * v.x - x * v.y }; }
#else
			inline vec3d cross(const vec3d& v) const { return { y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x }; }
#endif
			vec3d normalize() const;
			double distance(const vec3d& vec) const;
			double magnitude() const;
		};

		vec3d normalize(const math::vec3d& vec);

		inline std::ostream& operator<<(std::ostream& stream, const vec3d& vec)
		{
			stream << "[" << vec.x << " " << vec.y << " " << vec.z << "]";
			return stream;
		}


		struct vec4
		{
			vec4();
			vec4(float x, float y, float z, float w);

			vec4(const vec2& vec1, const vec2& vec2);
			vec4(const vec2& vec, float z, float w);
			vec4(float x, const vec2& vec, float w);
			vec4(float x, float y, const vec2& vec);

			vec4(const vec3& vec, float w);
			vec4(float x, const vec3& vec);

			vec4(const vec4& vec);
			vec4(const vec4d& vec);


			union
			{
				float x, s, r;
			};

			union
			{
				float y, t, g;
			};

			union
			{
				float z, p, b;
			};

			union
			{
				float w, q, a;
			};


			void operator=(const vec4& vec);

			vec4 operator*(float k)			const;
			vec4 operator*(const vec4& vec)	const;
			vec4 operator/(float k)			const;
			vec4 operator/(const vec4& vec)	const;
			vec4 operator+(const vec4& vec)	const;
			vec4 operator-(const vec4& vec)	const;
			vec4 operator-() const;

			SET_OPERATOR(*, float, k);
			SET_OPERATOR(*, const vec4&, vec);
			inline vec4d operator*=(const mat4& mat) { *this = mat * vec4d(*this); }
			SET_OPERATOR(/ , float, k);
			SET_OPERATOR(/ , const vec4&, vec);
			SET_OPERATOR(+, const vec4&, vec);
			SET_OPERATOR(-, const vec4&, vec);

			vec4 normalize() const;
			float distance(const vec4& vec) const;
			float magnitude() const;
			//float cross(const vec4& vec) const;
			float dot(const vec4& vec) const;
			float cos(const vec4& vec) const;
		};

		inline std::ostream& operator<<(std::ostream& stream, const vec4& vec)
		{
			stream << "[" << vec.x << " " << vec.y << " " << vec.z << " " << vec.w << "]";
			return stream;
		}


		struct vec4d
		{
			vec4d();
			vec4d(double x, double y, double z, double w);

			vec4d(const vec2d& vec1, const vec2d& vec2);
			vec4d(const vec2d& vec, double z, double w);
			vec4d(double x, const vec2d& vec, double w);
			vec4d(double x, double y, const vec2d& vec);

			vec4d(const vec3d& vec, double w);
			vec4d(double x, const vec3d& vec);

			vec4d(const vec4d& vec);
			vec4d(const vec4& vec);

			union
			{
				double x, s, r;
			};
			union
			{
				double y, t, g;
			};
			union
			{
				double z, p, b;
			};
			union
			{
				double w, q, a;
			};

			void operator=(const vec4d& vec);

			inline vec4d operator*(double k)			const { return { x * k, y * k, z * k, w * k }; }
			inline vec4d operator*(const vec4d& vec)	const { return { x * vec.x, y * vec.y, z * vec.z, w * vec.w }; }
			inline vec4d operator/(double k)			const { return { x / k, y / k, z / k, w / k }; }
			inline vec4d operator/(const vec4d& vec)	const { return { x / vec.x, y / vec.y, z / vec.z, w / vec.w }; }
			inline vec4d operator+(const vec4d& vec)	const { return { x + vec.x, y + vec.y, z + vec.z, w + vec.w }; }
			inline vec4d operator-(const vec4d& vec)	const { return { x - vec.x, y - vec.y, z - vec.z, w + vec.w }; }
			inline vec4d operator-() const { return { -x, -y, -z, -w }; }

			SET_OPERATOR(*, double, k);
			SET_OPERATOR(*, const vec4d&, vec);
			inline vec4d operator*=(const mat4& mat) { *this = mat * *this; }
			SET_OPERATOR(/ , double, k);
			SET_OPERATOR(/ , const vec4d&, vec);
			SET_OPERATOR(+, const vec4d&, vec);
			SET_OPERATOR(-, const vec4d&, vec);

			vec4d normalize();
		};

		inline std::ostream& operator<<(std::ostream& stream, const vec4d& vec)
		{
			stream << "[" << vec.x << " " << vec.y << " " << vec.z << " " << vec.w << "]";
			return stream;
		}


		struct mat2
		{
			mat2();
			mat2(const mat2& mat);
			mat2(double scale);
			mat2(const vec2d& i, const vec2d& j);

			union
			{
				vec2d x, i;
			};

			union
			{
				vec2d y, j;
			};

			vec2d operator*(const vec2d& vec) const;

			inline float det() const { return x.cross(y); }

			const mat2& operator*(const mat2& matrix);
		};

		struct mat2f {
			mat2f();
			mat2f(const mat2f& mat);
			mat2f(const mat2& mat);

			union
			{
				vec2 x, i;
			};

			union
			{
				vec2 y, j;
			};
		};

		struct mat3
		{
			mat3();
			mat3(const mat3f& mat);
			mat3(const mat3& mat);

			mat3(double scale);
			mat3(const vec3d& x, const vec3d& y, const vec3d& z);

			union
			{
				vec3d x, i;
			};

			union
			{
				vec3d y, j;
			};

			union
			{
				vec3d z, k;
			};

			vec3d operator*(const vec3d& vec) const;

			inline float det() const { return x.cross(y).dot(z); }

			mat3 operator*(const mat3& matrix) const;
		};

		struct mat3f {
			mat3f();
			mat3f(const mat3f& mat);
			mat3f(const mat3& mat);

			union
			{
				vec3 x, i;
			};

			union
			{
				vec3 y, j;
			};

			union
			{
				vec3 z, k;
			};
		};

		struct mat4
		{
			mat4();
			mat4(const mat4f& mat);
			mat4(const mat4& mat);

			mat4(const vec4& x, const vec4& y, const vec4& z, const vec4& w);
			mat4(float scale);

			union
			{
				vec4d x, i;
			};

			union
			{
				vec4d y, j;
			};

			union
			{
				vec4d z, k;
			};

			union
			{
				vec4d w, l;
			};

			mat4& operator=(const mat4& mat);

			vec4d operator*(const vec4d& vec) const;

			mat4 operator*(const mat4& matrix) const;
			inline const void operator*=(const mat4& matrix) { *this = *this * matrix; }
		};

		struct mat4f {
			mat4f();
			mat4f(const mat4f& mat);
			mat4f(const mat4& mat);

			union
			{
				vec4 x, i;
			};

			union
			{
				vec4 y, j;
			};

			union
			{
				vec4 z, k;
			};

			union
			{
				vec4 w, l;
			};
		};

		struct mat3x2
		{
			mat3x2();
			mat3x2(float scale);

			vec2d x;
			vec2d y;
			vec2d z;
		};

		struct mat3x2f
		{
			mat3x2f();
			mat3x2f(float scale);

			vec2 x;
			vec2 y;
			vec2 z;
		};


		template <typename T>
		struct vec2 {
			union
			{
				T x, s, r;
			};

			union
			{
				T y, t, g;
			};
		};


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
					vec2(*(const XType*)(vertices + indices[ind_count] * stride), *(const YType*)(vertices + indices[ind_count] * stride + sizeof(XType))),
					vec2(*(const XType*)(vertices + indices[ind_count - 1] * stride), *(const YType*)(vertices + indices[ind_count - 1] * stride + sizeof(XType))),
					vec2(*(const XType*)(vertices + indices[ind_count - 2] * stride), *(const YType*)(vertices + indices[ind_count - 2] * stride + sizeof(XType))),
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

