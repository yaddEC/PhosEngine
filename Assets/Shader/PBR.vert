#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out vec2 texCoord;
out vec3 FragPos;
out mat3 TBN;
out vec3 Normal;

uniform mat4 mvp;
uniform mat4 model;

void main()
{
    gl_Position =  mvp * vec4(aPos, 1.0);
    texCoord = aTexCoord;
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal =  vec3(model * vec4(aNormal, 0.0));

    vec3 T = normalize(vec3(model * vec4(aTangent,   0.0)));
    vec3 B = normalize(vec3(model * vec4(aBitangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(aNormal,    0.0)));
    TBN = mat3(T, B, N);
}