#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform int cameraCount;
uniform sampler2D screenTexture[4];

const float offset = 1.0 / 300.0; 

void main()
{
    FragColor = vec4(0.5, 0.2, 0.3, 1.0);
    
    
} 