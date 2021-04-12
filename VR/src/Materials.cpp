#include "pch.h"
#include "VR.h"

namespace VR
{
	Material::Material(const char* shader, const gl::AttribLayout& layout)
		:shader(shader), attributesLayout(layout)
	{
	}

	BasicMaterial::BasicMaterial(const math::vec4& color)
		:Material("Color.shader"), color(color)
	{
		attributesLayout.Push<float>(3);
		attributesLayout.Push<float>(4);
	}

	LambertMaterial::LambertMaterial(const math::vec4& color)
		:Material("Diffuse.shader"), color(color)
	{
		attributesLayout.Push<float>(3);
		attributesLayout.Push<float>(4);
		attributesLayout.Push<float>(3);
	}

	_2DMaterial::_2DMaterial(const math::vec4& color)
		:Material("Buttons.shader"), color(color)
	{
		attributesLayout.Push<float>(2);
		attributesLayout.Push<float>(4);
	}
}