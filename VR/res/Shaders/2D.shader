#shader vertex
#version 330 core

layout(location = 0) in vec2 in_pos;
layout(location = 1) in vec4 in_color;

out vec4 color;
uniform mat3x2 transform;

void main()
{
	color = in_color;
	gl_Position = vec4(vec3(transform * vec3(in_pos, 1.0), 0.0), 1.0);
}

#shader fragment
#version 330 core

in vec4 color;

out vec4 out_color;

void main()
{
	out_color = color;
}