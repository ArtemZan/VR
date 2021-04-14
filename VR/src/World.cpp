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
		/*
			struct Vert
			{
				math::vec3 p;
				math::vec4 c;
				math::vec3 n;
			};
			Vert vert[24];
			memcpy(vert, batch.vertices.data(), 960);
		*/
		/*struct Vert
		{
			math::vec2 p;
			math::vec4 c;
		};
		Vert vert[8];
		memcpy(vert, batch.vertices.data(), 192);*/

		batch.shader->Bind();
		batch.vb.Bind();
		batch.vb.Data(batch.vertices.size(), batch.vertices.data());
		batch.va.Bind();
		batch.va.AddBuffer(batch.attribLayout);
		GLCall(glDrawElements(GL_TRIANGLES, batch.indices.size(), GL_UNSIGNED_INT, batch.indices.data()));
	}

	glfwSwapBuffers(Context::Get()->window);

}

void VR::World::Update()
{
	OnUpdate(m_timer.Update());

	glfwPollEvents();

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
