#include "pch.h"
#include "VR.h"

namespace VR
{
	std::vector<std::pair<std::string, gl::Shader*>> Material::shaders;


	Material::Material(const char* shader_path)
	{
		SetShader(shader_path);
	}

	/*Material::Material(const Material& mat)
	{
		std::cout << "Material::Material(const Material& mat) :) \n";
	}*/


	int Material::FindShader(const std::string& path)
	{
		int id = 0;
		for (auto& [_path, shader] : shaders)
		{
			if (_path == path)
			{
				m_shader = shader;
				return id;
			}

			id++;
		}

		return -1;
	}


	void Material::DeleteShaders()
	{
		for (auto& [path, shader] : shaders)
		{
			delete shader;
		}

		shaders.clear();
	}

	void Material::SetShader(const std::string& path)
	{
		m_shaderId = FindShader(path);

		if (m_shaderId == -1)
		{
			shaders.push_back(std::pair<std::string, gl::Shader*>(path, new gl::Shader(path.c_str())));
			m_shaderId = shaders.size() - 1;
		}
		
		m_shader = shaders[m_shaderId].second;
	}



	void Material::SetShaderUniforms()
	{
		//std::unique_ptr<gl::Shader> shader;
#define SET_UNIFORMS(map) for (auto& [name, value] : map)\
			m_shader->SetUniform(name.c_str(), value);

		SET_UNIFORMS(ui);
		SET_UNIFORMS(uf);
		SET_UNIFORMS(uv2);
		SET_UNIFORMS(uv3);
		SET_UNIFORMS(um3);
		SET_UNIFORMS(um4);
		SET_UNIFORMS(um3x2);

		for (auto [name, value] : uiv)
			m_shader->SetUniform(name.c_str(), value.first.data(), value.second);
	}
	

	void Material::SetShaderUniform(const std::string& name, const int* data, size_t count)
	{
		std::pair<std::vector<int>, size_t> pair({}, count);
		std::initializer_list<int> initList(data, data + count);
		pair.first.insert(pair.first.begin(), initList);
		uiv[name] = pair;
	}

	bool Material::operator==(const Material& material)
	{
		return GetShaderId() == material.GetShaderId(); // To do
	}


	Material2D::Material2D(const char* shader_path)
		:Material(shader_path)
	{
		SetShaderUniform("transform", math::mat3x2(1.0));
	}


	Material3DLambert::Material3DLambert()
		:Material("C:\\Users\\Professional\\Documents\\VisualStudio\\Fun\\VR\\VR\\res\\Shaders\\Diffuse.shader")
	{
		
	}

	Material3DColor::Material3DColor()
		:Material("C:\\Users\\Professional\\Documents\\VisualStudio\\Fun\\VR\\VR\\res\\Shaders\\Color.shader")
	{
		
	}

	Material2DColor::Material2DColor()
		: Material2D("C:\\Users\\Professional\\Documents\\VisualStudio\\Fun\\VR\\VR\\res\\Shaders\\2D.shader")
	{
	}

	Material2DTextured::Material2DTextured()
		: Material2D("C:\\Users\\Professional\\Documents\\VisualStudio\\Fun\\VR\\VR\\res\\Shaders\\2D.shader")
	{
	}
}