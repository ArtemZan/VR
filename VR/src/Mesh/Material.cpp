#include "pch.h"
#include "VR.h"

namespace VR
{
	std::vector<std::pair<std::string, gl::Shader*>> Material::shaders;
	std::vector<gl::AttribLayout> Material::layouts;


	Material::Material(const char* shader_path, const gl::AttribLayout& layout)
	{
		SetShader(shader_path);

		SetLayout(layout);
	}

	Material::Material(const char* shader_path)
	{
		SetShader(shader_path);
		SetLayout({});
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

	int Material::FindLayout(const gl::AttribLayout& layout)
	{
		int id = 0;
		for (auto& _layout : layouts)
		{
			if (_layout.GetAttributes().size() == layout.GetAttributes().size())
			{
				auto attribs = layout.GetAttributes();
				auto _attribs = _layout.GetAttributes();

				bool same = true;

				for (int i = 0; i < attribs.size(); i++)
				{
					if (attribs[i].type != _attribs[i].type)
					{
						same = false;
					}
				}

				if (same)
				{
					return id;
				}
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

	void Material::SetLayout(const gl::AttribLayout& layout)
	{
		m_layoutId = FindLayout(layout);

		if (m_layoutId == -1)
		{
			layouts.push_back(layout);
			m_layoutId = layouts.size() - 1;
		}
	}

#define AttribSetterInit\
	const std::vector<gl::VertexAttrib>& attribs = GetLayout().GetAttributes(); \
	if (attribs.size() <= pos)																			 \
	{																										 \
		std::cout << "Attribute position out of range\n";													 \
		return false;																						 \
	}

	bool Material::SetColorOffset(size_t pos)
	{
		AttribSetterInit

		if (attribs[pos].count != 4 || attribs[pos].type != GL_FLOAT)
		{
			std::cout << "Attribute at given position cannot be color\n";
			return false;
		}

		props.attribsPos.color = pos;
		props.attribsOffsets.color = GetLayout().GetOffset(pos);

		return true;
	}

	bool Material::SetPosOffset(size_t pos)
	{
		AttribSetterInit

		if (attribs[pos].type != GL_FLOAT)
		{
			std::cout << "Attribute at given position cannot be position\n";
			return false;
		}

		if (attribs[pos].count == 3)
		{
			props._3d = true;
		}

		if (attribs[pos].count == 2)
		{
			props._3d = false;
		}

		if (attribs[pos].count == 2 || attribs[pos].count == 3)
		{
			props.attribsPos.pos = pos;
			props.attribsOffsets.pos = GetLayout().GetOffset(pos);
			return true;
		}

		std::cout << "Attribute at given position cannot be position (invalid dimension)\n";
		return false;
	}

	bool Material::SetNormalOffset(size_t pos)
	{
		AttribSetterInit
		if (attribs[pos].type != GL_FLOAT)
		{
			std::cout << "Attribute at given position cannot be normal\n";
			return false;
		}

		if (attribs[pos].count == 3)
		{
			if (!props._3d)
			{
				std::cout << "Warning: set position attribute before setting normal attribute\n";
			}

			props._3d = true;
		}

		if (attribs[pos].count == 2)
		{
			if (props._3d)
			{
				std::cout << "Warning: set position attribute before setting normal attribute\n";
			}
			props._3d = false;
		}

		if (attribs[pos].count == 2 || attribs[pos].count == 3)
		{
			props.attribsPos.normal = pos;
			props.attribsOffsets.normal = GetLayout().GetOffset(pos);
			return true;
		}

		std::cout << "Attribute at given position cannot be normal (invalid dimension)\n";
		return false;
	}

#define TRY_TO_GET_OFFSET(data) 										   \
	if (props.attribsOffsets.data == -1)								   \
	{																	   \
		std::cout << "Error: " << #data << " offset hasn't been set\n";	   \
		return 0;														   \
	}																	   \
	return props.attribsOffsets.data;

	int Material::GetColorOffset() const
	{
		TRY_TO_GET_OFFSET(color);
	}

	int Material::GetPosOffset() const
	{
		TRY_TO_GET_OFFSET(pos);
	}

	int Material::GetNormalOffset() const
	{
		TRY_TO_GET_OFFSET(normal);
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


	Material2D::Material2D()
		:Material("C:\\Users\\Professional\\Documents\\VisualStudio\\Fun\\VR\\VR\\res\\Shaders\\2D.shader")
	{
		math::mat3x2 transform(1);
		SetShaderUniform("transform", transform);

		PushAttrib<float>(2);
		PushAttrib<float>(4);

		SetPosOffset(0);
		SetColorOffset(1);
	}
}