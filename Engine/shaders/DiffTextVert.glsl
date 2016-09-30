#version 450 core
layout(location = 0) in vec3 Position;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 cols;
layout (location = 4) in vec2 texCoords;

out vec3 fragmentColor;
out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 Projection, View, Model;
uniform vec3 myColor;


void main()
{	
	
	gl_Position =  Projection * View * Model * vec4(Position,1.0f);
	FragPos = vec3( View * Model * vec4(vertexPosition_modelspace, 1.0f));
    Normal = normalize(normal*mat3(View*Model));
	fragmentColor = cols;
	TexCoords = texCoords;
}