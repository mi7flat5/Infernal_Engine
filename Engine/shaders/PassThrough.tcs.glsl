#version 420 core

layout (vertices =3) out;

in vec3 WorldPos_CS_in[];
in vec2 TexCoord_CS_in[];
in vec3 Normal_CS_in[];
in vec3 TanlightPos_CS_in[];
in vec3 TanViewPos_CS_in[];
in vec3 TanFragPos_CS_in[];

// attributes of the output CPs
out vec3 WorldPos_ES_in[];
out vec2 TexCoord_ES_in[];
out vec3 Normal_ES_in[];
out vec3 TanlightPos_ES_in[];
out vec3 TanViewPos_ES_in[];
out vec3 TanFragPos_ES_in[];

uniform mat4 Projection, View, Model;
uniform vec3 viewPos;

float GetTessLevel(float Distance0, float Distance1)
{
    float AvgDistance = (Distance0 + Distance1) / 2.0;

    if (AvgDistance <= 2.0) {
        return 50.0;
    }
    else if (AvgDistance <= 5.0) {
        return 50.0;
    }
    else {
        return 20.0;
    }
}

void main(void)
{
		
	vec3 gEyeWorldPos = viewPos ;
	TexCoord_ES_in[gl_InvocationID] = TexCoord_CS_in[gl_InvocationID];
    Normal_ES_in[gl_InvocationID] = Normal_CS_in[gl_InvocationID];
    WorldPos_ES_in[gl_InvocationID] = WorldPos_CS_in[gl_InvocationID];
	TanlightPos_ES_in[gl_InvocationID] = TanlightPos_CS_in[gl_InvocationID];
	TanViewPos_ES_in[gl_InvocationID] = TanViewPos_CS_in[gl_InvocationID];
	TanFragPos_ES_in[gl_InvocationID] =TanFragPos_CS_in[gl_InvocationID];
	
	 // Calculate the distance from the camera to the three control points
    float EyeToVertexDistance0 = distance(gEyeWorldPos, WorldPos_ES_in[0]);
    float EyeToVertexDistance1 = distance(gEyeWorldPos, WorldPos_ES_in[1]);
    float EyeToVertexDistance2 = distance(gEyeWorldPos, WorldPos_ES_in[2]);

	 gl_TessLevelOuter[0] = GetTessLevel(EyeToVertexDistance1, EyeToVertexDistance2);
    gl_TessLevelOuter[1] = GetTessLevel(EyeToVertexDistance2, EyeToVertexDistance0);
    gl_TessLevelOuter[2] = GetTessLevel(EyeToVertexDistance0, EyeToVertexDistance1);
    gl_TessLevelInner[0] = gl_TessLevelOuter[2];


    // Calculate the tessellation levels
 //   if (gl_InvocationID == 0)
 //   {
 //   gl_TessLevelOuter[0] = 100;
 //   gl_TessLevelOuter[1] = 100;
 //   gl_TessLevelOuter[2] = 100;
 //   gl_TessLevelInner[0] = 100;
	//}
}

