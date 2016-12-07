//Vertex shader for normal maps
#version 450 core
layout(location = 0) in vec3 Position;
// locaation 1 is index buffer
layout(location = 2) in vec3 normal;
//location 3 is diffuse colors
layout (location = 4) in vec2 texCoords;
layout (location = 5) in vec3 tangent;
layout (location = 6) in vec3 bitangent;  

out VS_OUT {
 vec3 Normal;
 vec3 FragPos;
 vec2 TexCoords;
 vec3 TanlightPos;
 vec3 TanViewPos;
 vec3 TanFragPos;
} vs_out;

uniform mat4 Projection,View, Model;

uniform vec3 lightPos;

uniform vec3 viewPos;//camera position

void main(){	

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  Projection *View *Model* vec4(Position,1.0f);

	vs_out.FragPos = vec3(  Model*vec4(Position, 1.0f));
    vs_out. Normal = vec3(View * Model*vec4(norms,0.0));
	vs_out.TexCoords = texCoords;

 
	vec3 T = normalize(vec3(View * Model * vec4(tangent,   0.0)));
	vec3 B = normalize(vec3(View * Model * vec4(bitangent, 0.0)));
	vec3 N = normalize(vec3(View * Model * vec4(normal,    0.0)));
	mat3 TBN = transpose(mat3(T, B, N));
 
	vs_out.TanlightPos = TBN * lightPos;
	vs_out.TanViewPos = TBN * viewPos;
	vs_out.TanFragPos = TBN * vs_out.FragPos;

	
}
