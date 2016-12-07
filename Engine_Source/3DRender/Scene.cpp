#include"Engine.h"
#include"..\EventSystem\EventManager.h"
#include "..\3DRender\Scene.h"
#include"..\EventSystem\Event.h"



Scene::Scene()
{
	m_Root.reset(INFERNAL_NEW RootNode());
	IEventManager* pEventMgr = IEventManager::Get();
	pEventMgr->VAddListener(fastdelegate::MakeDelegate(this, &Scene::NewRenderComponentDelegate), EvtData_New_Render_Component::sk_EventType);
}


Scene::~Scene()
{
	IEventManager* pEventMgr = IEventManager::Get();
	pEventMgr->VRemoveListener(fastdelegate::MakeDelegate(this, &Scene::NewRenderComponentDelegate), EvtData_New_Render_Component::sk_EventType);
}

void Scene::OnRender()
{
	/*if (m_Camera && m_ControlledObject)
		m_Camera->SetTarget(m_ControlledObject);*/
	if (m_Root->VPreRender(this))
	{
		m_Root->VRender(this);
		m_Root->VRenderChildren(this);
		m_Root->VPostRender(this);
	}
}

void Scene::OnRestore()
{
}

void Scene::OnLostDevice()
{
}

void Scene::OnUpdate(const int deltaMilliseconds)
{
	m_Root->VOnUpdate(this, deltaMilliseconds);
}

std::shared_ptr<ISceneNode> Scene::FindActor(ObjectId id)
{
	return std::shared_ptr<ISceneNode>();
}

bool Scene::AddChild(ObjectId id, std::shared_ptr<ISceneNode> kid)
{
	if (id != INVALID_OBJECT_ID)
	{
		// This allows us to search for this later based on actor id
		m_ObjectMap[id] = kid;
	}

	return m_Root->VAddChild(kid); ;
}

bool Scene::RemoveChild(ObjectId id)
{
	return false;
}
void Scene::NewRenderComponentDelegate(IEventDataPtr pEventData)
{
	std::shared_ptr<EvtData_New_Render_Component> pCastEventData = std::static_pointer_cast<EvtData_New_Render_Component>(pEventData);

	ObjectId actorId = pCastEventData->GetActorId();
	std::shared_ptr<SceneNode> pSceneNode(pCastEventData->GetSceneNode());

	// FUTURE WORK: Add better error handling here.		
	if (!pSceneNode)
	{
		std::string error = "Failed to restore scene node to the scene for actorid " + ToStr(actorId);
		
		return;
	}
	std::cout << "\n component added to scene" << "\n"<<" ObjectId is: "<<actorId;
	AddChild(actorId, pSceneNode);
	
}