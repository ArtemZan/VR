#pragma once

class Pendulum : public World
{
	void* p;
	gl::ShadowGenerator shadowGen;
	gl::Shader shader;
	Object2D rect;
	_2DMaterial mat;

public:
	Pendulum()
		:shader("Test.shader")
	{
		m_scene.AddBox({ 1.5, 1.0 }, &mat, &rect.mesh);
	}

	void OnAttach() override
	{
		std::cout << "Shadow\n";
		
		SetClearColor({ 1.0, 0.0, 1.0, 1.0 });
	}

	void OnUpdate(float dTime) override
	{				
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		shadowGen.BindBuffer({1.0});
		shader.Bind();
		shader.SetUniform("tex", 0);
		//shadowGen.UnbindBuffer();//BindShadowMap();
		/*float v[]
		{
			-1.0, -1.0,
			1.0, -1.0,
			-1.0, 1.0,
			1.0, 1.0
		};
		gl::VertexBuffer vb(v, sizeof(v));
		gl::VertexArray va;
		gl::AttribLayout layout;
		layout.Push<float>(2);
		vb.Bind();
		va.Bind();
		va.AddBuffer(layout);
		uint32_t ind[]
		{
			0, 1, 2,
			1, 2, 3
		};
		GLCall(glClearColor(1.0, 0.0, 1.0, 1.0));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, ind));
		glfwSwapBuffers(Context::Get()->window);*/
		Render();
		//shadowGen.UnbindBuffer();
		//shadowGen.BindShadowMap();
		Render();
		if (glfwWindowShouldClose(Context::Get()->window))
			Detach();
	}
};