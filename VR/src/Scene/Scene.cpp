#include "pch.h"
#include "VR.h"

namespace VR
{

	Scene::Scene()
	{

	}

	void Scene::Add(Mesh& mesh)
	{
		Add(mesh.GetData());
		mesh.GetData()->scene = this;
	}

	void Scene::Add(const std::shared_ptr<MeshContainer>& mesh)
	{
		for (Batch& batch : batches)
		{
			if (batch.meshes.size() == 0 || batch.meshes[0]->material.GetShaderId() == mesh->material.GetShaderId())
			{
				batch.Add(mesh);
				return;
			}
		}

		batches.emplace_back();

		batches.back().Add(mesh);
	}

	void Scene::Delete(Mesh& mesh)
	{
		for (Batch& batch : batches)
		{
			if (batch.meshes.size())
			{
				batch.Delete(mesh);
				return;
			}
		}
	}


	void Scene::Render()
	{

		//glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);

		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		for (Batch& batch : batches)
		{
			Material& mat = batch.meshes.front()->material;

			for (int m = 0; m < batch.meshes.size(); m++)
			{
				if (batch.vertices.data() > batch.meshes[m]->geometry.vertices 
					&& batch.vertices.data() + batch.vertices.size() < batch.meshes[m]->geometry.vertices + batch.meshes[m]->geometry.vertices_size)
				{
					batch.EraseMesh(m);
					Add(batch.meshes[m]);
				}
			}

			mat.BindShader();
			mat.SetShaderUniforms();

			batch.vb.Bind();
			batch.vb.Data(batch.vertices.size(), batch.vertices.data());
			/*for (int i = 0; i < batch.vertices.size(); i+=4)
			{
				if (i % batch.meshes[0]->material.GetVertexSize() == 0)
				{
					std::cout << std::endl;
				}
				std::cout << std::setw(8) << *(float*)(&batch.vertices[i]) << " ";
			}*/
			batch.va.Bind();
			batch.va.AddBuffer(mat.GetLayout());
			GLCall(glDrawElements(GL_TRIANGLES, batch.indices.size(), GL_UNSIGNED_INT, batch.indices.data()));
		}

		glfwSwapBuffers(Context::Get()->m_window.m_window);

	}


	



	
}