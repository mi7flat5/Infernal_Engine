#version 450 core
//Texture fragment shader with map shading options
//TODO add uniforms to control ambient, and specular strengths 
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
	sampler2D texture_displacement1;
    float shininess;
}; 

uniform vec3 lightColor;
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform Material material;
uniform mat4 View;
uniform samplerCube SkyBox;
uniform int Mode;
out vec4 FragColor;

//Main functions returning fragment color
vec4 Diffuse_Only_Texture();
vec4 Diffuse_With_NormalMap();
vec4 Diffuse_SpecularMap_NormalMap();
vec4 Diffuse_SpecularMap();

// utility functions returning respective fragment color components
vec3 Ambient();
vec3 Diffuse();
vec3 Specular();
vec3 Diffuse_NormalMap();
vec3 Specular_Map();
vec3 Tangent_Normal();
vec2 ParallaxMapping(vec2 , vec3 );
vec3 ViewDirection();

vec2 TEXCOORDS;

void main()//texture fragment shader
{
	//TODO Add logic to chose shader outcome from mode uniform 
	
        TEXCOORDS = fs_in.TexCoords;
    if (Mode ==7)
        TEXCOORDS = ParallaxMapping(TEXCOORDS,  ViewDirection());
        
     //discards a fragment when sampling outside default texture region (fixes border artifacts)
    //if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
    //    discard;
	
	switch (Mode)
		{
			case 0:
				FragColor = Diffuse_Only_Texture();
				break;
			case 1:
				FragColor = Diffuse_SpecularMap();
				break;
			case 2:
				FragColor = Diffuse_With_NormalMap();
				break;
			case 3:
				FragColor = Diffuse_SpecularMap_NormalMap();
				break;
			default:
			FragColor = Diffuse_SpecularMap_NormalMap();
		}
	
} 



//Frag color out funtions
vec4 Diffuse_SpecularMap_NormalMap()
{
	return vec4((Ambient()+Diffuse_NormalMap() + Specular_Map()),0.0f);
}
vec4 Diffuse_With_NormalMap()
{
	return vec4(Ambient()+Diffuse_NormalMap()+Specular(),0.0f);
}
vec4 Diffuse_SpecularMap()
{
	return vec4(Ambient()+Diffuse()+Specular_Map(),0.0f);
}
vec4 Diffuse_Only_Texture()
{
	return vec4(Ambient()+Diffuse()+Specular(),0.0f);
}



//Utility Function
 vec3 Diffuse_NormalMap()
 {
	vec3 color = texture(material.texture_diffuse1,TEXCOORDS).rgb;
	vec3 lightDir = normalize(fs_in.TanlightPos - fs_in.TanFragPos);
	float diff = max(dot(lightDir,Tangent_Normal()), 0.0);
	return diff * color;
 }

 vec3 Specular_Map()
 {
   
	float specularStrength = 0.4;
	
	vec3 lightDir = normalize(fs_in.TanlightPos - fs_in.TanFragPos);
	// ATTENTION 
	vec3 reflectDir = reflect(-lightDir, Tangent_Normal());  
   
	vec3 halfwayDir = normalize(lightDir + ViewDirection());  
 	float spec = pow(max(dot(Tangent_Normal(),halfwayDir ), 0.0), 32);
	return specularStrength * spec*vec3(texture(material.texture_specular1,TEXCOORDS))*lightColor;  
 
 }

 vec3 Ambient()
 {
	float ambientStrength = 0.2;
	return ambientStrength* Diffuse_NormalMap();
 }

vec3 Diffuse()
{
	   
    vec3 lightDir = normalize(lightPos- fs_in.FragPos);
    float diff = max(dot(normalize(fs_in.Normal), lightDir), 0.0);
    return diff * vec3(texture(material.texture_diffuse1,TEXCOORDS));
}

vec3 Specular()
{
	float specularStrength = 0.3;
	vec3 viewDir = normalize(viewPos- fs_in.FragPos);
	vec3 lightDir = normalize(lightPos-fs_in.FragPos);
	vec3 reflectDir = reflect(-lightDir, normalize(fs_in.Normal));  
   	float spec = pow(max(dot(viewDir, reflectDir ), 0.0), 16);
	return specularStrength * spec*vec3(1,1,1);	
}

vec3 Tangent_Normal()
{
	vec3 TangNorm = texture(material.texture_normal1,TEXCOORDS).rgb;
	return normalize(TangNorm*2.0-1.0);
}


vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{ 
    // number of depth layers
    const float minLayers = 10;
    const float maxLayers = 64;
    float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));  
    // calculate the size of each layer
    float layerDepth = 1.0 / numLayers;
    // depth of current layer
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 P = viewDir.xy*0.07;//height scale 
    vec2 deltaTexCoords = P / numLayers;
  
    // get initial values
    vec2  currentTexCoords     = texCoords;
    float currentDepthMapValue = texture(material.texture_displacement1, currentTexCoords).r;
      
    while(currentLayerDepth < currentDepthMapValue)
    {
        // shift texture coordinates along direction of P
        currentTexCoords -= deltaTexCoords;
        // get depthmap value at current texture coordinates
        currentDepthMapValue = texture(material.texture_displacement1, currentTexCoords).r;  
        // get depth of next layer
        currentLayerDepth += layerDepth;  
    }
    
    // -- parallax occlusion mapping interpolation from here on
    // get texture coordinates before collision (reverse operations)
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    // get depth after and before collision for linear interpolation
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(material.texture_displacement1, prevTexCoords).r - currentLayerDepth + layerDepth;
 
    // interpolation of texture coordinates
    float weight = afterDepth / (afterDepth - beforeDepth);
    return  prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    
}
vec3 ViewDirection(){return normalize(fs_in.TanViewPos - fs_in.TanFragPos);}