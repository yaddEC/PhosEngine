#version 330 core

uniform sampler2D Texture;

in vec2 texCoord;

out vec4 FragColor;

void main()
{    
    vec4 color = texture2D(Texture, texCoord);
    if(color.w < 0.1)
        discard;
    FragColor = color;
}