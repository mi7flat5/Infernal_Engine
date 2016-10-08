#include"Engine.h"


vec3 g_Right(1.0f, 0.0f, 0.0f);
vec3 g_Up(0.0f, 1.0f, 0.0f);
vec3 g_Forward(0.0f, 0.0f, -1.0f);


vec4 g_Up4(g_Up.x, g_Up.y, g_Up.z, 0.0f);
vec4 g_Right4(g_Right.x, g_Right.y, g_Right.z, 0.0f);
vec4 g_Forward4(g_Forward.x, g_Forward.y, g_Forward.z, 0.0f);

GLdouble g_DeltaTime = 0;

GLuint HEIGHT = 600, WIDTH = 800;