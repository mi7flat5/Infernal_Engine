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
uniform mat4 View;
uniform mat4 Model;

out vec3 color;

void main()
{
	//vec3 lpo = vec3(lightPos.x,lightPos.y,-lightPos.z)
    // Ambient
	
	vec3 lc = vec3(1,1,1);
    float ambientStrength = 0.6;
    vec3 ambient = ambientStrength * lc;
  	
    // Diffuse 
    vec3 norm = normalize( Normal);
    vec3 lightDir = normalize(lightPos-FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular
	vec3 specular;
    float specularStrength = 0.9;
	
    vec3 viewDir =  normalize(viewPos-fragmentColor);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
        specular = specularStrength * spec * lc;  
        
    vec3 result = (ambient + diffuse + specular)*fragmentColor;
    color =result;
	
} 