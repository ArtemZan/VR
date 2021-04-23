#pragma once

class Pendulum : public World
{
	void* p;
	gl::ShadowGenerator shadowGen;
	gl::Shader shader;

public:
	Pendulum()
		:shader("Test.shader")
	{
	}

	void OnUpdate(float dTime) override
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		//shadowGen.BindBuffer(1.0);
		//glDrawBuffer(GL_FRONT_AND_BACK);
		shadowGen.BindShadowMap();
		shader.Bind();
		shader.SetUniform("tex", 0);
		glfwSwapBuffers(Context::Get()->window);
		if (glfwWindowShouldClose(Context::Get()->window))
			Detach();
	}
};