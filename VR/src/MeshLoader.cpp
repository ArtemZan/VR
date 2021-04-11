#include "pch.h"
#include "VR.h"

namespace VR
{
	void OBJLoader::Load(const char* filepath)
	{
		
	}

	MeshLoader::MeshLoader()
		:mesh(nullptr)
	{
	}

	void MeshLoader::Load(const char* obj, const char* mtl)
	{
		std::ifstream file;
		file.open(obj);
		if (!file.is_open())
		{
			std::cout << "Couldn't open \"" << obj << "\"\n";
		}

		//std::stringstream content;

		std::string line;

		std::vector<math::vec3> v;
		std::vector<math::vec3> vn;


		while (std::getline(file, line))
		{
			if (line[0] == 'v')
			{
				switch (line[1])
				{
				case ' ':
				{
					v.emplace_back();
					sscanf_s(line.c_str(), "v %f %f %f", &v.back().x, &v.back().y, &v.back().z);
					break;
				}
				case 'n':
				{
					vn.emplace_back();
					sscanf_s(line.c_str(), "vn %f %f %f", &vn.back().x, &vn.back().y, &vn.back().z);
					break;
				}
				}
			}
			else if (line[0] == 'f')
			{
				int slashes = 0;
				for (int i = 0; i < line.size(); i++)
				{
					if (line[i] == '/') slashes++;
				}

				int f_ind = vertices.size() / 10;
				indices.resize(indices.size() + (slashes == 6 ? 3 : 6));
				vertices.resize(vertices.size() + slashes / 2 * 10);

				if (slashes == 6)
				{
					struct { int v, vt, vn; } vert[3];
					sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &vert[0].v, &vert[0].vt, &vert[0].vn, &vert[1].v, &vert[1].vt, &vert[1].vn, &vert[2].v, &vert[2].vt, &vert[2].vn);
					float* vertBuf = vertices.data() + vertices.size() - 30;

					for (int i = 0; i < 3; i++)
					{
						vertBuf[i * 10 + 0] = v[vert[i].v - 1].x;
						vertBuf[i * 10 + 1] = v[vert[i].v - 1].y;
						vertBuf[i * 10 + 2] = v[vert[i].v - 1].z;

						vertBuf[i * 10 + 3] = 1.0;
						vertBuf[i * 10 + 4] = 1.0;
						vertBuf[i * 10 + 5] = 1.0;
						vertBuf[i * 10 + 6] = 1.0;

						vertBuf[i * 10 + 7] = vn[vert[i].vn - 1].x;
						vertBuf[i * 10 + 8] = vn[vert[i].vn - 1].y;
						vertBuf[i * 10 + 9] = vn[vert[i].vn - 1].z;
					}


					indices[indices.size() - 3] = f_ind;
					indices[indices.size() - 2] = f_ind + 1;
					indices[indices.size() - 1] = f_ind + 2;
				}
				else
				{
					struct { int v, vt, vn; } vert[4];
					sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", 
						&vert[0].v, &vert[0].vt, &vert[0].vn, 
						&vert[1].v, &vert[1].vt, &vert[1].vn, 
						&vert[2].v, &vert[2].vt, &vert[2].vn, 
						&vert[3].v, &vert[3].vt, &vert[3].vn);
					float* vertBuf = vertices.data() + vertices.size() - 40;

					for (int i = 0; i < 4; i++)
					{
						vertBuf[i * 10 + 0] = v[vert[i].v - 1].x;
						vertBuf[i * 10 + 1] = v[vert[i].v - 1].y;
						vertBuf[i * 10 + 2] = v[vert[i].v - 1].z;

						vertBuf[i * 10 + 3] = 1.0;
						vertBuf[i * 10 + 4] = 1.0;
						vertBuf[i * 10 + 5] = 1.0;
						vertBuf[i * 10 + 6] = 1.0;

						vertBuf[i * 10 + 7] = vn[vert[i].vn - 1].x;
						vertBuf[i * 10 + 8] = vn[vert[i].vn - 1].y;
						vertBuf[i * 10 + 9] = vn[vert[i].vn - 1].z;
					}

					indices[indices.size() - 6] = f_ind;
					indices[indices.size() - 5] = f_ind + 1;
					indices[indices.size() - 4] = f_ind + 2;
					indices[indices.size() - 3] = f_ind + 1;
					indices[indices.size() - 2] = f_ind + 2;
					indices[indices.size() - 1] = f_ind + 3;
				}
			}
		}

		mesh.geometry.indices = indices.data();
		mesh.geometry.indices_count = indices.size();
		mesh.geometry.vertices = (uint8_t*)vertices.data();
		mesh.geometry.vertices_size = vertices.size() * sizeof(float);

		mesh.material = Material::LambertMaterial;
	}
}