#pragma once
namespace VR
{
	struct Object : public Events
	{
		Mesh mesh;

		Object(const Mesh& mesh);
		Object(const Material& material);

		virtual inline void Shape(const uint8_t* vertices, size_t vert_size, const uint32_t* indices, size_t ind_count) = 0;
		virtual inline void Shape(const Geometry& geo) = 0;
	};

	struct Object3D : public Object
	{
		Object3D();
		Object3D(const Material& material);

		inline void Cube(float size) { mesh.Cube(size); }
		inline void Box(math::vec3 size) { mesh.Box(size); }

		inline void Move(const math::vec3& bias)
		{
			Move(bias);
		}

		inline void MoveTo(const math::vec3& new_pos)
		{
			mesh.MoveTo(new_pos);
		}

		inline void Scale(const math::vec3& scale)
		{
			mesh.Scale(scale);
		}

		inline math::vec3 Pos() const { return mesh.pos.Get3D(); }
		inline math::vec3 Size() const { return mesh.size.Get3D(); }
		//inline math::vec3 Dir() const { return mesh.dir.Get3D(); }

		inline void Shape(const uint8_t* vertices, size_t vert_size, const uint32_t* indices, size_t ind_count) override
		{
			mesh.Shape3D(vertices, vert_size, indices, ind_count);
		}

		inline void Shape(const Geometry& geo) override
		{
			mesh.Shape3D(geo);
		}
	};

	struct Object2D : public Object
	{
		Object2D();
		Object2D(const Material& material);

		inline void Square(float size) { mesh.Square(size); }
		inline void Rect(math::vec2 size) { mesh.Rect(size); }
		inline void Shape(const uint8_t* vertices, size_t vert_size, const uint32_t* indices, size_t ind_count) override
		{
			mesh.Shape2D(vertices, vert_size, indices, ind_count);
		}

		inline void Shape(const Geometry& geo) override
		{
			mesh.Shape2D(geo);
		}

		inline void Move(const math::vec2& bias)
		{
			mesh.Move(bias);
		}

		inline void MoveTo(const math::vec2& new_pos)
		{
			mesh.MoveTo(new_pos);
		}

		inline void Scale(const math::vec2& scale)
		{
			mesh.Scale(scale);
		}

		inline math::vec2 Pos() const { return mesh.pos.Get2D(); }
		inline math::vec2 Size() const { return mesh.size.Get2D(); }

	};
}
