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

		AddHandler(this);
		
		SetClearColor({ 1.0, 0.0, 1.0, 1.0 });
		Render();
		shadowGen.BindBuffer({ 1.0 });
		shader.Bind();
		shader.SetUniform("tex", 0);
	}

	void OnUpdate(float dTime) override
	{				
		Render();
		MustUpdate();

		//shadowGen.UnbindBuffer();
		//shadowGen.BindShadowMap();
	}
};