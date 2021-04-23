#pragma once

namespace VR
{
	namespace gl
	{
		class ShadowGenerator
		{
			GLuint m_bufferID;
			GLuint m_depthMap;

			Shader shader;

		public:
			ShadowGenerator();

			void BindBuffer(const math::mat4& light_view);
			static inline void UnbindBuffer() { GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0)); }

			inline void BindShadowMap(int slot = 0) const { GLCall(glBindTextureUnit(slot, m_depthMap)); }
		};
	}
}