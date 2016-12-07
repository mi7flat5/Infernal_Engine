#version 420 core

layout (triangles, equal_spacing,ccw) in;


in vec3 WorldPos_ES_in[];
in vec2 TexCoord_ES_in[];
in vec3 Normal_ES_in[];
in vec3 TanlightPos_ES_in[];
in vec3 TanViewPos_ES_in[];
in vec3 TanFragPos_ES_in[];

out vec3 WorldPos_FS_in;
out vec2 TexCoord_FS_in;
out vec3 Normal_FS_in;
out vec3 TanlightPos_FS_in;
out vec3 TanViewPos_FS_in;
out vec3 TanFragPos_FS_in;


struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
	sampler2D texture_normal1;
	sampler2D texture_displacement1;
    float shininess;
}; 
uniform vec3 viewPos;
uniform mat4 Projection, View, Model;
uniform Material material;
uniform float DispLevel;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
   	return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
   	return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}


void main(void)
{
	
	
	TexCoord_FS_in = interpolate2D(TexCoord_ES_in[0], TexCoord_ES_in[1], TexCoord_ES_in[2]);
   	Normal_FS_in = interpolate3D(Normal_ES_in[0], Normal_ES_in[1], Normal_ES_in[2]);
	Normal_FS_in = normalize(Normal_FS_in);
   	TanlightPos_FS_in = interpolate3D(TanlightPos_ES_in[0], TanlightPos_ES_in[1], TanlightPos_ES_in[2]);
	TanViewPos_FS_in = interpolate3D(TanViewPos_ES_in[0], TanViewPos_ES_in[1], TanViewPos_ES_in[2]);
	TanFragPos_FS_in = interpolate3D(TanFragPos_ES_in[0], TanFragPos_ES_in[1], TanFragPos_ES_in[2]);
	WorldPos_FS_in = interpolate3D(WorldPos_ES_in[0], WorldPos_ES_in[1], WorldPos_ES_in[2]);

	float Displacement = texture(material.texture_displacement1, TexCoord_FS_in).r*DispLevel;
	//Displacement += noise1(viewPos.x*viewPos.z)*10;
   	WorldPos_FS_in +=Normal_FS_in* Displacement ;
   	gl_Position = Projection * vec4(WorldPos_FS_in, 1.0);
}
