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

	for (const Scene::Batch& objects : scene.batches)
	{
		objects.material.shader.Bind();
		objects.va.Bind();
		objects.vb->Bind();
		objects.vb->Data(objects.vertices.size(), objects.vertices.data());
		GLCall(glDrawElements(GL_TRIANGLES, objects.indices.size(), GL_UNSIGNED_INT, objects.indices.data()));
	}

	glfwSwapBuffers(Context::Get()->window);

}

void VR::World::Update()
{
	OnUpdate(m_timer.Update());

	glfwPollEvents();

	std::this_thread::sleep_for(std::chrono::milliseconds(0));
}
