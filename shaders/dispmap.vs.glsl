#version 420 core
uniform mat4 View,Model;
uniform vec3 light;
uniform vec3 viewPos;
out VS_OUT
{
    vec2 tc;
	vec2 tc2;
	vec4 tanFragPos;
	vec4 tanLightPos;
	vec4 tanViewPos;
	vec4 norm;
	vec4 tang;
	vec4 bittang;
} vs_out;
 
void main(void)
{
    const vec4 vertices[] = vec4[](vec4(-0.5, 0.0, -0.5, 1.0),
											  vec4( 0.5, 0.0, -0.5, 1.0),
											  vec4(-0.5, 0.0,  0.5, 1.0),
											  vec4( 0.5, 0.0,  0.5, 1.0));
	
	const vec4 normals[] = vec4[](vec4( 0, -1.0,  0, 1.0),
											vec4( 0, -1.0,  0, 1.0),
											vec4( 0, -1.0,  0, 1.0),
											vec4( 0, -1.0,  0, 1.0));
											
	const vec4 tangents[] = vec4[](vec4( 1, 0,  0, 1.0),
										  vec4( 1, 0,  0, 1.0),
										  vec4( 1, 0,  0, 1.0),
										  vec4( 1, 0,  0, 1.0));
											
	const vec4 bittangents[] = vec4[](vec4( 0, 0,  1, 1.0),
											 vec4( 0, 0,  1, 1.0),
											 vec4( 0, 0,  1, 1.0),
											 vec4( 0, 0,  1, 1.0));
											 
	vec3 T = normalize(mat3(Model) * vec3(tangents[gl_VertexID]));
    vec3 B = normalize(mat3(Model) * vec3(bittangents[gl_VertexID]));
    vec3 N = normalize(mat3(Model) * vec3(normals[gl_VertexID]));
    mat3 TBN = transpose(mat3(T, B, N));
											 


    int x = gl_InstanceID & 63;
    int y = gl_InstanceID >> 6;
    vec2 offs = vec2(x, y);
	vs_out.tanLightPos = vec4(light,1.0);
	vs_out.tanViewPos = vec4(viewPos,1.0);
	vs_out.tanFragPos = vec4(vec3(vertices[gl_VertexID]),1);
	
	vs_out.norm = normals[gl_VertexID]+ vec4(float(x - 32), 0.0, float(y - 32), 0.0);
	vs_out.tang = tangents[gl_VertexID]+ vec4(float(x - 32), 0.0, float(y - 32), 0.0);
	vs_out.bittang = bittangents[gl_VertexID]+ vec4(float(x - 32), 0.0, float(y - 32), 0.0);
	
    vs_out.tc = (vertices[gl_VertexID].xz + offs + vec2(0.5))/64;
	vs_out.tc2 = (vertices[gl_VertexID].xz + offs + vec2(0.5))/2;
    gl_Position = vertices[gl_VertexID]+ vec4(float(x - 32), 0.0, float(y - 32), 0.0);

}
