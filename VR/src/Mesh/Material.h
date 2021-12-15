#pragma once

namespace VR
{
	namespace shaders
	{
		constexpr const char* _2D = "C:\\Users\\Professional\\Documents\\VisualStudio\\Fun\\VR\\VR\\res\\Shaders\\2D.shader";
		constexpr const char* _3DDiffuse = "C:\\Users\\Professional\\Documents\\VisualStudio\\Fun\\VR\\VR\\res\\Shaders\\Diffuse.shader";
		constexpr const char* _3DColor = "C:\\Users\\Professional\\Documents\\VisualStudio\\Fun\\VR\\VR\\res\\Shaders\\Color.shader";
	}

	struct Material
	{
		friend class Context;

		Material(const char* shader_path);

	public:
		math::vec4 m_color;

		void SetShader(const std::string& path);
		inline size_t GetShaderId() const { return m_shaderId; }

		inline void BindShader() { m_shader->Bind(); }
		void SetShaderUniforms();

		inline void SetShaderUniform(const std::string& name, int v) { ui[name] = v; }
		inline void SetShaderUniform(const std::string& name, float v) { uf[name] = v; }
		inline void SetShaderUniform(const std::string& name, const math::vec2& v) { uv2[name] = v; }
		inline void SetShaderUniform(const std::string& name, const math::vec3& v) { uv3[name] = v; }
		void SetShaderUniform(const std::string& name, const int* data, size_t count);
		inline void SetShaderUniform(const std::string& name, const math::mat4& matrix) { um4[name] = matrix; }
		inline void SetShaderUniform(const std::string& name, const math::mat3& matrix) { um3[name] = matrix; }
		inline void SetShaderUniform(const std::string& name, const math::mat3x2& matrix) { um3x2[name] = matrix; }

		bool operator==(const Material& material);


	private:
		gl::Shader* m_shader;
		size_t m_shaderId = 0;

		std::map<std::string, int> ui;
		std::map<std::string, float> uf;
		std::map<std::string, math::vec2> uv2;
		std::map<std::string, math::vec3> uv3;
		std::map<std::string, std::pair<std::vector<int>, size_t>> uiv;
		std::map<std::string, math::mat3> um3;
		std::map<std::string, math::mat4> um4;
		std::map<std::string, math::mat3x2> um3x2;

		int FindShader(const std::string& path);

		static void DeleteShaders();

		static std::vector<std::pair<std::string, gl::Shader*>> shaders;
	};

	struct Material2D : public Material
	{
		Material2D(const char* shader_path);
	};

	struct Material2DColor : public Material2D {
		Material2DColor();
	};

	struct Material2DTextured : public Material2D {
		Material2DTextured();
	};

	struct Material3DLambert : public Material
	{
		Material3DLambert();
	};

	struct Material3DColor : public Material
	{
		Material3DColor();
	};

}