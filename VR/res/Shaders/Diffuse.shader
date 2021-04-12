#shader vertex
#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec3 in_normal;

out vec4 color;

struct DiffuseLight
{
	vec3 position;
	vec3 color;
};

uniform mat4 mvp;
uniform vec3 ambientLightColor;
uniform DiffuseLight diffuseLight;

void main()
{
	color = vec4(in_color.rgb * ambientLightColor + diffuseLight.color * max(-dot(in_normal, normalize(in_position - diffuseLight.position)), 0.0), 1.0);
	//color = vec4(in_color.rgb, 1.0);
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
	out_color = vec4(color.r, color.g, color.b, color.a);
	//out_color = vec4(0.0, 1.0, 1.0, 0.0);
}