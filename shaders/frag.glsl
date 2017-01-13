#version 450 core


in vec3 fragmentColor;
in vec3 Normal;
in vec3 FragPos;



uniform vec3 lightPos; 
uniform vec3 viewPos;



out vec3 color;

void main()
{

    // Ambient
	
	vec3 lc = vec3(1,1,1);
    float ambientStrength = 0.6;
    vec3 ambient = ambientStrength * lc;
  	
    // Diffuse 
    vec3 norm = normalize( Normal);
    vec3 lightDir = normalize(lightPos-FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lc;
    
    // Specular
	vec3 specular;
    float specularStrength = 0.9;
	
    vec3 viewDir =  normalize(viewPos-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
        specular = specularStrength * spec * lc;  
        
    vec3 result = (ambient + diffuse + specular)*fragmentColor;
    color = result;
	
} 