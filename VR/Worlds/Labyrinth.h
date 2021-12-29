#pragma once

class Labyrinth : public World
{
	struct Node
	{
		math::vec2 pos;
		std::vector<Node*> neighbours;
	};
	std::vector<Node> graph;

	struct Box : public Object2D
	{
		math::vec2 size;
	};

	_2DMaterial material;
	GUIMaterial guiMat;

	math::mat3 view;

	std::vector<Box> boxes;
	Box box;
	Box center;
	Box solve;
	std::vector<Box> path;

	bool move_box = false;

	bool topResize = false;
	bool bottomResize = false;
	bool leftResize = false;
	bool rightResize = false;

	bool leftMouseButtonDown = false;

public:
	Labyrinth()
		:material({0.6, 0.5, 0.2, 0.5}), view(1.0)
	{

	}

	void OnAttach() override
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);

		AddHandler(this);

		IO* io = IO::Get();
		math::vec2i wSize = io->WindowSize();

		guiMat.color = {0.6, 0.5, 0.2, 0.5};
		m_scene.AddBox({ 0.3f, 0.3 }, &guiMat, &box.mesh);
		box.size = {0.3f, 0.3f};
		box.Scale({float(wSize.height) / wSize.width, 1.0});
		box.Move({1.f - 0.3f * float(wSize.height) / wSize.width / 2.0f, 0.85f});

		guiMat.color = { 0.0, 1.0, 0.0, 0.5 };
		m_scene.AddBox({ 0.15f, 0.1f }, &guiMat, &solve.mesh);
		solve.MoveTo({ 0.0, 0.95 });

		OnWindowResize(wSize.width, wSize.height);

		Render();
	}

	void OnUpdate(float dTime) override
	{
		//Render();
	}

	void OnMouseMove(math::vec2 pos) override
	{
		float x = pos.x;
		float y = pos.y;

		IO* io = IO::Get();
		math::vec2i wSize = io->WindowSize();
		math::vec2i prevPos = io->MousePos(); //stupid

		x /= wSize.width / 2;
		x -= 1;
		y /= -wSize.height / 2;
		y += 1;

		float wh = float(wSize.width) / wSize.height;

		if (move_box)
		{
			boxes.back().MoveTo({ float(x) * wh, float(y) });
			//center.MoveTo({ float(x), float(y) });
			Render();
		}

		if (leftMouseButtonDown)
		{
			float* vert = (float*)boxes.back().mesh.geometry.vertices;
			float dMousePos = x - x;

			if (leftResize)
			{
				vert[6] += dMousePos * wh;
				vert[18] += dMousePos * wh;
				boxes.back().pos.x += dMousePos * wh / 2.0f;
				boxes.back().size.x -= dMousePos * wh;
			}

			if (rightResize)
			{
				vert[0 ] += dMousePos * wh;
				vert[12] += dMousePos * wh;
				boxes.back().pos.x += dMousePos * wh / 2.0f;
				boxes.back().size.x += dMousePos * wh;
			}

			dMousePos = y - y;

			if (topResize)
			{
				vert[12 + 1] += dMousePos;
				vert[18 + 1] += dMousePos;
				boxes.back().pos.y += dMousePos / 2.0f;
				boxes.back().size.y += dMousePos;
			}

			if (bottomResize)
			{
				vert[0 + 1] += dMousePos;
				vert[6 + 1] += dMousePos;
				boxes.back().pos.y += dMousePos / 2.0f;
				boxes.back().size.y -= dMousePos;
			}

			if (leftResize || rightResize || topResize || bottomResize)
			{
				//center.MoveTo(boxes.back().pos * math::Tvec2( 1.0f / wh, 1.0f));
				Render();
			}
		}
		else
		{
			if (x > 1.0 - 0.3 * wSize.height / float(wSize.width) && y > 0.7)
			{
				glfwSetCursor(Context::Get()->window, glfwCreateStandardCursor(GLFW_HAND_CURSOR));
			}
			else
			{
				if (boxes.size())
				{
					leftResize = false;
					rightResize = false;
					topResize = false;
					bottomResize = false;

					if (abs((boxes.back().pos.x - boxes.back().size.x / 2.0) / wh - x) < 0.05)
					{
						leftResize = true;
					}
					else if (abs((boxes.back().pos.x + boxes.back().size.x / 2.0) / wh - x) < 0.05)
					{
						rightResize = true;
					}
					else if (abs(boxes.back().pos.y - boxes.back().size.y / 2.0 - y) < 0.05)
					{
						bottomResize = true;
					}
					else if (abs(boxes.back().pos.y + boxes.back().size.y / 2.0 - y) < 0.05)
					{
						topResize = true;
					}

					if (leftResize || rightResize)
					{
						glfwSetCursor(Context::Get()->window, glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR));
						move_box = false;
					}
					else if (topResize || bottomResize)
					{
						glfwSetCursor(Context::Get()->window, glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR));
						move_box = false;
					}
					else
					{
						glfwSetCursor(Context::Get()->window, glfwCreateStandardCursor(GLFW_ARROW_CURSOR));
					}
				}
				else
				{
					glfwSetCursor(Context::Get()->window, glfwCreateStandardCursor(GLFW_ARROW_CURSOR));
				}
			}
		}
	}

	void OnMouseDown(int button, int mods) override
	{
		double mX, mY;
		glfwGetCursorPos(Context::Get()->window, &mX, &mY);
		int width, height;
		glfwGetWindowSize(Context::Get()->window, &width, &height);
		mX /= width / 2;
		mX -= 1;
		mY /= height / 2;
		mY = 1 - mY;

		
		if (button == GLFW_MOUSE_BUTTON_LEFT && !move_box)
		{
			leftMouseButtonDown = true;

			if (-1.0 < mX && -0.9 > mX && 1.0 > mY && 0.95 < mY)
			{
				Detach();
			}

			if (mX > -0.15 / 2.0f && mX < 0.15 / 2.0f && mY > 0.9)
			{
				Solve();
			}

			if (mX > 1 - 0.3 / float(width) * height && mY > 0.7)
			{
				move_box = true;
				boxes.emplace_back();
				m_scene.AddBox({ 0.3, 0.3 }, &material, &boxes.back().mesh);
				boxes.back().size = { 0.3, 0.3 };

				/*if (boxes.size() == 1)
				{
					guiMat.color = {0.0, 1.0, 0.0, 0.0};
					scene.AddBox({ 0.1, 0.1 }, &guiMat, &center.mesh);
					guiMat.color = { 0.6, 0.5, 0.2, 0.0 };
				}*/
			}
		}
	}

	void OnMouseUp(int button, int mods) override
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			move_box = false;
			leftMouseButtonDown = false;
		}
	}

	void Solve()
	{
		GenGraph();
		DrawGraph();
	}

	void GenGraph()
	{
		graph.resize(4 * boxes.size());
		for (int i = 0; i < boxes.size(); i++)
		{
			graph[i * 4 + 0].pos = boxes[i].pos - boxes[i].size / 2.0f;
			graph[i * 4 + 1].pos = {boxes[i].pos.x + boxes[i].size.x / 2.0f, boxes[i].pos.y - boxes[i].size.y / 2.0f};
			graph[i * 4 + 2].pos = {boxes[i].pos.x - boxes[i].size.x / 2.0f, boxes[i].pos.y + boxes[i].size.y / 2.0f };
			graph[i * 4 + 3].pos = boxes[i].pos + boxes[i].size / 2.0f;
		}
		for (int from = 0; from < boxes.size(); from++)
		{
			graph[from * 4 + 0].neighbours.emplace_back(&graph[from * 4 + 1]);
			graph[from * 4 + 0].neighbours.emplace_back(&graph[from * 4 + 2]);
			graph[from * 4 + 1].neighbours.emplace_back(&graph[from * 4 + 0]);
			graph[from * 4 + 1].neighbours.emplace_back(&graph[from * 4 + 3]);
			graph[from * 4 + 2].neighbours.emplace_back(&graph[from * 4 + 0]);
			graph[from * 4 + 2].neighbours.emplace_back(&graph[from * 4 + 3]);
			graph[from * 4 + 3].neighbours.emplace_back(&graph[from * 4 + 1]);
			graph[from * 4 + 3].neighbours.emplace_back(&graph[from * 4 + 2]);
			for (int to = from + 1; to < boxes.size(); to++)
			{
				/*math::Tvec2 v0[4]{
					boxes[from].pos - boxes[from].size / 2.0f,
					{boxes[from].pos.x + boxes[from].size.x / 2.0f, boxes[from].pos.y - boxes[from].size.y / 2.0f},
					{boxes[from].pos.x - boxes[from].size.x / 2.0f, boxes[from].pos.y + boxes[from].size.y / 2.0f},
					boxes[from].pos + boxes[from].size / 2.0f
				};

				math::Tvec2 v1[4]{
					boxes[to].pos - boxes[to].size / 2.0f,
					{boxes[to].pos.x + boxes[to].size.x / 2.0f, boxes[to].pos.y - boxes[to].size.y / 2.0f},
					{boxes[to].pos.x - boxes[to].size.x / 2.0f, boxes[to].pos.y + boxes[to].size.y / 2.0f},
					boxes[to].pos + boxes[to].size / 2.0f
				};*/


				for (int v0 = 0; v0 < 4; v0++)
				{
					for (int v1 = 0; v1 < 4; v1++)
					{
						const math::vec2& dist = graph[from * 4 + v0].pos - graph[to * 4 + v1].pos;

						float a = dist.y / dist.x;
						float b = graph[from * 4 + v0].pos.y - graph[from * 4 + v0].pos.x * a;

						bool cross = false;
						for (int obst = 0; obst < boxes.size() && !cross; obst++)
						{
							/*math::Tvec2 ov[4]{
								boxes[obst].pos - boxes[obst].size / 2.0f,
								{boxes[obst].pos.x + boxes[obst].size.x / 2.0f, boxes[obst].pos.y - boxes[obst].size.y / 2.0f},
								{boxes[obst].pos.x - boxes[obst].size.x / 2.0f, boxes[obst].pos.y + boxes[obst].size.y / 2.0f},
								boxes[obst].pos + boxes[obst].size / 2.0f
							};*/

							bool below = false;
							for (int ov = 0; ov < 4; ov++)
							{
								//float min = math::dot(graph[from * 4 + v0].pos - math::Tvec2(0.0, b), graph[obst * 4 + ov].pos);
								//float max = math::dot(graph[to * 4 + v1].pos - math::Tvec2(0.0, b), graph[obst * 4 + ov].pos)
								//if(math::normalize(graph[obst * 4 + ov].pos).)

								if ((from == obst && ov == v0) || (to == obst && ov == v1))
									continue;
								if (a * graph[obst * 4 + ov].pos.x + b > graph[obst * 4 + ov].pos.y)
								{
									if (ov && !below)
									{
										cross = true;
										break;
									}
									below = true;
								}
								else if (below)
								{
									cross = true;
									break;
								}
							}
						}

						if (!cross)
						{
							graph[from * 4 + v0].neighbours.emplace_back(graph.data() + to * 4 + v1);
							graph[to * 4 + v1].neighbours.emplace_back(graph.data() + from * 4 + v0);
						}
					}
				}
			}
		}
	}

	void DrawGraph()
	{
		material.color = {1.0, 0.6, 0.3, 0.5};
		int paths_count = 0;
		for (int i = 0; i < graph.size(); i++)
		{
			paths_count += graph[i].neighbours.size();
		}
		paths_count /= 2;
		path.reserve(paths_count);
		for (int i = 0; i < graph.size(); i++)
		{
			for (int n = 0; n < graph[i].neighbours.size(); n++)
			{
				if (graph[i].neighbours[n] > graph.data() + i)
				{
					path.emplace_back();

					m_scene.AddBox({ 0.0, 0.0 }, &material, &path.back().mesh);

					float* vert = (float*)path.back().mesh.geometry.vertices;
					int fpv = path.back().mesh.material->attributesLayout.GetStride() / sizeof(float);
					(math::vec2&)vert[fpv * 0] = graph[i].pos;
					math::vec2 d = graph[i].neighbours[n]->pos - graph[i].pos;
					(math::vec2&)vert[fpv * 1] = graph[i].pos + math::vec2(-d.y, d.x) * 0.01f;
					(math::vec2&)vert[fpv * 2] = graph[i].neighbours[n]->pos;
					(math::vec2&)vert[fpv * 3] = graph[i].neighbours[n]->pos + math::vec2(-d.y, d.x) * 0.01f;
				}
			}
		}
		Render();
	}


	void OnWindowResize(int width, int height) override
	{
		view.x.x = 1.0f / width * height;
		material.shader->Bind();
		material.shader->SetUniform("view", view);

		glViewport(0, 0, width, height);

		box.Scale({ float(height) / width / box.scale.x, 1.0 });
		box.MoveTo({ 1.f - 0.3f * float(height) / width / 2.0f, 0.85f });

		Render();
	}
};