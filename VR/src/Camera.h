#pragma once

namespace VR
{
	struct Camera3D
	{
		Camera3D(float fov, float aspect, float near, float far, const math::vec3& pos = math::vec3(), const math::vec3& direction = math::vec3(0.0, 0.0, 1.0));

		void SetPosition(math::vec3 pos);
		void Move(math::vec3 dPos);

		void SetRotation(math::vec3 rot);
		void Rotate(math::vec3 axis, float angle);

		void SetFOV(float fov);
		void SetAspectRatio(float aspect);


		inline const math::vec3& Pos() const { return pos; }
		inline const math::vec3& Dir() const { return dir; }
		inline const math::mat4& View() const { return view; }
		inline const math::mat4& Proj() const { return proj; }

	private:
		inline void SetView() { view = math::lookAt(pos, dir, math::vec3(0, 1, 0)); }

		math::vec3 pos;
		math::vec3 dir;
		math::mat4 view;

		float fov;
		float aspect;
		math::mat4 proj;
	};

	namespace fit_types
	{
		enum
		{
			CENTER = 0,

			ALIGN_LEFT = 1,
			ALIGN_RIGHT = 2,
			ALIGN_TOP = 4,
			ALIGN_BOTTOM = 8,

			FIT_X = 16,
			FIT_Y = 32,
			FIT_MAX = 64,
			SCREEN = 128
		};
	}

	typedef int fit_t;

	struct Camera2D
	{
		Camera2D(float aspect = 1, const math::vec3& pos = {}, fit_t fit = fit_types::ALIGN_LEFT);

		void SetPosition(math::vec3 pos);
		void SetAspectRatio(float aspect);
		void Move(math::vec3 dPos);

		inline const math::vec3& Pos() const { return pos; }
		inline const math::mat3x2& View() const { return view; }


	private:
		void SetView();

		fit_t fit;

		float aspect;
		math::vec3 pos;
		math::mat3x2 view;
	};
}