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

	uniform mat4 Projection, View, Model;
	uniform Material material;
	uniform vec3 lightPos;
	uniform vec3 viewPos;
	
	uniform sampler2D DisplacementMap;
	
void main()//displacement mapping vertex shader, requires many verices, prefer tesselation shading
{


		vec4 newVertexPos;
		vec4 DisplacementVector;
		float DisplacementFactor;
		vec2  DisplacedTexCoords = texCoords;
		DisplacementVector = texture2D(material.texture_displacement1,texCoords);
		DisplacementFactor = 0.590*DisplacementVector.x + 0.11*DisplacementVector.y + 0.59*DisplacementVector.z;
		newVertexPos = vec4(normalize(normal) * DisplacementFactor * 0.001, 0.0) + vec4(Position,1.0);
		
		vec3 T = normalize(mat3(View * Model) * tangent);
		vec3 B = normalize(mat3(View * Model) * bitangent);
		vec3 N = normalize(mat3(View * Model) * normal);
		mat3 TBN = transpose(mat3(T, B, N));

		vs_out.FragPos = vec3( View * Model * newVertexPos);
		vs_out.Normal = vec3(View * Model * vec4(norms,0.0));
		vs_out.TexCoords = texCoords;
		vs_out.TanlightPos = TBN * lightPos;
		vs_out.TanViewPos = TBN * viewPos;
		vs_out.TanFragPos = TBN * vs_out.FragPos;
		gl_Position =  Projection * View * Model* newVertexPos;
}	