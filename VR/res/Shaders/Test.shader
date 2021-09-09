#shader vertex
#version 330 core

layout(location = 0) in vec2 pos; 

out vec2 texCoords;

void main()
{
	gl_Position = vec4(pos, 0.0, 1.0);
}

#shader fragment
#version 330 core

in vec2 texCoords;
out vec4 color;

uniform sampler2D tex;

void main()
{
	color = vec4(1.0, 1.0, 0.0, 0.5);
	//color = texture(tex, texCoords);
}