#include "Engine.h"
#include "SceneNode.h"
#include"SHObject/TransformComponent.h"
#include"SHObject/RenderComponent.h"

OGLMeshNode::OGLMeshNode(const ObjectId Id,
	WeakBaseRenderComponentPtr renderComponent,
	RenderPass renderPass, const char* shaderV, const char* shaderF, const char* meshPath)
	: SceneNode(Id, renderComponent, renderPass)
{
	
	m_Props.m_Name = "OGLMeshNode";
	NodeShader.reset(new Shaders(shaderV, shaderF));
	LoadUtility::loadModel(m_Meshes, meshPath, MeshType::TEXTURE_2D);
	for (GLuint i = 0; i < m_Meshes.size();i++)
		m_Meshes[i].SetShader(NodeShader->getProgram());
	
	lightColor = glm::vec3(1, 1, 1);
	ProjectionMatrixID = glGetUniformLocation(NodeShader->getProgram(), "Projection");
	ViewMatrixID = glGetUniformLocation(NodeShader->getProgram(), "View");
	ModelMatrixID = glGetUniformLocation(NodeShader->getProgram(), "Model");
	lightPosLoc = glGetUniformLocation(NodeShader->getProgram(), "lightPos");
	viewPosLoc = glGetUniformLocation(NodeShader->getProgram(), "viewPos");
	PickingShader.reset(INFERNAL_NEW Shaders("..//shaders//PickingVert.glsl", "..//shaders//PickingFrag.glsl"));
	PickingID = glGetUniformLocation(PickingShader->getProgram(), "whywontyouwork");

	
	
	std::vector<vec3> sphereCalc;
	LoadUtility::LoadCollider(meshPath, sphereCalc, std::vector<GLuint>(), std::vector<vec3>());
	m_Props.m_BVsphere.SphereFromDistantPoints(sphereCalc);
	m_Props.ModelRadius = m_Props.m_BVsphere.radius;
	m_Props.ModelSpherePosition = m_Props.m_BVsphere.position;
	
}

void OGLMeshNode::VRender(Scene * pScene)
{
	if (!pScene->Picking()) {
		NodeShader->Use();

		vec3 campos = pScene->GetCamera()->GetCameraPosition();


		lightPos = vec3(0, 900, 900);
		glUniform3fv(LC, 1, &lightColor[0]);
		glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(viewPosLoc, campos.x, campos.y, campos.z);
		glUniformMatrix4fv(ProjectionMatrixID, 1, GL_FALSE, &ProjectionMat[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &pScene->GetTopMatrix()[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMat[0][0]);

		for (int i = 0;i < m_Meshes.size();i++)
		{
			m_Meshes[i].DrawMesh(MeshType::TEXTURE_2D);
		}

	}
	else {
		PickingShader->Use();
	
		glUniformMatrix4fv(ProjectionMatrixID, 1, GL_FALSE, &ProjectionMat[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &pScene->GetTopMatrix()[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMat[0][0]);
		
		glUniform3fv(PickingID, 1, &vec4(m_Props.m_Id / 255.0f)[0]);
		for (int i = 0;i < m_Meshes.size();i++)
		{
			m_Meshes[i].DrawMesh(MeshType::NO_TEXTURE);
		}

	}

	
}




bool OGLMeshNode::VIsVisible(Scene * pScene) const
{
	Frustum* pCurrentFrustum = pScene->GetCamera()->GetFrustum();


	if (pCurrentFrustum)
	{
		if (pCurrentFrustum->Inside(GetBVSphere()))
		{
			//std::cout << ".\n";
			return true;

		}
	}
	
	return false; //broken for the momment
}

