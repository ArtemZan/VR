#pragma once

namespace VR
{
	struct MeshContainer : public Object
	{
	protected:
		Material m_material;

	public:
		MeshContainer(const Material& material);
		~MeshContainer();

		//Transformation

		inline void Transform(const math::mat3& transform) {
			GetGeometry().Transform(transform);
		}


		void SetColor(const math::vec4& color);

		inline Material& GetMaterial() { return m_material; }
		inline const Material& GetMaterial() const { return m_material; }

		virtual Geometry& GetGeometry() = 0; // { return *std::make_unique<Geometry2D>().get(); }
		virtual const Geometry& GetGeometry() const = 0; // { return *std::make_unique<Geometry2D>().get();; }
		//virtual void SetGeometry(std::unique_ptr<Geometry>& geometry) = 0;


		//inline math::vec4& GetColor(size_t vertex) const;
	};

	struct Mesh2DContainer : public MeshContainer, Object2D
	{
	private:
		Geometry2D m_geometry;


	public:
		Mesh2DContainer();

		Mesh2DContainer(const Mesh2DContainer& mesh);

		Mesh2DContainer(const Geometry2D& geometry);

		Mesh2DContainer(const Material2D& material);

		Mesh2DContainer(const Material2D& material, const Geometry2D& geometry);

		/*void Line(float length, float width, float border_radius, size_t border_sections = -1);
		void Line(const math::vec2& start, const math::vec2& end, float width, float border_radius, size_t border_sections = -1);
		void Curve(const std::vector<math::vec2>& points, float width, float border_radius, size_t border_sections = -1);
		void BezierCurve(const std::vector<math::vec2>& pivot_points, float width, int quality, float border_radius, size_t border_sections = -1);

		void Shape(const uint8_t* vertices, size_t vert_size, const uint32_t* indices, size_t ind_count);
		void Shape(const Geometry& geo);*/

		inline Geometry2D& GetGeometry() override { return m_geometry; }
		inline const Geometry2D& GetGeometry() const override { return m_geometry; }
		void SetGeometry(const Geometry2D& geometry) { m_geometry = geometry; }
		void SetGeometry(const Geometry2D&& geometry) { m_geometry = geometry; }


		inline void Transform(const math::mat2& transform) { m_geometry.Transform(transform); }
		inline void Transform(const math::mat3& transform) { m_geometry.Transform(transform); }

		void Move(const math::vec2& bias);
		void MoveTo(const math::vec2& new_pos);

		void Rotate(const math::vec2& center, float angle);

		void Scale(const math::vec2& scale, const math::vec2& center);
		void Scale(const math::vec2& scale);
		void SetScale(const math::vec2& scale) override;
		void SetScale(const math::vec2& scale, const math::vec2& center);
		const math::vec2& GetScale() const override { return m_geometry.GetScale(); }

		inline void SetPos(const math::vec2& new_pos) override { MoveTo(new_pos); }
		inline const math::vec2& GetPos() const override { return m_geometry.GetPos(); }

		bool IsHovered(const math::mat3& camera_view = 1.f) const;
		bool IsHovered(const math::mat3x2& camera_view = 1.f) const;

	private:

		math::vec2& GetPos(size_t vertex);
	};

	struct Mesh3DContainer : public MeshContainer, Object3D
	{
		Mesh3DContainer(const Material& material);

		Mesh3DContainer(const Mesh3DContainer& mesh);
	protected:

	private:
		Geometry3D m_geometry;

	public:
		void Cube(float size);
		void Box(const math::vec3& size);


		inline void Transform(const math::mat4& transform) { m_geometry.Transform(transform); }

		void Move(const math::vec3& bias);
		void MoveTo(const math::vec3& new_pos);

		inline const math::vec3& GetPos() const { return m_geometry.GetPos(); }
		inline void SetPos(const math::vec3& pos) { m_geometry.SetPos(pos); }

		void Rotate(const math::vec3& axis, const math::vec3& center, float angle);

		void Scale(const math::vec3& scale, const math::vec3& center);
		void Scale(const math::vec3& scale);
		void SetScale(const math::vec3& scale);
		void SetScale(const math::vec3& scale, const math::vec3& center);

		inline const math::vec3& GetScale() const override { return m_geometry.GetScale(); }

		void CreateNormals();
		void ShadeSmooth(float distance_threshold = 1e-6);

		bool IsHovered(const math::mat4& mvp = 1.f) const;


		inline Geometry3D& GetGeometry() override { return m_geometry; }
		inline const Geometry3D& GetGeometry() const override { return m_geometry; }
		inline void SetGeometry(const Geometry3D& geometry) { m_geometry = geometry; }

	};

}
