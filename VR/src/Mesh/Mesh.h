#pragma once

namespace VR
{
	struct Mesh
	{
		Mesh(const Material& material);
		~Mesh();


		//Transformation

		//to do
		void Transform(const math::mat4& transform);
		void Transform(const math::mat3& transform);
		void Transform(const math::mat2& transform);

		
		void SetColor(const math::vec4& color);

		Material material;
		Geometry geometry;
	};

	struct Mesh2D : public Mesh
	{
		Mesh2D()
			:Mesh(Material2D())
		{

		}


		void Square(float size);
		void Rect(const math::vec2& size);
		void Line(float length, float width, float border_radius, size_t border_sections = -1);
		void Line(const math::vec2& start, const math::vec2& end, float width, float border_radius, size_t border_sections = -1);
		void BezierCurve(const std::vector<math::vec2>& points);

		void Shape(const uint8_t* vertices, size_t vert_size, const uint32_t* indices, size_t ind_count);
		void Shape(const Geometry& geo);


		void Move(const math::vec2& bias);
		void MoveTo(const math::vec2& new_pos);

		void Rotate(const math::vec2& center, float angle);

		void Scale(const math::vec2& scale, const math::vec2& center);
		void Scale(const math::vec2& scale);
		void SetScale(const math::vec2& scale);
		void SetScale(const math::vec2& scale, const math::vec2& center);


		bool IsHovered(const math::mat3& camera_view = 1.f) const;
		bool IsHovered(const math::mat3x2& camera_view = 1.f) const;

		inline const math::vec2& Pos() const { return pos; }
		inline const math::vec2& Size() const { return size; }

	private:
		math::vec2 pos;
		math::vec2 size;
	};

	struct Mesh3D : public Mesh
	{
	protected:
		Mesh3D(const Material& material);

	public:
		void Cube(float size);
		void Box(const math::vec3& size);

		void Shape(const uint8_t* vertices, size_t vert_size, const uint32_t* indices, size_t ind_count);
		void Shape(const Geometry& geo);


		void Move(const math::vec3& bias);
		void MoveTo(const math::vec3& new_pos);

		void Rotate(const math::vec3& axis, const math::vec3& center, float angle);

		void Scale(const math::vec3& scale, const math::vec3& center);
		void Scale(const math::vec3& scale);
		void SetScale(const math::vec3& scale);
		void SetScale(const math::vec3& scale, const math::vec3& center);


		bool IsHovered(const math::mat4& mvp = 1.f) const;

		inline const math::vec3& Pos() const { return pos; }
		inline const math::vec3& Size() const { return size; }

	protected:
		math::vec3 pos;
		math::vec3 size;
	};


	struct Mesh3DLambert : public Mesh3D
	{
		Mesh3DLambert()
			:Mesh3D(Material3DLambert())
		{

		}
	};

	struct Mesh3DColor : public Mesh3D
	{
		Mesh3DColor()
			:Mesh3D(Material3DColor())
		{

		}
	};
}
