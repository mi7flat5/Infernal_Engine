#pragma once
#include"SceneNode.h"
#include"EventManager.h"
//class CameraNode;
//class SkyNode;

typedef std::map<ObjectId, std::shared_ptr<ISceneNode> > SceneActorMap;
class Scene
{
	std::shared_ptr<SceneNode>  	m_Root;
	std::shared_ptr<CameraNode> 	m_Camera;
	

	/*MatrixStack 		*m_MatrixStack;
	AlphaSceneNodes 		m_AlphaSceneNodes;*/
	SceneActorMap 			m_ActorMap;

public:
	Scene();
	~Scene();

	void OnRender();
	void OnRestore();
	void OnLostDevice();
	void OnUpdate(const int deltaMilliseconds);
	std::shared_ptr<ISceneNode> FindActor(ObjectId id);
	bool AddChild(ObjectId id, std::shared_ptr<ISceneNode> kid);
	bool RemoveChild(ObjectId id);

	void NewRenderComponentDelegate(IEventDataPtr pEventData);
	void ModifiedRenderComponentDelegate(IEventDataPtr pEventData);


	void SetCamera(std::shared_ptr<CameraNode> camera) { m_Camera = camera; }

	const std::shared_ptr<CameraNode> GetCamera() const { return m_Camera; }

	

	//void NewRenderComponentDelegate(IEventDataPtr pEventData);
	//void ModifiedRenderComponentDelegate(IEventDataPtr pEventData);			// added post-press!
	//void DestroyActorDelegate(IEventDataPtr pEventData);
	//void MoveActorDelegate(IEventDataPtr pEventData);

};

