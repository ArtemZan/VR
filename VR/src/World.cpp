#include "pch.h"
#include "VR.h"

VR::World::World()
{
}

void VR::World::Run()
{
	m_attached = true;

	while (m_attached)
	{
		Update();
	}
}

void VR::World::Render()
{
	GLCall(glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	for (const Scene::Batch& batch : scene.batches)
	{
		batch.material->shader.Bind();
		batch.vb.Bind();
		batch.va.Bind();
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
