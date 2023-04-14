#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;


out vec3 FragPos;
// out vec3 Normal;
out vec2 texCoord;
out mat3 TBN;
// out vec3 viewPosition;
out vec3 TangentViewPos;
// out vec3 TangentFragPos;

uniform vec3 viewPos;
uniform mat4 mvp;
uniform mat4 model;
// uniform vec3 viewPos;

void main()
{
    gl_Position = mvp * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
	// Normal = vec3(model * vec4(aNormal, 0.0));
    texCoord = aTexCoord;
    
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    // vec3 B = normalize(normalMatrix * aBitangent);
    TBN = transpose(mat3(T, B, N));  
    TangentViewPos = TBN * viewPos;
    // viewPosition = viewPos;
    // TangentFragPos = TBN * FragPos;
}