#version 450 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 2) in vec3 norms;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 Projection,View,Model;


void main(){	

	gl_Position =  Projection*View *Model* vec4(vertexPosition_modelspace,1.0f);
	FragPos = vec3(View*Model*vec4(vertexPosition_modelspace, 1.0f));
    Normal = vec3(View*Model*vec4(norms,0.0));
	
}