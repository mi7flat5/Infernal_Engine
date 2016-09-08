#pragma once
#include"SceneNode.h"
class CubeMapNode :public SceneNode
{
	//this loads the texture files and holds the texture and vert data
	//perhaps move verts into shader
public:
	CubeMapNode();
	~CubeMapNode();
};

class OGLCubemap : public CubeMapNode {
	//this holds buffer data and does the actual drawing

};