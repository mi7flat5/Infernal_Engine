#version 420 core

layout (quads, fractional_odd_spacing) in;
struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
	sampler2D texture_normal1;
	sampler2D texture_displacement1;
    float shininess;
};

uniform Material material;
uniform mat4 Projection,View,Model;
uniform float DispLevel;
uniform vec3 lightPos,viewPos;


in TCS_OUT
{
    vec2 tc;
	vec2 tc2;
	vec4 norm;
} tes_in[];

out TES_OUT
{
    vec2 tc;
	vec2 tc2;
    vec3 world_coord;
    vec3 eye_coord;
	vec4 norm;

	
} tes_out;

void main(void)
{
    vec2 tc1 = mix(tes_in[0].tc, tes_in[1].tc, gl_TessCoord.x);
    vec2 tc2 = mix(tes_in[2].tc, tes_in[3].tc, gl_TessCoord.x);
    vec2 tc = mix(tc2, tc1, gl_TessCoord.y);
	 tc1 = mix(tes_in[0].tc2, tes_in[1].tc2, gl_TessCoord.x);
     tc2 = mix(tes_in[2].tc2, tes_in[3].tc2, gl_TessCoord.x);
	 tc2 = mix(tc2, tc1, gl_TessCoord.y);
	 vec4 norm1 = mix(tes_in[0].norm, tes_in[1].norm, gl_TessCoord.x);
    vec4 norm2 = mix(tes_in[2].norm, tes_in[3].norm, gl_TessCoord.x);
	vec4  n = mix(norm2, norm1, gl_TessCoord.y);
	n.y += texture(material.texture_displacement1, tc).r *200.0;
    vec4 p1 = mix(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_TessCoord.x);
    vec4 p2 = mix(gl_in[2].gl_Position, gl_in[3].gl_Position, gl_TessCoord.x);
    vec4 p = mix(p2, p1, gl_TessCoord.y);
    p.y += texture(material.texture_displacement1, tc).r *253.555;

    vec4 P_eye = View*Model * p;
	vec4 N_eye = View*Model* n;

    tes_out.tc = tc;
	tes_out.tc2 = tc2;
    tes_out.world_coord = p.xyz;
    tes_out.eye_coord = P_eye.xyz;
	tes_out.norm = Projection * N_eye;
    gl_Position = Projection *P_eye;
}
