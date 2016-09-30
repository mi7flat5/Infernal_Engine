#version 420 core

layout (vertices = 4) out;

in VS_OUT
{
    vec2 tc;
	vec2 tc2;
	vec4 norm;
	
} tcs_in[];

out TCS_OUT
{
    vec2 tc;
	vec2 tc2;
	vec4 norm;
	
} tcs_out[];

uniform mat4 Projection,View,Model;

void main(void)
{

  
            gl_TessLevelOuter[0] = 5;
            gl_TessLevelOuter[1] = 5;
            gl_TessLevelOuter[2] = 5;
            gl_TessLevelOuter[3] = 5;
            gl_TessLevelInner[0] = 10;
            gl_TessLevelInner[1] = 10;
       
    
	
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    tcs_out[gl_InvocationID].tc = tcs_in[gl_InvocationID].tc;
	tcs_out[gl_InvocationID].tc2 = tcs_in[gl_InvocationID].tc2;
	tcs_out[gl_InvocationID].norm = tcs_in[gl_InvocationID].norm;
	
}
