#version 440 core
layout (location = 0) in vec3 position;
uniform mat4 Projection, View, Model;
uniform vec3 whywontyouwork;
out vec3 outID;
void main()
{ 
    gl_Position =  Projection * View *Model *vec4(position, 1.0);  
	outID = whywontyouwork;
}  