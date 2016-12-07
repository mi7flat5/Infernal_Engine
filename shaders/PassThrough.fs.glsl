#version 450 core
//Texture fragment shader with map shading options
//TODO add uniforms to control ambient, and specular strengths 
in vec3 WorldPos_FS_in;
in vec2 TexCoord_FS_in;
in vec3 Normal_FS_in;
in vec3 TanlightPos_FS_in;
in vec3 TanViewPos_FS_in;
in vec3 TanFragPos_FS_in;



struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
	sampler2D texture_normal1;
	sampler2D texture_displacement1;
    float shininess;
}; 

uniform Material material;
uniform bool NormMapping;
float density = 0.008;
float LOG2 = 1.442695;
vec4 fog_color = vec4(0.1, 0.1, 0.1, 0.0);

out vec4 color;
 vec3 Tangent_Normal()
{
	vec3 TangNorm = texture(material.texture_normal1,TexCoord_FS_in).rgb;
	return normalize(TangNorm*2.0-1.0);
}
vec3 ViewDirection(){return normalize(TanViewPos_FS_in - TanFragPos_FS_in);}
vec3 Specular_Map()
 {
   
	float specularStrength = material.shininess;
	
	vec3 lightDir = normalize(TanlightPos_FS_in - TanFragPos_FS_in);
	// ATTENTION 
	vec3 reflectDir = reflect(-lightDir, Tangent_Normal());  
   
	vec3 halfwayDir = normalize(lightDir + ViewDirection());  
 	float spec = pow(max(dot(Tangent_Normal(),halfwayDir ), 0.0), 32);
	return specularStrength * spec*vec3(texture(material.texture_specular1,TexCoord_FS_in));  
 
 }
 vec3 Diffuse_NormalMap()
 {
	vec3 color = texture(material.texture_diffuse1,TexCoord_FS_in).rgb;
	vec3 lightDir = normalize(TanlightPos_FS_in - TanFragPos_FS_in);
	float diff = max(dot(lightDir,Tangent_Normal()), 0.0);
	return diff * color;
 }



void main(void)
{
	if (NormMapping)
	{

		float z = (WorldPos_FS_in).z;
		float fogFactor = exp2(-density *density*z*z*LOG2);
		fogFactor = clamp(fogFactor,0.0,1.0);
		
		
		color = mix(fog_color,vec4(Diffuse_NormalMap()+Specular_Map(),1.0),fogFactor)*0.7f;
		//color  = vec4(Diffuse_NormalMap()+Specular_Map(),1.0);
	}
	else
	{
		color = texture(material.texture_diffuse1, TexCoord_FS_in)*0.7f;
	}
}