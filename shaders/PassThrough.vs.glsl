//Pass through vertex shader for Tesselation control shader. 
#version 450 core

layout (location = 0) in vec3 Position;
layout (location = 2) in vec3 Normal;
layout (location = 4) in vec2 TexCoords;
layout (location = 5) in vec3 Tangent;
layout (location = 6) in vec3 Bitangent;  

uniform mat4 Projection, View, Model;
uniform vec3 lightPos, viewPos;

out vec3 WorldPos_CS_in;
out vec2 TexCoord_CS_in;
out vec3 Normal_CS_in;
out vec3 TanlightPos_CS_in;
out vec3 TanViewPos_CS_in;
out vec3 TanFragPos_CS_in;

void main(void)
{
	
	WorldPos_CS_in = (View*Model* vec4(Position, 1.0)).xyz;
	Normal_CS_in = ( View*Model*vec4(Normal, 0.0)).xyz;
	TexCoord_CS_in = TexCoords;

    vec3 T = normalize(mat3(View*Model) * Tangent);
    vec3 B = normalize(mat3(View*Model) * Bitangent);
    vec3 N = normalize(mat3(View*Model) * Normal);
    mat3 TBN = transpose(mat3(T, B, N));

	TanlightPos_CS_in = TBN * lightPos;
	TanViewPos_CS_in = TBN * viewPos;
	TanFragPos_CS_in = TBN * WorldPos_CS_in;
	
	gl_Position = vec4(WorldPos_CS_in,1.0);
}

