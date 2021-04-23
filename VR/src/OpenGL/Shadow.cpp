#include "pch.h"
#include "VR.h"

namespace VR
{
	namespace gl
	{
		ShadowGenerator::ShadowGenerator()
			:shader("Depth.shader")
		{
			GLCall(glGenFramebuffers(1, &m_bufferID));

			GLCall(glGenTextures(1, &m_depthMap));

			GLCall(glBindTexture(GL_TEXTURE_2D, m_depthMap));

			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));

			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_bufferID));
			GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMap, 0));
			GLCall(glDrawBuffer(GL_NONE));
			GLCall(glReadBuffer(GL_NONE));
			UnbindBuffer();
		}

		void ShadowGenerator::BindBuffer(const math::mat4& light_view)
		{
			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_bufferID));
			shader.Bind();
			shader.SetUniform("light", light_view);
		}
	}
}