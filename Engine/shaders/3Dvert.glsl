#version 330 core
layout (location = 0) in vec3 position;
out vec3 TexCoords;

uniform mat4 Projection;//has View matrix

uniform mat4 View;

void main()
{
    gl_Position =  Projection * View * vec4(position, 1.0);  

    TexCoords = position;
}  