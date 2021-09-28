#pragma once

namespace VR
{
	struct MeshContainer
	{
		friend class Mesh;

		Material material;
		Geometry geometry;

		MeshContainer(const Material& material, const Geometry& geometry = {});
		~MeshContainer();

	private:
	};

	struct Mesh
	{
		Mesh(const Material& material);
		Mesh(const Mesh& mesh);
		~Mesh();



		//Transformation

		//to do
		void Transform(const math::mat4& transform);
		void Transform(const math::mat3& transform);
		void Transform(const math::mat2& transform);

		
		void SetColor(const math::vec4& color);

		inline Material& GetMaterial() { return mesh->material; }
		inline Geometry& GetGeometry() { return mesh->geometry; }

		inline const Material& GetMaterial() const { return mesh->material; }
		inline const Geometry& GetGeometry() const { return mesh->geometry; }

		inline const std::shared_ptr<MeshContainer>& GetData() const { return mesh; }

	protected:

		std::shared_ptr<MeshContainer> mesh;

		inline math::vec4& GetColor(size_t vertex) const;
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
		void Curve(const std::vector<math::vec2>& points, float width, float border_radius, size_t border_sections = -1);
		void BezierCurve(const std::vector<math::vec2>& pivot_points, float width, int quality, float border_radius, size_t border_sections = -1);

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

		math::vec2& GetPos(size_t vertex);
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

		void CreateNormals();
		void ShadeSmooth(float distance_treshold = 1e-6);

		bool IsHovered(const math::mat4& mvp = 1.f) const;

		inline const math::vec3& Pos() const { return pos; }
		inline const math::vec3& Size() const { return size; }

	protected:
		math::vec3 pos;
		math::vec3 size;

		math::vec3& GetPos(size_t vertex);
		math::vec3& GetNormal(size_t vertex);
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
