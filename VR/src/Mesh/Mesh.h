#pragma once

namespace VR
{
	struct Mesh : public Object
	{
	protected:
		Material material;

	public:
		Mesh(const Material& material);
		Mesh(const Mesh& mesh) = delete;
		~Mesh();

		//Transformation

		inline void Transform(const math::mat3& transform) {
			GetGeometry().Transform(transform);
		}

		
		void SetColor(const math::vec4& color);

		inline const Material& GetMaterial() const { return material; }


	protected:

		virtual Geometry& GetGeometry() = 0;

		//inline math::vec4& GetColor(size_t vertex) const;
	};

	struct Mesh2D : public Mesh, Object2D
	{
	private:
		Geometry2D m_geometry;

	public:
		Mesh2D()
			:Mesh(Material2D())
		{
		}

		/*void Line(float length, float width, float border_radius, size_t border_sections = -1);
		void Line(const math::vec2& start, const math::vec2& end, float width, float border_radius, size_t border_sections = -1);
		void Curve(const std::vector<math::vec2>& points, float width, float border_radius, size_t border_sections = -1);
		void BezierCurve(const std::vector<math::vec2>& pivot_points, float width, int quality, float border_radius, size_t border_sections = -1);

		void Shape(const uint8_t* vertices, size_t vert_size, const uint32_t* indices, size_t ind_count);
		void Shape(const Geometry& geo);*/


		inline void Transform(const math::mat2& transform) { m_geometry.Transform(transform); }
		inline void Transform(const math::mat3& transform) { m_geometry.Transform(transform); }

		void Move(const math::vec2& bias);
		void MoveTo(const math::vec2& new_pos);

		void Rotate(const math::vec2& center, float angle);

		void Scale(const math::vec2& scale, const math::vec2& center);
		void Scale(const math::vec2& scale);
		void SetScale(const math::vec2& scale) override;
		void SetScale(const math::vec2& scale, const math::vec2& center);

		inline void SetPos(const math::vec2& new_pos) override { MoveTo(new_pos); }
		inline const math::vec2& GetPos() const override { return m_geometry.GetPos(); }

		bool IsHovered(const math::mat3& camera_view = 1.f) const;
		bool IsHovered(const math::mat3x2& camera_view = 1.f) const;

	private:

		math::vec2& GetPos(size_t vertex);
	};

	struct Mesh3D : public Mesh, Object3D
	{
	protected:
		Mesh3D(const Material& material);

	private:
		Geometry3D m_geometry;

	public:
		void Cube(float size);
		void Box(const math::vec3& size);


		inline void Transform(const math::mat4& transform) { m_geometry.Transform(transform); }

		void Move(const math::vec3& bias);
		void MoveTo(const math::vec3& new_pos);

		void Rotate(const math::vec3& axis, const math::vec3& center, float angle);

		void Scale(const math::vec3& scale, const math::vec3& center);
		void Scale(const math::vec3& scale);
		void SetScale(const math::vec3& scale);
		void SetScale(const math::vec3& scale, const math::vec3& center);

		void CreateNormals();
		void ShadeSmooth(float distance_threshold = 1e-6);

		bool IsHovered(const math::mat4& mvp = 1.f) const;



	protected:

		inline Geometry& GetGeometry() override { return m_geometry; }
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
