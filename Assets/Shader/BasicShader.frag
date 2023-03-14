#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 texCoord;

uniform sampler2D albedoTexture;

void main()
{
    // TEMP
    vec3 lightDir = vec3(0.3, -1.0, 0.1);

    lightDir = normalize(-lightDir);

    float diffuse = max(dot(lightDir, Normal), 0.4);

    vec4 result =  texture(albedoTexture, texCoord) * (diffuse);
    result.w = 1;

    FragColor = result;
} 