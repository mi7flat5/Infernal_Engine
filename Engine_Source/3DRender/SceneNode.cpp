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

void SceneNode::VSetTransform(const mat4 * toWorld, const mat4 * fromWorld)
{
	m_Props.m_ToWorld = *toWorld;
	if(!fromWorld)
	m_Props.m_FromWorld = glm::inverse(*toWorld);
}
void SceneNode::SetVectorTransform(const vec3& position,const vec3& rotation,const vec3& scale)
{
	m_Props.m_Wpos = position;
	m_Props.m_WrotPYR = rotation;
	m_Props.m_Wscale = scale;

	float maxScale = scale.x;

	if (scale.y > scale.x)
		maxScale = scale.y;
	if (scale.z > scale.x && scale.z > scale.y)
		maxScale = scale.z;
	
		
	m_Props.RadiusScale = maxScale;
	m_Props.m_BVsphere.radius = m_Props.ModelRadius*m_Props.RadiusScale;
	EDITOR_LOG("radius: " + ToStr(m_Props.m_BVsphere.radius))

}
void SceneNode::GetVectorTransform(vec3& position, vec3& rotation, vec3& scale) 
{
	position = m_Props.m_Wpos;
	rotation = m_Props.m_WrotPYR;
	scale = m_Props.m_Wscale;
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

	//g_pApp->GetGameLogic()->VGetActor(m_Props.m_Id);
	/*if (pActor)
	{
		shared_ptr<TransformComponent> pTc = MakeStrongPtr(pActor->GetComponent<TransformComponent>(TransformComponent::g_Name));
		if (pTc)
		{
			m_Props.m_ToWorld = pTc->GetTransform();
		}
	}*/
	
	pScene->PushAndSetMatrix(m_Props.m_ToWorld);
	


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
	pScene->PopMatrix();
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
		
			EDITOR_LOG("Remaining shared pointers: "+ToStr((*i).use_count()-1))
			
				
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





