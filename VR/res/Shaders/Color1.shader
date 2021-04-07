#shader vertex
#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;

out vec4 color;

uniform mat4 mvp;
uniform float ratio;

void main()
{
	color = in_color;
	gl_Position = mvp * vec4(in_position, 1.0);
	//gl_Position = vec4(position.x * ratio, position.y, position.z, position.w);
	//gl_Position = vec4(position.x * 100.0f, position.y * 100.0f, 10.0f, 1.0f);

	//gl_Position = vec4(position.x * ratio, position.y, -position.z, position.w);
}

#shader fragment
#version 330 core

out vec4 out_color;

in vec4 color;

void main()
{
	out_color = vec4(color.r, color.g, 1.0, color.a);
	//out_color = vec4(0.0, 1.0, 1.0, 0.0);
}