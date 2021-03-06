#pragma once
typedef std::map<ObjectId, StrongObjectPtr> ObjectMap;

#include"..//Engine_Source/3DRender/SceneNode.h"
class ObjectFactory;
class CameraNode;

class BaseGameLogic : public IGameLogic
{
	friend class InferanlKernel;						// This is only to gain access to the view list
	
protected:
	float m_Lifetime;								//indicates how long this game has been in session
						// our RNG
	ObjectMap m_objects;
	ObjectId m_LastActorId;
	BaseGameState m_State;							// game state: loading, running, etc.


	std::shared_ptr<Scene> m_pScene;
	std::shared_ptr<CameraNode> m_pCamera;
	ObjectFactory* m_pObjectFactory;

public:

	BaseGameLogic();
	virtual ~BaseGameLogic();
	bool Init(void);


	ObjectId GetNewActorID(void)
	{
		return ++m_LastActorId;
	}

	virtual StrongObjectPtr VCreateActor(const std::string &actorResource,  const ObjectId serversActorId = INVALID_OBJECT_ID); 
	virtual void VDestroyActor(const ObjectId actorId);
	virtual WeakObjectPtr VGetActor(const ObjectId actorId);
	virtual void VModifyActor(const ObjectId actorId, tinyxml2::XMLElement *overrides);

	virtual void VMoveActor(const ObjectId id, mat4 const &mat) {}

	// editor functions
	std::string GetActorXml(const ObjectId id);

	// Level management

	virtual bool VLoadGame(const char* levelResource) override; 


	// Logic Update
	virtual void VOnUpdate(float time, float elapsedTime);

	// Changing Game Logic State
	virtual void VChangeState(BaseGameState newState);
	const BaseGameState GetState() const { return m_State; }

	// Render Diagnostics

	// event delegates
	void RequestDestroyActorDelegate(IEventDataPtr pEventData);

	std::shared_ptr<Scene> GetScene() const{ return m_pScene; }
	std::shared_ptr<CameraNode> GetCamera()const { return m_pCamera; }

protected:
	virtual ObjectFactory* VCreateActorFactory(void);

	virtual bool VLoadGameDelegate(tinyxml2::XMLElement* pLevelData) { return true; }

	void MoveActorDelegate(IEventDataPtr pEventData);
	void RequestNewActorDelegate(IEventDataPtr pEventData);
};
