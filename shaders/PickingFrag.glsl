#version 420 core   


			   
in vec3 outID; 
out vec3 IDColor;

void main()
{
	//float id = ObjectID/255.0;
	IDColor= outID;
} 