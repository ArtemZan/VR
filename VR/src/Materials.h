#pragma once

namespace VR
{
	enum class MATERIAL_TYPE
	{
		BASIC, LAMBERT, _2D
	};

	struct Material
	{
	protected:
		Material(const char* shader, const gl::AttribLayout& layout = {});

	public:
		virtual inline MATERIAL_TYPE GetTypeID() const = 0;
		virtual inline int GetColorOffset() const = 0;

		gl::Shader* shader;
		gl::AttribLayout attributesLayout;

	private:
		static std::map<const char*, gl::Shader> shaders;
	};

	struct BasicMaterial : public Material
	{
		BasicMaterial(const math::vec4& color = {1.0, 1.0, 1.0, 1.0});

		inline MATERIAL_TYPE GetTypeID() const override { return MATERIAL_TYPE::BASIC; }
		inline int GetColorOffset() const override { return 12; }

		math::vec4 color;
	};

	struct LambertMaterial : public Material
	{
		LambertMaterial(const math::vec4& color = { 1.0, 1.0, 1.0, 1.0 });

		inline MATERIAL_TYPE GetTypeID() const override { return MATERIAL_TYPE::LAMBERT; }
		inline int GetColorOffset() const override { return 12; }

		math::vec4 color;
	};

	struct _2DMaterial : public Material
	{
		_2DMaterial(const math::vec4& color = { 1.0, 1.0, 1.0, 1.0 });

		inline MATERIAL_TYPE GetTypeID() const override { return MATERIAL_TYPE::_2D; }
		inline int GetColorOffset() const override { return 8; }

		math::vec4 color;
	};
}