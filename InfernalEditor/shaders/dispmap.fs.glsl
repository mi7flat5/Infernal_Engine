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
uniform bool enable_fog = true;
uniform vec4 fog_color = vec4(0.1, 0.1, 0.1, 0.0);
float density = 0.008;
float LOG2 = 1.442695;


in TES_OUT
{
    vec2 tc;
	vec2 tc2;
    vec3 world_coord;
    vec3 eye_coord;
	vec4 norm;
} fs_in;
uniform vec3 viewPos;
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
	
    vec4 landscape = texture(material.texture_diffuse1, fs_in.tc2);

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
