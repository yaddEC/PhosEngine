#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

uniform vec4 position_scale;


out vec2 texCoord;

void main()
{
    vec3 pos = vec3(position_scale.x, position_scale.y, 0);
    vec3 scale = vec3(position_scale.z, position_scale.w, 1);

    gl_Position =  vec4(aPos * scale + pos, 1.0);

    texCoord = aTexCoord;
}  