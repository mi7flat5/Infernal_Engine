#include"Engine.h"
#include"..\EventSystem\EventManager.h"
#include "Scene.h"
#include"..\EventSystem\Event.h"
#include"RayPick.hpp"


Scene::Scene()
{
	m_Root.reset(INFERNAL_NEW RootNode());
	IEventManager* pEventMgr = IEventManager::Get();
	m_MatrixStack.reset(INFERNAL_NEW std::stack<mat4>());
	m_MatrixStack->emplace(mat4(1.0f));
	pEventMgr->VAddListener(fastdelegate::MakeDelegate(this, &Scene::NewRenderComponentDelegate), EvtData_New_Render_Component::sk_EventType);
	pEventMgr->VAddListener(fastdelegate::MakeDelegate(this, &Scene::DestroyActorDelegate), EvtData_Destroy_Actor::sk_EventType);
	pEventMgr->VAddListener(fastdelegate::MakeDelegate(this, &Scene::TestRayCollisonDelegate), EvtData_RayCast::sk_EventType);
}


Scene::~Scene()
{
	IEventManager* pEventMgr = IEventManager::Get();
	m_MatrixStack->pop();
	m_MatrixStack.reset();
	pEventMgr->VRemoveListener(fastdelegate::MakeDelegate(this, &Scene::NewRenderComponentDelegate), EvtData_New_Render_Component::sk_EventType);
	pEventMgr->VRemoveListener(fastdelegate::MakeDelegate(this, &Scene::DestroyActorDelegate), EvtData_Destroy_Actor::sk_EventType);
	pEventMgr->VRemoveListener(fastdelegate::MakeDelegate(this, &Scene::TestRayCollisonDelegate), EvtData_RayCast::sk_EventType);
}

void Scene::OnRender()
{

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
void Scene::DestroyActorDelegate(IEventDataPtr pEventData)
{

	std::shared_ptr<EvtData_Destroy_Actor> pCastEventData = std::static_pointer_cast<EvtData_Destroy_Actor>(pEventData);
	RemoveChild(pCastEventData->GetId());
}
std::shared_ptr<ISceneNode> Scene::FindActor(ObjectId id)
{
	return m_ObjectMap[id];
}

bool Scene::AddChild(ObjectId id, std::shared_ptr<ISceneNode> kid)
{
	if (id != INVALID_OBJECT_ID)
	{	
		// This allows us to search for this later based on actor id
		m_ObjectMap[id] = kid;
		if (std::static_pointer_cast<SceneNode>(kid)->GetBVSphere().radius>0) {
			m_BVMap[id] = std::static_pointer_cast<SceneNode>(kid)->GetBVSphereRefernce();
		
		}
	}
	return m_Root->VAddChild(kid); ;
}

bool Scene::RemoveChild(ObjectId id)
{
	if (id == INVALID_OBJECT_ID)
	{
		
		return false;
	}
	
	m_ObjectMap.erase(id);
	m_BVMap.erase(id);
	return m_Root->VRemoveChild(id);
}
void Scene::NewRenderComponentDelegate(IEventDataPtr pEventData)
{
	std::shared_ptr<EvtData_New_Render_Component> pCastEventData = std::static_pointer_cast<EvtData_New_Render_Component>(pEventData);

	ObjectId actorId = pCastEventData->GetActorId();
	std::shared_ptr<SceneNode> pSceneNode(pCastEventData->GetSceneNode());

	// FUTURE WORK: Add better error handling here.		
	if (!pSceneNode)
	{
		std::string error = "Failed to restore scene node to the scene for actorid " + ToStr(actorId);//TODO
		EDITOR_LOG(error)
		return;
	}
	
	AddChild(actorId, pSceneNode);
	
}

void Scene::TestRayCollisonDelegate(IEventDataPtr pEventData)
{
	std::shared_ptr<EvtData_RayCast> pCastEventData = std::static_pointer_cast<EvtData_RayCast>(pEventData);
	RayPick ray(pCastEventData->x,pCastEventData->y,this,pCastEventData->Width,pCastEventData->Height);
	
	ObjectId hitId = INVALID_OBJECT_ID;
	float nx = -1 + (2.0f * pCastEventData->x) / pCastEventData->Width;
	float ny = 1.0f - (2.0f * pCastEventData->y) / pCastEventData->Height;
	glm::vec2 ClickPoint(nx, ny);
	float minDist = FLT_MAX;
	
	for (auto& i : m_BVMap) {	
	
		if (ray.RayTest(i.second))
		{
						
			glm::vec2 CollsionPos(i.second->position.x/ i.second->position.z , i.second->position.y / i.second->position.z) ;
			//sort out need for abs(), macro problem?
			if (abs((sqr((ClickPoint.x - CollsionPos.x)) + sqr((ClickPoint.y - CollsionPos.y)))) < minDist)
			{
				minDist = abs(sqr((ClickPoint.x-CollsionPos.x))+sqr((ClickPoint.y - CollsionPos.y)));
				hitId = i.first;
			}
		}
	}
	if (hitId != INVALID_OBJECT_ID) {
		std::shared_ptr<EvtData_EvtRayHit> pEvent(INFERNAL_NEW EvtData_EvtRayHit(hitId, m_ObjectMap[hitId]));
		IEventManager::Get()->VTriggerEvent(pEvent);
	}
}
