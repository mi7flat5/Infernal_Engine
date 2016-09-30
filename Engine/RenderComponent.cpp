#include"Engine.h"
#include "RenderComponent.h"
#include"Event.h"
#include"LoadUtility.h"
#include"Mesh.h"
#include"Shaders.hpp"

const char* MeshRenderComponent::g_Name = "MeshRenderComponent";
const char* CubeMapRenderComponent::g_Name = "CubeMapRenderComponent";



bool BaseRenderComponent::VInit(tinyxml2::XMLElement * pData)
{
	
	return false;
}

void BaseRenderComponent::VPostInit(void)
{
	std::shared_ptr<SceneNode> pSceneNode(VGetSceneNode());
	std::shared_ptr<EvtData_New_Render_Component> pEvent(INFERNAL_NEW EvtData_New_Render_Component(m_pOwner->GetId(), pSceneNode));
	std::cout << "\n add component to scene triggering . . ." << '\n';
	IEventManager::Get()->VTriggerEvent(pEvent);
}

void BaseRenderComponent::VOnChanged(void)
{
}

tinyxml2::XMLElement * BaseRenderComponent::VGenerateXml(void)
{
	return nullptr;
}

std::shared_ptr<SceneNode> BaseRenderComponent::VGetSceneNode(void)
{
	
	if (!m_pSceneNode)
		m_pSceneNode = VCreateSceneNode();
	return m_pSceneNode;
	
}



std::shared_ptr<SceneNode> MeshRenderComponent::VGetSceneNode(void)
{
	if (!m_pSceneNode)
		m_pSceneNode = VCreateSceneNode();
	return m_pSceneNode;
	
}

MeshRenderComponent::MeshRenderComponent(void)
{

	
}

std::shared_ptr<SceneNode> MeshRenderComponent::VCreateSceneNode(void)
{
	WeakBaseRenderComponentPtr weak(this);

	std::shared_ptr<OGLnode> mesh;
	mesh = std::shared_ptr<OGLnode>(INFERNAL_NEW OGLnode(m_pOwner->GetId(), weak, RenderPass_Actor));

	return mesh;
}

void MeshRenderComponent::VCreateInheritedXmlElements(tinyxml2::XMLElement * pBaseElement)
{
}



CubeMapRenderComponent::CubeMapRenderComponent(void)
{
	
}

bool CubeMapRenderComponent::VDelegateInit(tinyxml2::XMLElement * pData)
{
	return false;
}

bool CubeMapRenderComponent::VDelegateInit()
{
	return false;
}

std::shared_ptr<SceneNode> CubeMapRenderComponent::VCreateSceneNode(void)
{
	WeakBaseRenderComponentPtr weak(this);
	
	std::shared_ptr<CubemapNode> sky;
	sky = std::shared_ptr<CubemapNode>(INFERNAL_NEW CubemapNode(m_pOwner->GetId(), weak, RenderPass_Sky));
	
	return sky;
}



void CubeMapRenderComponent::VCreateInheritedXmlElements(tinyxml2::XMLElement * pBaseElement)
{
}
