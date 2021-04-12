#include "pch.h"
#include "VR.h"

VR::World::World()
{
}

void VR::World::Run()
{
	GLCall(glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a));

	OnAttach();

	m_attached = true;

	while (m_attached)
	{
		Update();
	}
}

void VR::World::Render()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	for (const Scene::Batch& batch : scene.batches)
	{
		if (batch.vertices.size() == 960)
		{
			struct Vert
			{
				math::vec3 p;
				math::vec4 c;
				math::vec3 n;
			};
			Vert vert[24];
			memcpy(vert, batch.vertices.data(), 960);
			std::cout << "";
		}
		batch.material->shader.Bind();
		batch.vb.Bind();
		batch.va.Bind();
		batch.va.AddBuffer(batch.material->attributesLayout);
		batch.vb.Data(batch.vertices.size(), batch.vertices.data());
		GLCall(glDrawElements(GL_TRIANGLES, batch.indices.size(), GL_UNSIGNED_INT, batch.indices.data()));
	}

	glfwSwapBuffers(Context::Get()->window);

}

void VR::World::Update()
{
	OnUpdate(m_timer.Update());

	glfwPollEvents();

	std::this_thread::sleep_for(std::chrono::milliseconds(0));
}
