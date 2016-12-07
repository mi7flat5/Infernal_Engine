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



#include <crtdbg.h>
#include <stdlib.h>
#include <mmsystem.h>
#include <limits>


#include"glm\glm.hpp"
#include"glm\gtc\matrix_transform.hpp"
#include"glm\gtc\type_ptr.hpp"
#include"GL\glew.h"


#include"assimp\Importer.hpp"
#include"assimp\scene.h"        
#include"assimp\postprocess.h"
#include"include\SOIL\SOIL.h"
#include"Transform.h"


#include<map>
#include<list>
#include<vector>
#include<fstream>
#include<sstream>
#include<iostream>
#include<string>
#include<memory>
#include"tinyxml2.h"
#include"interfaces.h"
#include"Template.h"
#include"Utility.h"
#include"Inf_Scene.h"
#include"Inf_Mesh.h"

#include"FastDelegate.h"
#include"EventManagerImpl.h"
#include"EventManager.h"
#include"ObjectFactory.h"
#include"SceneNode.h"







#if defined(_DEBUG)
#	define INFERNAL_NEW new
#else
#	define INFERNAL_NEW new
#endif

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