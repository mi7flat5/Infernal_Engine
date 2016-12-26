#include"Engine.h"
#include "RenderComponent.h"
#include"..\EventSystem\Event.h"
#include"..\Utility\LoadUtility.h"
#include"Mesh.h"
#include"..\Utility\Shaders.hpp"

const char* MeshRenderComponent::g_Name = "MeshRenderComponent";
const char* CubeMapRenderComponent::g_Name = "CubeMapRenderComponent";



bool BaseRenderComponent::VInit(tinyxml2::XMLElement * pData)
{
	tinyxml2::XMLElement* pPaths = pData->FirstChildElement();
	
	meshPath= pPaths->Attribute("mesh");
	shaderV = pPaths->Attribute("shaderV");
	shaderF = pPaths->Attribute("shaderF");
	if (!meshPath)
	{
		EDITOR_LOG("Failed to load render component paths")
			return false;
	}

	return true;
}

void BaseRenderComponent::VPostInit(void)
{
	std::shared_ptr<SceneNode> pSceneNode(VGetSceneNode());
	std::shared_ptr<EvtData_New_Render_Component> pEvent(INFERNAL_NEW EvtData_New_Render_Component(m_pOwner->GetId(), pSceneNode));
	
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

	std::shared_ptr<OGLMeshNode> mesh;
	mesh = std::shared_ptr<OGLMeshNode>(INFERNAL_NEW OGLMeshNode(m_pOwner->GetId(), weak, RenderPass_Actor, shaderV, shaderF, meshPath));

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
	
	sky = std::shared_ptr<CubemapNode>(INFERNAL_NEW CubemapNode(m_pOwner->GetId(), weak, RenderPass_Sky,shaderV,shaderF,meshPath));
	
	return sky;
}



void CubeMapRenderComponent::VCreateInheritedXmlElements(tinyxml2::XMLElement * pBaseElement)
{
}
