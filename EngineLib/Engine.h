#pragma once
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// Windows Header Files:

#define NOMINMAX
#include <windows.h>
#include <windowsx.h>

#include <crtdbg.h>

#define _VS2005_
#if _MSC_VER < 1400
#undef _VS2005_
#endif



#include<map>
#include<list>
#include<vector>
#include<fstream>
#include<sstream>
#include<iostream>
#include<string>
#include<memory>
#include <iomanip>
#include <ctime>

void flogout(const char*);



#if defined(_DEBUG)
#   define LOG_TO_FILE(str) flogout(str);
#else
#   define LOG_TO_FILE(str) 
#endif



#if defined(_DEBUG)
#	define INFERNAL_NEW new(_NORMAL_BLOCK,__FILE__, __LINE__)
#else
#	define INFERNAL_NEW new
#endif

#include <crtdbg.h>
#include <stdlib.h>
#include <mmsystem.h>
#include <limits>


#include"glm\glm.hpp"
#include"glm\gtc\matrix_transform.hpp"
#include"glm\gtc\type_ptr.hpp"
#include"GL\glew.h"
#include"GLFW\glfw3.h"
#include"GL\glut.h"


#include"Utility\Logger.h"
#include"assimp\Importer.hpp"
#include"assimp\scene.h"        
#include"assimp\postprocess.h"
#include"SOIL\SOIL.h"
#include"Utility\Transform.h"



#include"tinyxml2.h"
#include"Utility\interfaces.h"
#include"Utility\Template.h"
#include"Utility\Utility.h"
#include"3DRender\Scene.h"
#include"3DRender\Mesh.h"
#include"EventSystem\EventManagerImpl.h"
#include"EventSystem\Event.h"
#include"SHObject\ObjectFactory.h"



using vec3 = glm::vec3;
using vec4 = glm::vec4;
using mat4 = glm::mat4;
using mat3 = glm::mat3;


extern vec3 g_Up;
extern vec3 g_Right;
extern vec3 g_Forward;

extern vec4 g_Up4;
extern vec4 g_Right4;
extern vec4 g_Forward4;

extern GLuint HEIGHT, WIDTH;
extern GLdouble g_DeltaTime;

