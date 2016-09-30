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
#include"GL\glew.h"
#include"GLFW\glfw3.h"
#include"GL\glut.h"

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
#include"Scene.h"
#include"EventManagerImpl.h"




#if defined(_DEBUG)
#	define INFERNAL_NEW new(_NORMAL_BLOCK,__FILE__, __LINE__)
#else
#	define INFERNAL_NEW new
#endif

using vec3 = glm::vec3;
using vec4 = glm::vec4;
using mat4 = glm::mat4;
using mat3 = glm::mat3;
