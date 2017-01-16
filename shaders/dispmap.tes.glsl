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
	vec4 tanFragPos;
	vec4 tanLightPos;
	vec4 tanViewPos;
	vec4 norm;
	vec4 tang;
	vec4 bittang;
} tes_in[];

out TES_OUT
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
	//n.y += texture(material.texture_displacement1, tc).r *253.0;
	
	vec4 tang1 = mix(tes_in[0].tang, tes_in[1].tang, gl_TessCoord.x);
    vec4 tang2 = mix(tes_in[2].tang, tes_in[3].tang, gl_TessCoord.x);
	vec4  t = mix(tang2, tang1, gl_TessCoord.y);
	//t.y += texture(material.texture_displacement1, tc).r *253.0;
	
	vec4 bittang1 = mix(tes_in[0].bittang, tes_in[1].bittang, gl_TessCoord.x);
    vec4 bittang2 = mix(tes_in[2].bittang, tes_in[3].bittang, gl_TessCoord.x);
	vec4  bt = mix(bittang2, bittang1, gl_TessCoord.y);
	//bt.y += texture(material.texture_displacement1, tc).r *253.0;
  
  vec4 tlp1 = mix(tes_in[0].tanLightPos, tes_in[1].tanLightPos, gl_TessCoord.x);
    vec4 tlp2 = mix(tes_in[2].tanLightPos, tes_in[3].tanLightPos, gl_TessCoord.x);
	vec4  tlp = mix(tlp2, tlp1, gl_TessCoord.y);
	
	 vec4 tvp1 = mix(tes_in[0].tanViewPos, tes_in[1].tanViewPos, gl_TessCoord.x);
    vec4 tvp2 = mix(tes_in[2].tanViewPos, tes_in[3].tanViewPos, gl_TessCoord.x);
	vec4  tvp = mix(tvp2, tvp1, gl_TessCoord.y);
	
	 vec4 tfp1 = mix(tes_in[0].tanFragPos, tes_in[1].tanFragPos, gl_TessCoord.x);
    vec4 tfp2 = mix(tes_in[2].tanFragPos, tes_in[3].tanFragPos, gl_TessCoord.x);
	vec4  tfp = mix(tfp2, tfp1, gl_TessCoord.y);
	
  
	vec4 p1 = mix(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_TessCoord.x);
    vec4 p2 = mix(gl_in[2].gl_Position, gl_in[3].gl_Position, gl_TessCoord.x);
    vec4 p = mix(p2, p1, gl_TessCoord.y);
    p.y += texture(material.texture_displacement1, tc).r *253.0;

    vec4 P_eye = View*Model * p;
	vec4 N_eye = View*Model* n;
	vec4 T_eye = View*Model* t;
	vec4 BT_eye = View*Model* bt;
	
	vec3 normmap =vec3(texture(material.texture_normal1, tc2).r );
	
	vec3 c1 = cross(normmap, vec3(0.0, 0.0, 1.0)); 
	vec3 c2 = cross(normmap, vec3(0.0, 1.0, 0.0)); 
	vec3 tan;
	vec3 bittan;
	if( length(c1) > length(c2) )
		{
			tan = c1;	
		}
	else
		{
			tan = c2;	
		}
	
	tan = normalize(tan);
	bittan = cross(tan,normmap);
	
	vec3 T = normalize(mat3(inverse(View)) * vec3(tan));
    vec3 B = normalize(mat3(inverse(View)) * vec3(bittan));
    vec3 N = normalize(mat3(inverse(View)) * vec3(normmap));
    mat3 TBN = transpose(mat3(T, B, N));
	
	
    tes_out.tc = tc;
	tes_out.tc2 = tc2;
	
    tes_out.world_coord = p.xyz;
    tes_out.eye_coord = P_eye.xyz;
	
	tes_out.tanFragPos = TBN*vec3(tfp);
	tes_out.tanLightPos = TBN*vec3(tlp);//(tlp).xyz;
	tes_out.tanViewPos = TBN*vec3(tvp);;
	
	
	tes_out.norm = n;
	tes_out.tang = t;
	tes_out.bittang = bt;
	
    gl_Position = Projection *P_eye;
}
