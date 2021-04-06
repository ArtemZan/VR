#pragma once

namespace VR
{
	struct Material
	{
		gl::Shader shader;
		gl::AttribLayout attributesLayout;
	};

	struct Scene
	{
		struct Objects
		{
			Material material; 
			std::vector<uint8_t> vertices; 
			std::vector<uint32_t> indices;
			gl::VertexArray va;
			gl::VertexBuffer* vb;
		};

		std::vector<Objects> objects;
	};
}
