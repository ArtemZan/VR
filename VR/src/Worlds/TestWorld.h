#pragma once
#include "VR.h"

using namespace VR;

class TestWorld : public World
{
	std::vector<unsigned int> indices;
	math::mat4 model;
	math::mat4 proj;
	math::mat4 view;
	math::mat4 rotX;
	math::mat4 rotY;
	math::mat4 mvp;

	Scene::Batch* batch;

	int wWidth;
	int wHeight;
public:

	TestWorld()
	{
		glfwGetWindowSize(Context::Get()->window, &wWidth, &wHeight);

		proj = math::perspective(6, float(wWidth) / wHeight, 0.1, 100.0f);

		glm::mat4 p = glm::perspective(glm::radians(270.0f), float(wWidth) / wHeight, 0.1f, 100.0f);

		//auto l = glm::lookAt(W);
		/*proj.x.x = p[0].x;
		proj.x.y = p[0].y;
		proj.x.z = p[0].z;
		proj.x.w = p[0].w;
		proj.x.x = p[1].x;
		proj.x.y = p[1].y;
		proj.x.z = p[1].z;
		proj.x.w = p[1].w;
		proj.x.x = p[2].x;
		proj.x.y = p[2].y;
		proj.x.z = p[2].z;
		proj.x.w = p[2].w;
		proj.x.x = p[3].x;
		proj.x.y = p[3].y;
		proj.x.z = p[3].z;
		proj.x.w = p[3].w;*/

		model = math::mat4(1.0f);

		rotX = math::mat4(1.0f);
		rotY = math::mat4(1.0f);

		float data[] =
		{
			 0.5f, -0.5f, 1 + -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, 1 + -0.5f, 1.0f, 0.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, 1 + -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 1 + -0.5f, 1.0f, 0.0f, 1.0f, 1.0f,

			 0.5f, -0.5f, 1 + 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, 1 + 0.5f, 1.0f, 0.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, 1 + 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 1 + 0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
		};


		indices.resize(36);
		indices[0] = 2;
		indices[1] = 1;
		indices[2] = 0;
		indices[3] = 3;
		indices[4] = 1;
		indices[5] = 2;

		indices[6] = 6;
		indices[7] = 4;
		indices[8] = 5;
		indices[9] = 5;
		indices[10] = 7;
		indices[11] = 6;

		indices[12] = 6;
		indices[13] = 3;
		indices[14] = 2;
		indices[15] = 3;
		indices[16] = 6;
		indices[17] = 7;

		indices[18] = 3;
		indices[19] = 5;
		indices[20] = 1;
		indices[21] = 5;
		indices[22] = 3;
		indices[23] = 7;

		indices[24] = 0;
		indices[25] = 1;
		indices[26] = 4;
		indices[27] = 5;
		indices[28] = 4;
		indices[29] = 1;

		indices[30] = 4;
		indices[31] = 2;
		indices[32] = 0;
		indices[33] = 6;
		indices[34] = 2;
		indices[35] = 4;

		SetClearColor({ 0.7, 0.9, 0.5, 0.0 });

		gl::AttribLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		scene.AddMaterial("Basic", "Color.shader", layout);
		batch = scene.Add((uint8_t*)data, sizeof(data), indices.data(), 36, "Basic");
	}

	~TestWorld()
	{
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

		model *= rotY * rotX;

		mvp = model * proj;
		batch->material.shader.SetUniform("mvp", mvp);

		Render();

		if (glfwWindowShouldClose(Context::Get()->window))
		{
			Detach();
		}
	}
};

