#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 lightMat;

void main()
{
	gl_Position = model * lightMat * vec4(aPos, 1.0);
};