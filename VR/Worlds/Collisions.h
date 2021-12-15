#pragma once

using namespace VR;

struct Collisions : public World
{
	class RigidBody2D : public Mesh2D
	{
	public:
		RigidBody2D(float m = 1.f)
			:m(m)
		{
			final_pos = GetPos();
		}


		void DoesCollideWith(const RigidBody2D& other)
		{

		}

		inline void ApplyForce(const math::vec2& dforce)
		{
			a += dforce / m;
		}

		inline void SetForce(const math::vec2& force)
		{
			a = force / m;
		}


		inline void ApplyAcceleration(const math::vec2& da)
		{
			a += da;
		}

		inline void SetAcceleration(const math::vec2& a)
		{
			this->a = a;
		}


		inline void ApplyVelocity(const math::vec2& dv)
		{
			v += dv;
		}

		inline void SetVelocity(const math::vec2& v)
		{
			this->v = v;
		}


		inline void SetMass(float m)
		{
			this->m = m;
		}

		inline void SetCenterOfMass(const math::vec2& center)
		{
			centerOfMass = center;
		}

		void UpdateState(double dTime)
		{
			v += a * 1e-3 * dTime;
			final_pos += v * 1e-3 * dTime;
		}

		void UpdateMesh()
		{
			MoveTo(final_pos);
		}

		void CalcCenterOfMass()
		{
			math::vec2 sum = 0;
			float area = 0;


			const Material& mat = GetMaterial();
			const Geometry2D& geo = GetGeometry();

			const int vertex_size = geo.GetVertexSize();
			const int vert_count = geo.m_data->GetVerticesSize() / vertex_size;
			const int indCount = geo.m_data->GetIndicesCount();

			for (int ind_i = 0; ind_i + 2 < indCount; ind_i += 3)
			{
				const math::vec2& A = geo.GetPos(geo.m_data->GetIndex(ind_i));
				const math::vec2& B = geo.GetPos(geo.m_data->GetIndex(ind_i + 1));
				const math::vec2& C = geo.GetPos(geo.m_data->GetIndex(ind_i + 2));

				float tr_area = math::area(A, B, C);

				sum += (A + B + C) / 3.f * tr_area;
				area += tr_area;
			}

			centerOfMass = sum / area;
		}


		float m;
		math::vec2 centerOfMass;

		math::vec2 final_pos;
		math::vec2 a;
		math::vec2 v;

	private:
	};

private:
	Camera2D camera;

	Mesh2D button;
	Mesh2D triangle;
	RigidBody2D box;

	float time = 0;


	const float amplitude = rand() % 100 / 100.f;
	const float freq = (rand() % 100 - 50) / 10 + 5;


	void OnAttach() override
	{
		AddHandler(this);
		m_scene.Render();
	}

	void OnDetach() override
	{
	}

	void OnMouseDown(int bc, int mods) override
	{
		//m_scene.Delete(button);

		if (button.IsHovered(camera.View()))
		{
			link = 0;
			Detach();
		}
	}

	void OnWindowResize(int w, int h) override
	{
		glViewport(0, 0, w, h);
		SetAspectRatio();
	}

	void OnUpdate(float dTime) override
	{
		IO* io = IO::Get();

		time += dTime / 1000.0;

		triangle;

		float dist = box.final_pos.magnitude() / 1e3;

		box.a = math::normalize(box.final_pos) * -1e4 / dist / dist;

		for (int i = 0; i < 10000; i++)
		{
			box.UpdateState(dTime * 1e-3);
		}
		box.UpdateMesh();

		//triangle.Rotate({ 0.0, 0.0 }, 0.1);

		m_scene.Render();

		MustUpdate();
	}

	void OnScroll(const math::vec2& scroll) override
	{
		if (camera.Pos().z - scroll.y > 0)
		{
			camera.Move({ 0.0, 0.0, -scroll.y * 1000.f });
		}

		SetAspectRatio();
	}

	void SetAspectRatio()
	{
		IO* io = IO::Get();
		math::vec2 wSize = io->WindowSize();

		camera.SetAspectRatio(wSize.x / wSize.y);

		button.GetMaterial().SetShaderUniform("transform", camera.View());

		m_scene.Render();
	}

public:

	Collisions()
		:camera(1.0, {}, fit_types::ALIGN_LEFT)
	{
		camera.SetPosition({ 0.0, 0.0, 1000.0 });

		SetAspectRatio();

		button.SetColor({ 0.0, 1.0, 0.0, 1.0 });
		//button.Rect(100.f);
		button.MoveTo(math::vec2( -900.f, 900.f ));
		m_scene.Add(button);

		std::vector<math::vec2> tr_points;
		tr_points.emplace_back(-250, -250);
		tr_points.emplace_back(0, 250);
		tr_points.emplace_back(250, -250);
		tr_points.emplace_back(-250, -250);

		triangle.SetColor({ 1.0, 0.0, 0.0, 0.0 });
		//triangle.Curve(tr_points, 10, 0, 0);
		m_scene.Add(triangle);

		box.final_pos.x = 5000;
		box.v.y = 1000.f;
		box.SetColor({ 0.0, 1.0, 1.0, 0.0 });
		//box.Square(1000.0);
		////box.Triangle(1.41f, 1.f, 1.f);
		box.CalcCenterOfMass();
		std::cout << box.centerOfMass << std::endl;
		m_scene.Add(box);
	}
};