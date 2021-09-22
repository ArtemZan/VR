#pragma once

namespace VR
{
	class Vec
	{
		float* data = nullptr;
		size_t size = 0;

		void Clear();

	public:
		Vec();
		Vec(const math::vec2& vec);
		Vec(const math::vec3& vec);
		Vec(const Vec& vec);
		Vec& operator=(const Vec& vec);
		Vec& operator=(const math::vec2& vec);
		Vec& operator=(const math::vec3& vec);
		~Vec();

		inline bool IsSet() const { return size; }
		inline bool Is2D() const { return size == 2; }
		inline bool Is3D() const { return size == 3; }

		inline math::vec2& Get2D() const 
		{
			if (size != 2)
			{
				std::cout << "Failed to get vector\n";
			}
			return *(math::vec2*)data;
		}


		inline math::vec3& Get3D() const
		{
			if (size != 3)
			{
				std::cout << "Failed to get vector\n";
			}
			return *(math::vec3*)data;
		}
	};

	struct Mesh
	{
		friend class Object;
		friend class Object2D;
		friend class Object3D;

		Mesh(const Material& material);
		~Mesh();


		//Transformation

		//to do
		void Transform(const math::mat4& transform);
		void Transform(const math::mat3& transform);
		void Transform(const math::mat2& transform);

		void Move(const math::vec3& bias);
		void Move(const math::vec2& bias);
		void MoveTo(const math::vec3& new_pos);
		void MoveTo(const math::vec2& new_pos);

		void Rotate(const math::vec3& axis, const math::vec3& center, float angle);
		void Rotate(const math::vec2& center, float angle);

		void Scale(const math::vec3& scale, const math::vec3& center);
		void Scale(const math::vec2& scale, const math::vec2& center);
		void Scale(const math::vec3& scale);
		void Scale(const math::vec2& scale);
		void SetScale(const math::vec2& scale);
		void SetScale(const math::vec3& scale);
		void SetScale(const math::vec3& scale, const math::vec3& center);
		void SetScale(const math::vec2& scale, const math::vec2& center);

		//Shape generation

		//2D
		void Square(float size);
		void Rect(const math::vec2& size);
		void Line(float length, float width, float border_radius, size_t border_sections = -1);
		void BezierCurve(const std::vector<math::vec2>& points);

		void Shape2D(const uint8_t* vertices, size_t vert_size, const uint32_t* indices, size_t ind_count);
		void Shape2D(const Geometry& geo);

		//3D
		void Cube(float size);
		void Box(const math::vec3& size);

		void Shape3D(const uint8_t* vertices, size_t vert_size, const uint32_t* indices, size_t ind_count);
		void Shape3D(const Geometry& geo);


		bool IsHovered(const math::mat4& mvp) const;
		bool IsHovered(const math::mat3& camera_view) const;

		void SetColor(const math::vec4& color);

		Material material;
		Geometry geometry;

	private:
		Vec pos;
		Vec size;
	};
}
