#pragma once
#include"..\3DRender\SceneNode.h"
#include"..\EventSystem\EventManager.h"
//class CameraNode;
//class SkyNode;

typedef std::map<ObjectId, std::shared_ptr<ISceneNode> > SceneObjectMap;
class Scene
{
	std::shared_ptr<SceneNode>  	m_Root;
	std::shared_ptr<CameraNode> 	m_Camera;
	std::shared_ptr<ISceneNode>  	m_ControlledObject;

	/*MatrixStack 		*m_MatrixStack;
	AlphaSceneNodes 		m_AlphaSceneNodes;*/
	SceneObjectMap 			m_ObjectMap;

public:
	Scene();
	~Scene();

	void OnRender();
	void OnRestore();
	void OnLostDevice();
	void OnUpdate(const int deltaMilliseconds);
	void DestroyActorDelegate(IEventDataPtr pEventData);
	std::shared_ptr<ISceneNode> FindActor(ObjectId id);
	bool AddChild(ObjectId id, std::shared_ptr<ISceneNode> kid);
	bool RemoveChild(ObjectId id);

	void NewRenderComponentDelegate(IEventDataPtr pEventData);
	void ModifiedRenderComponentDelegate(IEventDataPtr pEventData);


	void SetCamera(std::shared_ptr<CameraNode> camera) { m_Camera = camera; }
	void SetControlledObject(ObjectId pawn) { m_ControlledObject = m_ObjectMap[pawn]; }
	const std::shared_ptr<CameraNode> GetCamera() const { return m_Camera; }

	

	//void NewRenderComponentDelegate(IEventDataPtr pEventData);
	//void ModifiedRenderComponentDelegate(IEventDataPtr pEventData);			// added post-press!
	//void DestroyActorDelegate(IEventDataPtr pEventData);
	//void MoveActorDelegate(IEventDataPtr pEventData);

};

