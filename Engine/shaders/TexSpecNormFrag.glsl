#version 450 core
in VS_OUT {
 vec3 Normal;
 vec3 FragPos;
 vec2 TexCoords;
 vec3 TanlightPos;
 vec3 TanViewPos;
 vec3 TanFragPos;
} fs_in;

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
	sampler2D texture_normal1;
    float shininess;
}; 



uniform vec3 lightColor;
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform Material material;
uniform mat4 View;
uniform samplerCube SkyBox;
out vec4 FragColor;


void main()//texture fragment shader
{
 //   vec3 I = normalize(fs_in.FragPos);
	//vec3 Reflection = reflect(I, normalize(fs_in.Normal));
	//Reflection = vec3 (inverse (View) * vec4 (Reflection, 0.0));
	//vec4 ReflectColor = texture(SkyBox, Reflection);
	
	vec3 TangNorm = texture(material.texture_normal1,fs_in.TexCoords).rgb;
	TangNorm = normalize(TangNorm*2.0-1.0);
	vec3 color = texture(material.texture_diffuse1,fs_in.TexCoords).rgb;


	// Ambient
    float ambientStrength = 0.4f;
    vec3 ambient = ambientStrength* vec3(texture(material.texture_diffuse1,fs_in.TexCoords))*lightColor;
  	
    // Diffuse 
    ////vec3 norm = normalize(fs_in.Normal);
    vec3 lightDir = normalize(fs_in.TanlightPos - fs_in.TanFragPos);
    float diff = max(dot(TangNorm, lightDir), 0.0);
    vec3 diffuse = diff * color*lightColor;
    
    // Specular
    float specularStrength = 0.2;
    vec3 viewDir = normalize(fs_in.TanViewPos- fs_in.TanFragPos);
    vec3 reflectDir = reflect(lightDir, TangNorm);  
   
    vec3 halfwayDir = normalize(-lightDir + viewDir);  
    //float spec = pow(max(dot(TangNorm, halfwayDir), 0.0), 32.0);
    //   vec3 specular = vec3(0.4) * spec;
   
    float spec = pow(max(dot(TangNorm, halfwayDir ), 0.0), 32);
    vec3 specular = specularStrength * spec*vec3(texture(material.texture_specular1,fs_in.TexCoords));  
  
    vec4 result = vec4((ambient + diffuse + specular),1.0);
	//result = mix(ReflectColor,vec4(0.01,0.7,0.15,1),0.2);
    FragColor =  result; //output for this main is vec3
	
} 
