#include "..\VR.h"

using namespace VR;

class MyRenderer : public VR::Renderer
{
	std::vector<unsigned int> indices;
	gl::AttribLayout layout;
	gl::VertexArray va;
	gl::VertexBuffer* vb;
	gl::Shader shader;
	glm::mat4 model;
	glm::mat4 proj;
	glm::mat4 view;
	glm::mat4 rotX;
	glm::mat4 rotY;
	glm::mat4 mvp;

	int wWidth;
	int wHeight;
public:

	MyRenderer(int window_width, int window_height, const char* title)
		:Renderer(window_width, window_height, title), shader("Color.shader")
	{
		shader.Bind();

		GetWindowSize(&wWidth, &wHeight);

		shader.SetUniform("ratio", float(wHeight) / wWidth);

		proj = glm::mat4(1.0f);//glm::ortho(0.0f, float(wWidth), 0.0f, float(wHeight), 0.1f, 100.0f);
		proj[3].z = 0.5f;

		view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

		model = glm::mat4(1.0f);

		model[0].x = 0.5;
		model[1].y = 0.5;
		model[2].z = 0.5;
		
		rotX = glm::mat4(1.0f);
		rotY = glm::mat4(1.0f);

		float data[] =
		{
			 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f,

			 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
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

		SetIndicesPtr(&indices);

		SetClearColor({ 0.7, 0.9, 0.5, 0.0 });
	}

	~MyRenderer()
	{
		delete vb;
	}

	void OnUpdate(float dTime) override
	{
		rotX[1].y = cos(dTime / 1000.0f);
		rotX[1].z = -sin(dTime / 1000.0f);
		rotX[2].y = sin(dTime / 1000.0f);
		rotX[2].z = cos(dTime / 1000.0f);

		rotY[0].x = cos(dTime / 1000.0f);
		rotY[0].z = sin(dTime / 1000.0f);
		rotY[2].x = -sin(dTime / 1000.0f);
		rotY[2].z = cos(dTime / 1000.0f);

		model *= rotX * rotY;//glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		mvp = model * proj;
		shader.SetUniform("mvp", mvp);
	}
};

int main()
{
	VR::Renderer* renderer = new MyRenderer(960, 540, "Hello world");
	renderer->Run();
}