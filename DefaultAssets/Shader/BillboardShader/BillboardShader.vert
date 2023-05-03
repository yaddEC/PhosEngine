#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

out vec2 texCoord;

void main()
{
    mat4 modelView = modelViewMatrix;
    modelView[0][0] = 1.0; 
    modelView[0][1] = 0.0; 
    modelView[0][2] = 0.0;

    modelView[1][0] = 0.0; 
    modelView[1][1] = 1.0; 
    modelView[1][2] = 0.0; 

    modelView[2][0] = 0.0; 
    modelView[2][1] = 0.0; 
    modelView[2][2] = 1.0; 

    vec4 P = modelView * vec4(aPos,1);
    gl_Position = projectionMatrix * P; 

    texCoord = aTexCoord;
}  