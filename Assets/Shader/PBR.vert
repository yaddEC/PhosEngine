#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 texCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 mvp;
uniform mat4 model;

void main()
{
    texCoord = aTexCoord;
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal =  vec3(model * vec4(aNormal, 1.0));
    gl_Position =  mvp * vec4(aPos, 1.0);
}