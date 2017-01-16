#version 420 core

out vec4 color;


struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
	sampler2D texture_normal1;
	sampler2D texture_displacement1;
    float shininess;
}; 
uniform Material material;
//uniform mat3 View;
uniform vec3 light; 
uniform bool enable_fog = true;
uniform vec4 fog_color = vec4(0.1, 0.1, 0.1, 0.0);
float density = 0.008;
float LOG2 = 1.442695;


in TES_OUT
{
    vec2 tc;
	vec2 tc2;
	vec3 tanFragPos;
	vec3 tanLightPos;
	vec3 tanViewPos;
    vec3 world_coord;
    vec3 eye_coord;
	vec4 norm;
	vec4 tang;
	vec4 bittang;
} fs_in;
uniform vec3 viewPos;


vec3 Tangent_Normal()
{
	vec3 TangNorm = texture(material.texture_normal1,fs_in.tc2).rgb;
	return normalize(TangNorm*2.0-1.0);
}
vec4 fog(vec4 c)
{
    float z = length(viewPos);

    float de = 0.025 * smoothstep(0.0, 6.0, 10.0 - fs_in.world_coord.y);
    float di = 0.045 * (smoothstep(0.0, 40.0, 20.0 - fs_in.world_coord.y));

    float extinction   = exp(-z * de);
    float inscattering = exp(-z * di);

    return c * extinction + fog_color * (1.0 - inscattering);
}

void main(void)
{
	
	float ambientStrength = 0.7;
	
		float specularStrength = .9;
	vec3 viewDirs = normalize(fs_in.tanViewPos-fs_in.tanFragPos);
	vec3 lightDirs = normalize(fs_in.tanLightPos-fs_in.tanFragPos);
	vec3 reflectDir = reflect(-lightDirs, Tangent_Normal());  
	vec3 halfwayDir = normalize(fs_in.tanLightPos + fs_in.tanViewPos);
	 float spec = pow(max(dot( halfwayDir,Tangent_Normal() ), 0.0), 256);
	vec3 specular = specularStrength * spec*vec3(1,1,1);
	
    vec4 landscape = texture(material.texture_diffuse1, fs_in.tc2);
	vec3 lightDir = normalize(fs_in.tanLightPos-fs_in.tanFragPos);
	float diff = max(dot(lightDir,Tangent_Normal()), 0.0);
	landscape =diff * landscape+ vec4(specular,1);

    if (enable_fog)
    {
		
        float z = (fs_in.eye_coord).z;
		float fogFactor = exp2(-density *density*z*z*LOG2);
		fogFactor = clamp(fogFactor,0.0,1.0);
		
		
		color = mix(fog_color,landscape,fogFactor);
    }
    else{
    
        color = landscape;
    }
}
