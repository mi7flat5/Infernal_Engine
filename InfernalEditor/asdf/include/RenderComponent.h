#pragma once
#include"RenderComponentInterface.h"
#include"SceneNode.h"
#include"ObjectComponent.h"


class BaseRenderComponent:public RenderComponentInterface
{

	
	virtual std::shared_ptr<SceneNode> VGetSceneNode(void) override;
protected:
	virtual bool VDelegateInit(tinyxml2::XMLElement* pData) { return true; }
	std::shared_ptr<SceneNode> m_pSceneNode;
public:
	
	virtual bool VInit(tinyxml2::XMLElement* pData) override;
	virtual void VPostInit(void) override;
	virtual void VOnChanged(void) override;
	virtual tinyxml2::XMLElement* VGenerateXml(void) override;
	
	virtual std::shared_ptr<SceneNode> VCreateSceneNode(void) = 0;// factory method to create the appropriate scene node
	
};
class CubeMapRenderComponent : public BaseRenderComponent
{
	std::string m_textureResource;
public:
	CubeMapRenderComponent();
	static const char *g_Name;
	virtual const char *VGetName() const { return g_Name; }
	

	
	virtual std::shared_ptr<SceneNode> VCreateSceneNode(void) override;
protected:
	virtual bool VDelegateInit(tinyxml2::XMLElement* pData) override;
	//hard coded cubemap
	bool VDelegateInit();

	  // factory method to create the appropriate scene node

	// editor stuff
	virtual void VCreateInheritedXmlElements(tinyxml2::XMLElement* pBaseElement);
};


class MeshRenderComponent : public BaseRenderComponent
{
	virtual std::shared_ptr<SceneNode> VGetSceneNode(void) override;
public:
	MeshRenderComponent();
	static const char *g_Name;
	virtual const char *VGetName() const { return g_Name; }

	virtual std::shared_ptr<SceneNode> VCreateSceneNode(void) override;
protected:
	 // factory method to create the appropriate scene node
	virtual void VCreateInheritedXmlElements(tinyxml2::XMLElement* pBaseElement);
};


