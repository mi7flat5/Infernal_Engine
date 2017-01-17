#pragma once


using vec3 = glm::vec3;
using vec4 = glm::vec4;
using mat3 = glm::mat3;
using mat4 = glm::mat4;
using ObjectId = unsigned int;
using ComponentId = unsigned int;

class ObjectComponent;
class Object3D;
typedef std::shared_ptr<ObjectComponent> StrongObjectComponentPtr;
typedef std::weak_ptr<ObjectComponent> WeakObjectComponentPtr;
typedef std::shared_ptr<Object3D> StrongObjectPtr;
typedef std::weak_ptr<Object3D> WeakObjectPtr;

const ObjectId INVALID_OBJECT_ID = 0;
const ComponentId INVALID_COMPONENT_ID = 0;


class SceneNodeProperties;
class Scene;
class SceneNode;


class IKeyboardHandler
{
public:
	virtual bool VOnKeyDown(const GLuint  c) = 0;
	virtual bool VOnKeyUp(const GLuint  c) = 0;
};



class IRenderState
{
public:
	virtual std::string VToString() = 0;
};

enum RenderPass
{
	RenderPass_0,
	RenderPass_Static = RenderPass_0,
	RenderPass_Sky,
	RenderPass_Actor,
	RenderPass_NotRendered,
	RenderPass_Last
};


class IRenderer
{
public:
	virtual void VSetBackgroundColor() = 0;
	virtual void VOnRestore() = 0;
	virtual void VShutdown() = 0;
	virtual bool VPreRender() = 0;
	virtual bool VPostRender() = 0;

	virtual void VSetWorldTransform(const mat4 *m) = 0;
	virtual void VSetViewTransform(const mat4 *m) = 0;
	virtual void VSetProjectionTransform(const mat4 *m) = 0;
	virtual std::shared_ptr<IRenderState> VPrepareAlphaPass() = 0;
	virtual std::shared_ptr<IRenderState> VPrepareSkyBoxPass() = 0;

};


class ISceneNode
{
public:
	virtual const SceneNodeProperties * const VGet() const = 0;

	virtual void VSetTransform( const mat4 *toWorld, const mat4 *fromWorld = NULL) = 0;

	virtual void VOnUpdate(Scene *pScene, unsigned long const elapsedMs) = 0;
	virtual void VOnRestore(Scene *pScene) = 0;

	virtual bool VPreRender(Scene *pScene) = 0;
	virtual bool VIsVisible(Scene *pScene) const = 0;
	virtual void VRender(Scene *pScene) = 0;
	virtual void VRenderChildren(Scene *pScene) = 0;
	virtual void VPostRender(Scene *pScene) = 0;

	virtual bool VAddChild(std::shared_ptr<ISceneNode> kid) = 0;
	virtual bool VRemoveChild(ObjectId id) = 0;
	virtual void VOnLostDevice(Scene *pScene) = 0;



	virtual ~ISceneNode() { };
};

 class IScreenElement
 {
 public:
	 virtual void VOnRestore() = 0;
	 virtual void LostDevice() = 0;
	 virtual void VOnRender(double fTime, float fElapsedTime) = 0;
	 virtual void VOnUpdate(int deltaMilliseconds) = 0;

	 virtual int VGetZOrder() const = 0;
	 virtual void VSetZOrder(int const zOrder) = 0;
	 virtual bool VIsVisible() const = 0;
	 virtual void VSetVisible(bool visible) = 0;

	

	 virtual ~IScreenElement() { };
	 virtual bool const operator <(IScreenElement const &other) { return VGetZOrder() < other.VGetZOrder(); }
 };

 //class IGamePhysics;
 class IGameLogic
 {
 public:
	 virtual WeakObjectPtr VGetActor(const ObjectId id) = 0;
	 virtual StrongObjectPtr VCreateActor(const std::string &actorResource, const ObjectId serversActorId = INVALID_OBJECT_ID) = 0;
	 virtual void VDestroyActor(const ObjectId actorId) = 0;
	 virtual bool VLoadGame(const char* levelResource) = 0;
	// virtual void VSetProxy() = 0;
	 virtual void VOnUpdate(float time, float elapsedTime) = 0;
	 virtual void VChangeState(enum BaseGameState newState) = 0;
	 virtual void VMoveActor(const ObjectId	 id, mat4 const &mat) = 0;
	// virtual shared_ptr<IGamePhysics> VGetGamePhysics(void) = 0;
 };