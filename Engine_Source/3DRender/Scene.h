#pragma once
#include"..\3DRender\SceneNode.h"
#include"..\EventSystem\EventManager.h"

//class CameraNode;
//class SkyNode;

typedef std::map<ObjectId, std::shared_ptr<ISceneNode> > SceneObjectMap;
typedef std::map<ObjectId, BVSphere*> CollisionVolumeMap;//BVsphere is only current bounding volume, this will be generalized later
class Scene
{
	std::shared_ptr<SceneNode>  	m_Root;
	std::shared_ptr<CameraNode> 	m_Camera;
	std::shared_ptr<ISceneNode>  	m_ControlledObject;
	std::unique_ptr<std::stack<mat4>> 		m_MatrixStack;

//	AlphaSceneNodes 		m_AlphaSceneNodes;*/
	SceneObjectMap 			m_ObjectMap;
	CollisionVolumeMap m_BVMap;

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

	void TestRayCollisonDelegate(IEventDataPtr pEventData);

	void SetCamera(std::shared_ptr<CameraNode> camera) { m_Camera = camera; }
	void SetControlledObject(ObjectId pawn) { m_ControlledObject = m_ObjectMap[pawn]; }
	const std::shared_ptr<CameraNode> GetCamera() const { return m_Camera; }

	void PushAndSetMatrix(const mat4 &toWorld)
	{
		// Note this code carefully!!!!! It is COMPLETELY different
		// from some DirectX 9 documentation out there....
		// Scene::PushAndSetMatrix - Chapter 16, page 541
		if (!m_MatrixStack->empty())
		{
			mat4 ConcatMat = toWorld*m_MatrixStack->top();
			m_MatrixStack->push(ConcatMat);
		}
		
	}

	void PopMatrix()
	{
		if (!m_MatrixStack->empty()) 
		{
			m_MatrixStack->pop();
		}
	}

	const mat4 GetTopMatrix()
	{
		if (!m_MatrixStack->empty())
		{
			return static_cast<const mat4>(m_MatrixStack->top());
		}
		else return mat4(1.0f);
	}
	

	//void NewRenderComponentDelegate(IEventDataPtr pEventData);
	//void ModifiedRenderComponentDelegate(IEventDataPtr pEventData);			// added post-press!
	//void DestroyActorDelegate(IEventDataPtr pEventData);
	//void MoveActorDelegate(IEventDataPtr pEventData);

};

