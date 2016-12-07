#version 450 core
layout(location = 0) in vec3 VP;

uniform mat4 Projection;
uniform mat4 Model;
uniform mat4 View;



void main()
{	
	
	gl_Position =  Projection *View*Model* vec4(VP,1.0f);

}