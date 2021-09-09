#shader vertex
#version 330 core

layout(location = 0) in vec3 in_pos;

uniform mat4 light;

void main()
{
	gl_Position = light * vec4(in_pos, 1.0);
}

#shader fragment
#version 330 core

out vec4 color;

void main()
{
	//color = vec4(1.0, 0.0, 1.0, 0.0);
}