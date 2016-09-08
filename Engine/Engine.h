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

#include"glm\glm.hpp"
#include"GL\glew.h"
#include"GLFW\glfw3.h"
#include"GL\glut.h"

#include<assimp\Importer.hpp>
#include<assimp\scene.h>        
#include<assimp\postprocess.h>
#include<SOIL\SOIL.h>
#include<map>
#include<vector>
#include<iostream>
#include<memory>
#include"tinyxml2.h"
#include"interfaces.h"
#include"Template.h"
#include"Utility.h"




#if defined(_DEBUG)
#	define INFERNAL_NEW new(_NORMAL_BLOCK,__FILE__, __LINE__)
#else
#	define INFERNAL_NEW new
#endif

