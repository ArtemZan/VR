#pragma once

namespace VR
{
	struct AttribsPos
	{
		int8_t color = -1;
		int8_t pos = -1;
		int8_t normal = -1;
	};

	struct AttribsOffsets
	{
		int8_t color = -1;
		int8_t pos = -1;
		int8_t normal = -1;
	};

	struct MaterialProps
	{
		math::vec4 color;
		uint8_t textureId;
		AttribsPos attribsPos;
		AttribsOffsets attribsOffsets;
		bool _3d;
	};

	struct Material
	{
		friend class Context;

		Material(const char* shader_path, const gl::AttribLayout& layout);
		Material(const char* shader_path);
		Material(const Material& mat) = default;

	public:

		void SetShader(const std::string& path);
		inline size_t GetShaderId() const { return m_shaderId; }

		inline void BindShader() { m_shader->Bind(); }
		void SetShaderUniforms();

		void SetShaderUniform(const std::string& name, int v);
		void SetShaderUniform(const std::string& name, float v);
		void SetShaderUniform(const std::string& name, const math::vec2& v);
		void SetShaderUniform(const std::string& name, const math::vec3& v);
		void SetShaderUniform(const std::string& name, const int* data, size_t count);
		void SetShaderUniform(const std::string& name, const math::mat4& matrix);
		void SetShaderUniform(const std::string& name, const math::mat3& matrix);


		void SetLayout(const gl::AttribLayout& layout);
		inline const gl::AttribLayout& GetLayout() const { return layouts[m_layoutId]; }
		inline size_t GetVertexSize() const { return layouts[m_layoutId].GetStride(); }

		template<typename ValueT>
		inline void PushAttrib(size_t count) { layouts[m_layoutId].Push<ValueT>(count); } //To do: check for repeating layouts



		inline void SetColor(const math::vec4& color) { props.color = color; }
		inline math::vec4 GetColor() const { return props.color; }

		bool SetColorOffset(size_t pos);
		int GetColorOffset() const;
		bool SetPosOffset(size_t pos);
		int GetPosOffset() const;
		bool SetNormalOffset(size_t pos);
		int GetNormalOffset() const;
		inline bool HasNormals() const { return props.attribsPos.normal != int8_t(-1); }

		inline bool Is3D() const { return props._3d; }


	private:
		gl::Shader* m_shader;
		size_t m_shaderId = 0;
		size_t m_layoutId = 0;

		std::map<std::string, int> ui;
		std::map<std::string, float> uf;
		std::map<std::string, math::vec2> uv2;
		std::map<std::string, math::vec3> uv3;
		std::map<std::string, std::pair<std::vector<int>, size_t>> uiv;
		std::map<std::string, math::mat3> um3;
		std::map<std::string, math::mat4> um4;

		int FindShader(const std::string& path);
		int FindLayout(const gl::AttribLayout& path);

		MaterialProps props;

		static void DeleteShaders();

		static std::vector<std::pair<std::string, gl::Shader*>> shaders;
		static std::vector<gl::AttribLayout> layouts;
	};

	struct GUIMaterial : public Material
	{
		GUIMaterial();
	};
}