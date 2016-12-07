#version 450 core

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
}; 

in vec3 fragmentColor;
in vec3 Normal;
in vec3 FragPos;

in vec2 TexCoords;

uniform vec3 lightColor;
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform Material material;

out vec3 color;


void main()//texture fragment shader
{
    // Ambient
    float ambientStrength = 0.2f;
    vec3 ambient = ambientStrength* vec3(texture(material.texture_diffuse1,TexCoords))*lightColor;
  	
    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(texture(material.texture_diffuse1,TexCoords))*lightColor;
    
    // Specular
    float specularStrength = 0.6;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec*vec3(texture(material.texture_specular1,TexCoords))*lightColor;  
        
    vec3 result = (ambient + diffuse + specular);
    color =  result; //output for this main is vec3
	
} 
