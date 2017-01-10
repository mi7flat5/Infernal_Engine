#include"Engine.h"
#include "SceneNode.h"
#include"Scene.h"
#include"..//3DRender/GraphicsDebug.h"

//CameraNode::

SceneNode::SceneNode() {}

void SceneNode::SetMeshList(std::vector<Mesh> inMesh)
{
	m_Meshes = inMesh;
}




void SceneNode::VSetTransform(mat4 * toWorld, mat4 * fromWorld)
{
	ModelMatrix = *toWorld;
}

void SceneNode::VOnRestore(Scene * pScene)
{
}

void SceneNode::VOnUpdate(Scene *pScene, unsigned long const elapsedMs)
{
	// Iterate through the children....
	SceneNodeList::iterator i = m_Children.begin();
	SceneNodeList::iterator end = m_Children.end();

	while (i != end)
	{
		(*i)->VOnUpdate(pScene, elapsedMs);
		++i;
	}
}



bool SceneNode::VPreRender(Scene * pScene)
{
	return true;
}

bool SceneNode::VIsVisible(Scene * pScene) const
{
	return true;
}

void SceneNode::VRender(Scene * pScene)
{

}

void SceneNode::VRenderChildren(Scene * pScene)
{
	// Iterate through the children....
	SceneNodeList::iterator i = m_Children.begin();
	SceneNodeList::iterator end = m_Children.end();

	while (i != end)
	{
		if ((*i)->VPreRender(pScene))
		{
		
			if ((*i)->VIsVisible(pScene))
			{
				(*i)->VRender(pScene);
			
				(*i)->VRenderChildren(pScene);
			}
					
		}
		(*i)->VPostRender(pScene);
		++i;
	}
}

void SceneNode::VPostRender(Scene * pScene)
{
}

bool SceneNode::VAddChild(std::shared_ptr<ISceneNode> ikid)
{
	
	m_Children.push_back(ikid);

	std::shared_ptr<SceneNode> kid = std::static_pointer_cast<SceneNode>(ikid);

	kid->m_pParent = this;
	return true;
}

bool SceneNode::VRemoveChild(ObjectId id)
{
	for (SceneNodeList::iterator i = m_Children.begin(); i != m_Children.end(); ++i)
	{
		const SceneNodeProperties* pProps = (*i)->VGet();

		if (pProps->GetId() != INVALID_OBJECT_ID && id == pProps->GetId())
		{
			char a[5];
			long b = (*i).use_count();
			itoa(b, a, 10);
			EDITOR_LOG(a)
			
				
				i = m_Children.erase(i);	//this can be expensive for vectors
			return true;
		}
	}
	return false;
}

void SceneNode::VOnLostDevice(Scene * pScene)
{
}

SceneNodeProperties::SceneNodeProperties(void)
{
}

RootNode::RootNode() : SceneNode(INVALID_OBJECT_ID, WeakBaseRenderComponentPtr(), RenderPass_0)
{
	m_Children.reserve(RenderPass_Last);

	std::shared_ptr<SceneNode> staticGroup(INFERNAL_NEW SceneNode(INVALID_OBJECT_ID, WeakBaseRenderComponentPtr(), RenderPass_Static));
	m_Children.push_back(staticGroup);	// RenderPass_Static = 0

	std::shared_ptr<SceneNode> actorGroup(INFERNAL_NEW SceneNode(INVALID_OBJECT_ID, WeakBaseRenderComponentPtr(), RenderPass_Actor));
	m_Children.push_back(actorGroup);	// RenderPass_Actor = 1

	std::shared_ptr<SceneNode> skyGroup(INFERNAL_NEW SceneNode(INVALID_OBJECT_ID, WeakBaseRenderComponentPtr(), RenderPass_Sky));
	m_Children.push_back(skyGroup);	// RenderPass_Sky = 2

	std::shared_ptr<SceneNode> invisibleGroup(INFERNAL_NEW SceneNode(INVALID_OBJECT_ID, WeakBaseRenderComponentPtr(), RenderPass_NotRendered));
	m_Children.push_back(invisibleGroup);	// RenderPass_NotRendered = 3

	

}

bool RootNode::VAddChild(std::shared_ptr<ISceneNode> kid)
{
	
	RenderPass pass = kid->VGet()->RenderPass();
	
	return m_Children[pass]->VAddChild(kid);
}

void RootNode::VRenderChildren(Scene * pScene)
{
	for (int pass = RenderPass_0; pass < RenderPass_Last; ++pass)
	{
		switch (pass)
		{
		case RenderPass_Static:
		case RenderPass_Actor:
			m_Children[pass]->VRenderChildren(pScene);
			
			break;

		case RenderPass_Sky:
		{

			m_Children[pass]->VRenderChildren(pScene);
			break;
		}
		}
	}
}

bool RootNode::VRemoveChild(ObjectId id)
{
	
		bool anythingRemoved = false;
	for (int i = RenderPass_0; i < RenderPass_Last; ++i)
	{
		if (m_Children[i]->VRemoveChild(id))
		{
			anythingRemoved = true;
		}
	}
	if(anythingRemoved)
		EDITOR_LOG("Object Removed")
	return anythingRemoved;
}

void RootNode::VOnUpdate(Scene *pScene, unsigned long const elapsedMs)
{

	for (int i = 0; i < m_Children.size();i++)
		m_Children[i]->VOnUpdate(pScene,elapsedMs);
	
}



void CameraNode::UpdateOffsetsVectors()
{
	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89)
		pitch = -89;

	theta = yaw-90;
	phi = pitch-90;

	//front.x = radius * sin(glm::radians(phi))*cos(glm::radians(theta));
	//if (campos.y > TerrainHeight)
	//front.y = radius * cos(glm::radians(pitch + 90));// +10; //TODO add parameter for adjusting y facing offset
	//front.z = radius * cos(glm::radians(phi))*sin(glm::radians(theta));
	
	camfront = glm::normalize(Target-campos);
	
	vdist = radius*sin(glm::radians(pitch));
	hdist = radius*cos(glm::radians(pitch));
	Xoffset = hdist*cos(glm::radians(yaw));
	Zoffset = hdist*sin(glm::radians(yaw));
	vec3 CylinCamPos = glm::normalize(vec3(radius*cos(glm::radians(yaw)), 0, radius* sin(glm::radians(yaw))));
	rightvec = glm::normalize(glm::cross(camup,CylinCamPos ));
	
}
void CameraNode::VRender(Scene *pScene) 
{
	UpdateOffsetsVectors();
	
	glm::vec3 NewCampos;
	NewCampos.y = vdist + Target.y;	//TODO add parameter for vertical distance offset

	NewCampos.x = Target.x + Xoffset;
	NewCampos.z = Target.z + Zoffset;
	campos.x = NewCampos.x;
	campos.y = NewCampos.y;//Transform::Lerp(campos.y, NewCampos.y, .30);//TODO Create variable for camera y offset
	campos.z = NewCampos.z;
	
	View = glm::lookAt(campos, Target, camup);//*Transform::translate(0, -5, 0);
	
}
void CameraNode::VOnUpdate(Scene *pScene, unsigned long const elapsedMs)
{
	if(m_pTarget)
	Target = m_pTarget->getPosition();
}
void CameraNode::ExtractPlanesGL(bool normalize)
{
	
	Plane* p_planes;
	p_planes = m_Frustum.m_Planes;

	/*const GLfloat *ToWorldMatrix = (const GLfloat*)glm::value_ptr(Projection * View);*/
	mat4 ToWorldMatrix = Projection*View;
	// Left clipping plane
	m_Frustum.m_Planes[Frustum::Side::Left].a = ToWorldMatrix[3][0] + ToWorldMatrix[0][0];
	m_Frustum.m_Planes[Frustum::Side::Left].b = ToWorldMatrix[3][1] + ToWorldMatrix[0][1];
	m_Frustum.m_Planes[Frustum::Side::Left].c = ToWorldMatrix[3][2] + ToWorldMatrix[0][2];
	m_Frustum.m_Planes[Frustum::Side::Left].d = ToWorldMatrix[3][3] + ToWorldMatrix[0][3];
	// Right clipping plane
	m_Frustum.m_Planes[Frustum::Side::Right].a = ToWorldMatrix[3][0] - ToWorldMatrix[0][0];
	m_Frustum.m_Planes[Frustum::Side::Right].b = ToWorldMatrix[3][1]  - ToWorldMatrix[0][1];
	m_Frustum.m_Planes[Frustum::Side::Right].c = ToWorldMatrix[3][2] - ToWorldMatrix[0][2];
	m_Frustum.m_Planes[Frustum::Side::Right].d = ToWorldMatrix[3][3] - ToWorldMatrix[0][3];
	// Top clipping plane
	m_Frustum.m_Planes[Frustum::Side::Top].a = ToWorldMatrix[3][0] - ToWorldMatrix[1][0];
	m_Frustum.m_Planes[Frustum::Side::Top].b = ToWorldMatrix[3][1] - ToWorldMatrix[1][1];
	m_Frustum.m_Planes[Frustum::Side::Top].c = ToWorldMatrix[3][2] - ToWorldMatrix[1][2];
	m_Frustum.m_Planes[Frustum::Side::Top].d = ToWorldMatrix[3][3] - ToWorldMatrix[1][3];
	// Bottom clipping plane
	m_Frustum.m_Planes[Frustum::Side::Bottom].a = ToWorldMatrix[3][0] + ToWorldMatrix[1][0];
	m_Frustum.m_Planes[Frustum::Side::Bottom].b = ToWorldMatrix[3][1] + ToWorldMatrix[1][1];
	m_Frustum.m_Planes[Frustum::Side::Bottom].c = ToWorldMatrix[3][2] + ToWorldMatrix[1][2];
	m_Frustum.m_Planes[Frustum::Side::Bottom].d = ToWorldMatrix[3][3] + ToWorldMatrix[1][3];
	// Near clipping plane
	m_Frustum.m_Planes[Frustum::Side::Near].a = ToWorldMatrix[3][0] + ToWorldMatrix[2][0];
	m_Frustum.m_Planes[Frustum::Side::Near].b = ToWorldMatrix[3][1] + ToWorldMatrix[2][1];
	m_Frustum.m_Planes[Frustum::Side::Near].c = ToWorldMatrix[3][2] + ToWorldMatrix[2][2];
	m_Frustum.m_Planes[Frustum::Side::Near].d = ToWorldMatrix[3][3] + ToWorldMatrix[2][3];
	// Far clipping plane
	m_Frustum.m_Planes[Frustum::Side::Far].a = ToWorldMatrix[3][0] - ToWorldMatrix[2][0];
	m_Frustum.m_Planes[Frustum::Side::Far].b = ToWorldMatrix[3][1] - ToWorldMatrix[2][1];
	m_Frustum.m_Planes[Frustum::Side::Far].c = ToWorldMatrix[3][2] - ToWorldMatrix[2][2];
	m_Frustum.m_Planes[Frustum::Side::Far].d = ToWorldMatrix[3][3] - ToWorldMatrix[2][3];
	// Normalize the plane equations, if requested
	if (normalize == true)
	{
		m_Frustum.m_Planes[Frustum::Side::Left].Normalize();
		m_Frustum.m_Planes[Frustum::Side::Right].Normalize();
		m_Frustum.m_Planes[Frustum::Side::Top].Normalize();
		m_Frustum.m_Planes[Frustum::Side::Bottom].Normalize();
		m_Frustum.m_Planes[Frustum::Side::Near].Normalize();
		m_Frustum.m_Planes[Frustum::Side::Far].Normalize();
	}
}
bool CubemapNode::VPreRender(Scene * pScene)
{
	NodeShader->Use();

	glm::mat4 CubeView = glm::mat4(glm::mat3(pScene->GetCamera()->GetView()));// remove translations
	glm::mat4 CubeProjection = pScene->GetCamera()->GetProjection();
	glUniformMatrix4fv(ProjectionMatrixID, 1, GL_FALSE, &CubeProjection[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &CubeView[0][0]);

	return true;
}

void CubemapNode::VRender(Scene * pScene)
{
	for (int i = 0;i < m_Meshes.size();++i)
		m_Meshes[i].DrawMesh(MeshType::SKYBOX);
	
}

void CubemapNode::VPostRender(Scene * pScene)
{

}

void OGLMeshNode::VRender(Scene * pScene)
{
	NodeShader->Use();
	for (int i = 0;i < m_Meshes.size();i++)
	{
		m_Meshes[i].DrawMesh(MeshType::NO_TEXTURE);
	}

}

bool OGLMeshNode::VPreRender(Scene * pScene)
{
	NodeShader->Use();
	ViewMat = pScene->GetCamera()->GetView();
	ProjectionMat = pScene->GetCamera()->GetProjection();
	vec3 campos = pScene->GetCamera()->GetCameraPosition();
		
	SetSpherePosition(vec3(ProjectionMat*ViewMat*ModelMatrix[3]));
	
	vec3 lpos = vec3(0,5, -5);
		
	glUniform3fv(LC, 1, &lightColor[0]);
	glUniform3f(lightPosLoc, lpos.x, lpos.y, lpos.z);
	glUniform3f(viewPosLoc, campos.x, campos.y, campos.z);
	glUniformMatrix4fv(ProjectionMatrixID, 1, GL_FALSE, &ProjectionMat[0][0]);
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMat[0][0]);
		
	return true;
}

void OGLMeshNode::VOnUpdate(Scene *pScene, unsigned long const elapsedMs)
{	
}
bool OGLMeshNode::VIsVisible(Scene * pScene) const
{
	Frustum* pCurrentFrustum = pScene->GetCamera()->GetFrustum();
	
	if (pCurrentFrustum)
	{
		if (pCurrentFrustum->Inside(GetBVSphere()))
		{
			//std::cout << ".\n";
			return true;
			
		}
	}
	//std::cout << "NotVisible\n";
	return false;

}

