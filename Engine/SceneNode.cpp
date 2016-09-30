#include"Engine.h"
#include "SceneNode.h"
#include"Scene.h"

//CameraNode::

SceneNode::SceneNode() {}

SceneNode::SceneNode(ObjectId ObjectId, WeakBaseRenderComponentPtr renderComponent, RenderPass renderPass)
{
	std::cout << "\nSceneNode created";
	m_Props.m_RenderPass = renderPass;
}
void SceneNode::SetMeshList(std::vector<Mesh> inMesh) 
{
	m_Meshes = inMesh;
}


SceneNode::~SceneNode()
{
}

void SceneNode::VSetTransform(const mat4 * toWorld, const mat4 * fromWorld)
{
}

void SceneNode::VOnRestore(Scene * pScene)
{
}

void SceneNode::VOnUpdate(Scene *, unsigned long const elapsedMs)
{
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

	std::cout << " \n root created \n";

}

bool RootNode::VAddChild(std::shared_ptr<ISceneNode> kid)
{
	
	RenderPass pass = kid->VGet()->RenderPass();
	std::cout << "pass num is: " << pass;
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
	return false;
}



void CameraNode::UpdateOffsetsVectors()
{
	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89)
		pitch = -89;

	theta = 90 - yaw;
	phi = 90 - pitch;

	front.x = radius * sin(glm::radians(phi))*cos(glm::radians(theta));
	//if (campos.y > TerrainHeight)
	front.y = radius * cos(glm::radians(pitch + 90)) + 10; //TODO add parameter for adjusting y facing offset
	front.z = radius * sin(glm::radians(phi))*sin(glm::radians(theta));
	camfront = glm::normalize(front);

	vdist = radius*sin(glm::radians(pitch));
	hdist = radius*cos(glm::radians(pitch));
	Xoffset = hdist*sin(glm::radians(yaw));
	Zoffset = hdist*cos(glm::radians(yaw));

	Right = glm::normalize(glm::cross(camup, camfront));
}
void CameraNode::VRender(Scene *pScene) 
{
	UpdateOffsetsVectors();
	
	glm::vec3 NewCampos;
	NewCampos.y = vdist + Target.y;	//TODO add parameter for vertical distance offset

	NewCampos.x = Target.x - Xoffset;
	NewCampos.z = Target.z - Zoffset;
	campos.x = NewCampos.x;
	campos.y = Transform::Lerp(campos.y, NewCampos.y, .30);
	campos.z = NewCampos.z;
	View = glm::lookAt(campos, campos + camfront, camup);

}
void CameraNode::VOnUpdate(Scene *, unsigned long const elapsedMs)
{
	

}

bool CubemapNode::VPreRender(Scene * pScene)
{
	NodeShader->Use();

	glm::mat4 CubeView = glm::mat4(glm::mat3(pScene->GetCamera()->GetView()));// remove translations
	glm::mat4 CubeProjection = pScene->GetCamera()->GetProjection();
	glUniformMatrix4fv(ProjectionMatrixID, 1, GL_FALSE, &CubeProjection[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &CubeView[0][0]);
	glBindVertexArray(m_Meshes[0].VAO);
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Meshes[0].textures[0].id);
	return true;
}

void CubemapNode::VRender(Scene * pScene)
{
	glDrawElements(GL_TRIANGLES, m_Meshes[0].indices.size(), GL_UNSIGNED_INT, 0);
}

void CubemapNode::VPostRender(Scene * pScene)
{
	glBindTexture(GL_TEXTURE_3D, 0);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glBindVertexArray(0);
}
