#include "pch.h"
#include "VR.h"

namespace VR
{
	MeshLoader::MeshLoader()
	{
	}

	void MeshLoader::Load(const char* obj, Material* material)
	{
		std::ifstream file;
		file.open(obj);
		if (!file.is_open())
		{
			std::cout << "Couldn't open \"" << obj << "\"\n";
		}

		bool have_normals = material->GetTypeID() == MATERIAL_TYPE::LAMBERT;
		int vert_size = (material->attributesLayout.GetStride() - sizeof(math::vec4)) / sizeof(float);

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
					if (have_normals)
					{
						vn.emplace_back();
						sscanf_s(line.c_str(), "vn %f %f %f", &vn.back().x, &vn.back().y, &vn.back().z);
					}
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

				int f_ind = vertices.size() / vert_size;
				indices.resize(indices.size() + (slashes == 6 ? 3 : 6));
				vertices.resize(vertices.size() + slashes / 2 * vert_size);

				if (slashes == 6)
				{
					struct { int v, vt, vn; } vert[3];
					sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", 
						&vert[0].v, &vert[0].vt, &vert[0].vn, 
						&vert[1].v, &vert[1].vt, &vert[1].vn, 
						&vert[2].v, &vert[2].vt, &vert[2].vn);
					float* vertBuf = vertices.data() + vertices.size() - 3 * vert_size;

					for (int i = 0; i < 3; i++)
					{
						vertBuf[i * vert_size + 0] = v[vert[i].v - 1].x;
						vertBuf[i * vert_size + 1] = v[vert[i].v - 1].y;
						vertBuf[i * vert_size + 2] = v[vert[i].v - 1].z;

						if (material->GetTypeID() == MATERIAL_TYPE::LAMBERT)
						{
							vertBuf[i * 6 + 3] = vn[vert[i].vn - 1].x;
							vertBuf[i * 6 + 4] = vn[vert[i].vn - 1].y;
							vertBuf[i * 6 + 5] = vn[vert[i].vn - 1].z;
						}
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
					float* vertBuf = vertices.data() + vertices.size() - 4 * vert_size;

					for (int i = 0; i < 4; i++)
					{
						vertBuf[i * vert_size + 0] = v[vert[i].v - 1].x;
						vertBuf[i * vert_size + 1] = v[vert[i].v - 1].y;
						vertBuf[i * vert_size + 2] = v[vert[i].v - 1].z;

						if (have_normals)
						{
							vertBuf[i * 6 + 3] = vn[vert[i].vn - 1].x;
							vertBuf[i * 6 + 4] = vn[vert[i].vn - 1].y;
							vertBuf[i * 6 + 5] = vn[vert[i].vn - 1].z;
						}
					}

					indices[indices.size() - 6] = f_ind;
					indices[indices.size() - 5] = f_ind + 1;
					indices[indices.size() - 4] = f_ind + 2;
					indices[indices.size() - 3] = f_ind;
					indices[indices.size() - 2] = f_ind + 2;
					indices[indices.size() - 1] = f_ind + 3;
				}
			}
		}

		mesh.geometry.indices = indices.data();
		mesh.geometry.indices_count = indices.size();
		mesh.geometry.vertices = (uint8_t*)vertices.data();
		mesh.geometry.vertices_size = vertices.size() * sizeof(float);

		mesh.material = material;
	}
}