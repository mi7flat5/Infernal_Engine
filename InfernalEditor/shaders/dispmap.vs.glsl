#version 420 core

out VS_OUT
{
    vec2 tc;
	vec2 tc2;
	vec4 norm;
} vs_out;
 
void main(void)
{
    const vec4 vertices[] = vec4[](vec4(-0.5, 0.0, -0.5, 1.0),
                                   vec4( 0.5, 0.0, -0.5, 1.0),
                                   vec4(-0.5, 0.0,  0.5, 1.0),
                                   vec4( 0.5, 0.0,  0.5, 1.0));

    int x = gl_InstanceID & 63;
    int y = gl_InstanceID >> 6;
    vec2 offs = vec2(x, y);
	//vec3 normal;
	//for (int i=0; i<4; i++)
	//{
	//	int j = (i+1)%4;
	//	normal.x += (vertices[i].y - vertices[j].y)
	//			   *(vertices[i].z + vertices[j].z);
	//	normal.y += (vertices[i].z - vertices[j].z)
	//			   *(vertices[i].x + vertices[j].x);
	//	normal.z += (vertices[i].x - vertices[j].x)
	//			   *(vertices[i].y + vertices[j].y);
	//}
	//vs_out.norm = vec4(normalize (normal),1.0)+ vec4(float(x - 8), 0.0, float(y - 8), 0.0);
	
    vs_out.tc = (vertices[gl_VertexID].xz + offs + vec2(0.5))/64;
	vs_out.tc2 = (vertices[gl_VertexID].xz + offs + vec2(0.5))/2;
    gl_Position = vertices[gl_VertexID]+ vec4(float(x - 32), 0.0, float(y - 32), 0.0);

}
