#include "pch.h"
#include "VR.h"

namespace VR
{

	Scene::Scene()
	{

	}

	void Scene::Add(Mesh& mesh)
	{
		for (auto& w_batch : m_batches)
		{
			std::shared_ptr batch = w_batch.lock();

			if (batch->m_meshes.size() == 0 || batch->m_meshes[0]->GetMaterial() == mesh->GetMaterial())
			{
				Batch::Add(mesh, batch);
				return;
			}
		}

		const std::shared_ptr<Batch> newBatch = std::make_shared<Batch>();

		m_batches.emplace_back(newBatch);

		Batch::Add(mesh, newBatch);

		Add(mesh, newBatch);
	}

	void Scene::Add(Mesh& mesh, const std::shared_ptr<Batch>& batch)
	{

	}

	void Scene::Delete(Mesh& mesh)
	{
		for (auto& w_batch : m_batches)
		{
			std::shared_ptr batch = w_batch.lock();
			if (batch->m_meshes.size())
			{
				batch->Delete(mesh);
			}
		}
	}


	void Scene::Render()
	{

		//glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);

		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		for (auto& w_batch : m_batches)
		{
			std::shared_ptr<Batch> batch = w_batch.lock();

			if (batch->m_vertices.size() == 0) {
				continue;
			}

			Material& mat = batch->m_meshes.front()->GetMaterial();

			/*for (int m = 0; m < batch.m_meshes.size(); m++)
			{
				if (batch.m_vertices.data() > batch.m_meshes[m]->geometry.vertices 
					&& batch.m_vertices.data() + batch.m_vertices.size() < batch.meshes[m]->geometry.vertices + batch.meshes[m]->geometry.vertices_size)
				{
					batch.EraseMesh(m);
					Add(batch.m_meshes[m]);
				}
			}*/

			mat.BindShader();
			mat.SetShaderUniforms();

			batch->m_vb.Bind();
			batch->m_vb.Data(batch->m_vertices.size(), batch->m_vertices.data());
			/*for (int i = 0; i < batch->m_vertices.size(); i+=4)
			{
				if (i % batch->m_meshes[0]->GetGeometry().GetVertexSize() == 0)
				{
					std::cout << '\n';
				}
				std::cout << std::setw(8) << *(float*)(&batch->m_vertices[i]) << " ";
			}*/
			batch->m_va.Bind();
			batch->m_va.AddBuffer(batch->m_meshes.front()->GetGeometry().GetLayout());
			GLCall(glDrawElements(GL_TRIANGLES, batch->m_indices.size(), GL_UNSIGNED_INT, batch->m_indices.data()));
		}

		glfwSwapBuffers(Context::Get()->m_window.m_window);

	}


	



	
}