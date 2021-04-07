#pragma once

namespace VR
{
    namespace math
    {
        struct mat2;
        struct mat3;
        struct mat4;


        struct vec2
        {
            vec2();
            vec2(float x, float y);
            vec2(const vec2& vec2);

            union
            {
                float x, s, r;
            };
            union
            {
                float y, t, g;
            };

            void operator=(const vec2& vec);

            vec2 operator*(const mat2& matrix) const;
            vec2 operator*(float k) const;
            inline vec2 operator+(const vec2& vec) const;

            inline void operator*=(const mat2& matrix) { *this = *this * matrix; }
            inline void operator+=(const vec2& vec) { *this = *this + vec; }

            void normalize();
        };

        vec2 normalize(const vec2& vec);

        struct vec3
        {
            vec3();
            vec3(float x, float y, float z);
            vec3(const vec3& vec3);

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


            void operator=(const vec3& vec);

            vec3 operator*(const mat3& matrix) const;
            vec3 operator*(float k) const;
            inline vec3 operator+(const vec3& vec) const;
            inline vec3 operator-(const vec3& vec) const { return vec3(x - vec.x, y - vec.y, z - vec.z); }

            inline void operator*=(const mat3& matrix) { *this = *this * matrix; }
            inline void operator+=(const vec3& vec) { *this = *this + vec; }
            inline void operator-=(const vec3& vec) { *this = *this - vec; }

            void normalize();
        };

        vec3 normalize(const vec3& vec);


        struct vec4
        {
            vec4();
            vec4(float x, float y, float z, float w);
            vec4(const vec4& vec4);

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
            vec4 operator*(const mat4& matrix) const;
            vec4 operator*(float k) const;
            vec4 operator+(const vec4& vec) const;

            inline void operator*=(const mat4& matrix) { *this = *this * matrix; }
            inline void operator+=(const vec4& vec) { *this = *this + vec; }

            void normalize();
        };

        vec4 normalize(const vec4& vec);


        struct mat2
        {
            mat2();
            mat2(float scale);

            vec2 x;
            vec2 y;

            const mat2& operator*(const mat2& matrix);
        };

        struct mat3
        {
            mat3();
            mat3(float scale);

            vec3 x;
            vec3 y;
            vec3 z;

            mat3 operator*(const mat3& matrix) const;
        };

        struct mat4
        {
            mat4();
            mat4(float scale);

            vec4 x;
            vec4 y;
            vec4 z;
            vec4 w;

            mat4 operator*(const mat4& matrix) const;
            inline const void operator*=(const mat4& matrix) { *this = *this * matrix; }
        };


        mat4 perspective(float fov, float aspect, float near, float far);

        mat4 lookAt(const vec3& eye, const vec3& dir, const vec3& up);

        mat3 rotate(const vec3& axis, float angle);


        //Area of triangle
        inline double area(const glm::vec2& A, const glm::vec2& B, const glm::vec2& C)
        {
            return abs((A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y)) / 2);
        }

        //Returns whether the point is inside the triangle
        inline bool IsInside(const glm::vec2& A, const glm::vec2& B, const glm::vec2& C, const glm::vec2& point) {
            return (int)round(10000 * area(A, B, C)) == (int)round(10000 * (area(A, B, point) + area(A, C, point) + area(B, C, point)));
        }

        /// <param name="vertices">: vertices as an array of unsigned chars. If position isn't the first attribute
        /// in vertex, "vertices" should point to x coordinate of the first vertex!</param>
        /// <param name="stride">: the size of one vertex (in bytes)</param>
        /// <param name="indices">: array of indices used to draw the figure</param>
        /// <returns>Whether the point is inside the object defined by given vertices</returns>
        template <typename XType, typename YType = XType>
        bool IsInside(glm::vec2 point, const uint8_t* vertices, size_t stride, const unsigned int* indices, size_t ind_count)
        {
            ind_count--;
            while (ind_count >= 2 && ind_count != size_t(-1))
            {
                if (IsInside(
                    glm::vec2(*(const XType*)(vertices + indices[ind_count] * stride), *(const YType*)(vertices + indices[ind_count] * stride + sizeof(XType))),
                    glm::vec2(*(const XType*)(vertices + indices[ind_count - 1] * stride), *(const YType*)(vertices + indices[ind_count - 1] * stride + sizeof(XType))),
                    glm::vec2(*(const XType*)(vertices + indices[ind_count - 2] * stride), *(const YType*)(vertices + indices[ind_count - 2] * stride + sizeof(XType))),
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

