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
    // Ambient
    float ambientStrength = 0.4f;
    vec3 ambient = ambientStrength * lightColor;
  	
    // Diffuse 
    vec3 norm = normalize(mat3(inverse(View))* Normal);
    vec3 lightDir = normalize(lightPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular
	vec3 specular;
    float specularStrength = 0.9;
	 vec3 normalDirection = normalize(mat3(inverse(View))* Normal);
    vec3 viewDir =  normalize(vec3(View * vec4(0.0, 0.0, 0.0, 1.0) - Model* vec4(FragPos,0.0)));
    vec3 reflectDir = reflect(-lightDir, normalDirection);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
        specular = specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + diffuse + specular)*fragmentColor;
    color = result;
	
} 