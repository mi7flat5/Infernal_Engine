#version 450 core
	layout(location = 0) in vec3 Position;
	// locaation 1 is index buffer
	layout(location = 2) in vec3 normal;
	//location 3 is diffuse colors
	layout (location = 4) in vec2 texCoords;
	layout (location = 5) in vec3 tangent;
	layout (location = 6) in vec3 bitangent;  

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
	sampler2D texture_normal1;
	sampler2D texture_displacement1;
    float shininess;
}; 

out VS_OUT {
	 vec3 Normal;
	 vec3 FragPos;
	 vec2 TexCoords;
	 vec3 TanlightPos;
	 vec3 TanViewPos;
	 vec3 TanFragPos;
} vs_out;

	uniform mat4 Projection;
	uniform Material material;
	uniform vec3 lightPos;
	uniform mat4 Model;
	uniform vec3 viewPos;
	uniform mat4 View;
	uniform int Mode;
	


void main(){	
	
	 vec3 norm = texture(material.texture_normal1, texCoords).rgb;
	// Output position of the vertex, in clip space : MVP * position
	
	gl_Position =  Projection *View*Model* vec4(Position,1.0f);
	vs_out.FragPos = vec3(Model * vec4(Position, 1.0));
	vs_out.Normal = normalize(transpose(inverse(mat3(Model)))*normal);
    vs_out.TexCoords = texCoords;
       
    vec3 T = normalize(mat3(Model) * tangent);
    vec3 B = normalize(mat3(Model) * bitangent);
    vec3 N = normalize(mat3(Model) * normal);
    mat3 TBN = transpose(mat3(T, B, N));

	vs_out.TanlightPos = normalize(TBN * lightPos);
	vs_out.TanViewPos = normalize(TBN * viewPos);
	vs_out.TanFragPos = TBN * vs_out.FragPos;
	norm = normalize(normal *2.0-1.0);
	//vs_out.Normal = norm; //normalize(TBN*norm);
}
