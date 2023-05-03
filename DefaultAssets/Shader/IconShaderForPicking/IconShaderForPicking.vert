#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

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
}  