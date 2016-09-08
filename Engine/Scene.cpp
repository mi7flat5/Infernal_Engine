#include"Engine.h"
#include "Scene.h"



Scene::Scene()
{
	m_Root.reset(INFERNAL_NEW RootNode());
}


Scene::~Scene()
{
}

void Scene::OnRender()
{
}

void Scene::OnRestore()
{
}

void Scene::OnLostDevice()
{
}

void Scene::OnUpdate(const int deltaMilliseconds)
{
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
		m_ActorMap[id] = kid;
	}

	return m_Root->VAddChild(kid); ;
}

bool Scene::RemoveChild(ObjectId id)
{
	return false;
}
