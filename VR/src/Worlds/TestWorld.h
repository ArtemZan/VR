#pragma once
#include "VR.h"

using namespace VR;

class TestRenderer : public VR::Renderer
{
	std::vector<unsigned int> indices;
	gl::AttribLayout layout;
	gl::VertexArray va;
	gl::VertexBuffer* vb;
	gl::Shader shader;
	math::mat4 model;
	math::mat4 proj;
	math::mat4 view;
	math::mat4 rotX;
	math::mat4 rotY;
	math::mat4 mvp;

	int wWidth;
	int wHeight;
public:

	TestRenderer()
		:shader("Color.shader")
	{
		shader.Bind();

		GetWindowSize(&wWidth, &wHeight);

		proj = math::perspective(2, float(wWidth) / wHeight, 0.1, 100.0f);

		//view = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.0f));

		math::vec4(1, 2, 3, 4) * 2.0f + math::vec4(5, 6, 7, 8);

		model = math::mat4(1.0f);

		rotX = math::mat4(1.0f);
		rotY = math::mat4(1.0f);

		float data[] =
		{
			 0.5f, -0.5f, 5 + -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, 5 + -0.5f, 1.0f, 0.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, 5 + -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 5 + -0.5f, 1.0f, 0.0f, 1.0f, 1.0f,

			 0.5f, -0.5f, 5 + 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, 5 + 0.5f, 1.0f, 0.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, 5 + 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 5 + 0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
		};


		indices.resize(30);
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 1;
		indices[4] = 2;
		indices[5] = 3;

		indices[6] = 4;
		indices[7] = 5;
		indices[8] = 6;
		indices[9] = 5;
		indices[10] = 6;
		indices[11] = 7;

		indices[12] = 2;
		indices[13] = 3;
		indices[14] = 6;
		indices[15] = 3;
		indices[16] = 6;
		indices[17] = 7;

		indices[18] = 1;
		indices[19] = 5;
		indices[20] = 3;
		indices[21] = 5;
		indices[22] = 3;
		indices[23] = 7;

		indices[24] = 0;
		indices[25] = 1;
		indices[26] = 4;
		indices[27] = 1;
		indices[28] = 4;
		indices[29] = 5;


		vb = new gl::VertexBuffer(data, sizeof(data));
		layout.Push<float>(3);
		layout.Push<float>(4);
		va.Bind();
		va.AddBuffer(layout);

		//SetIndicesPtr(&indices);

		SetClearColor({ 0.7, 0.9, 0.5, 0.0 });
	}

	~TestRenderer()
	{
		delete vb;
	}

	void OnUpdate(float dTime) override
	{
		rotX.y.y = cos(dTime / 1000.0f);
		rotX.y.z = -sin(dTime / 1000.0f);
		rotX.z.y = sin(dTime / 1000.0f);
		rotX.z.z = cos(dTime / 1000.0f);

		rotY.x.x = cos(dTime / 1000.0f);
		rotY.x.z = sin(dTime / 1000.0f);
		rotY.z.x = -sin(dTime / 1000.0f);
		rotY.z.z = cos(dTime / 1000.0f);

		model *= rotX * rotY;

		mvp = model * proj;
		shader.SetUniform("mvp", mvp);

		Render({}, {});
	}
};

class TestWorld : public World
{
public:
	TestWorld()
		:World(new TestRenderer())
	{

	}
};

