#version 450 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 2) in vec3 norms;
layout(location = 3) in vec3 cols;
layout (location = 4) in vec2 texCoords;

out vec3 fragmentColor;
out vec3 Normal;
out vec3 FragPos;


uniform mat4 Projection;
uniform mat4 Model;

uniform mat4 View;

void main()
{	
	
	gl_Position =  Projection *View*Model* vec4(vertexPosition_modelspace,1.0f);

	FragPos = vec3( Model*vec4(vertexPosition_modelspace, 1.0f));
    Normal = norms;//mat3(inverse(View*Model)) * norms;
	fragmentColor = cols;

}
