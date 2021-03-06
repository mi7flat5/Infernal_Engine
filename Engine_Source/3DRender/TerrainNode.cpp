#include "Engine.h"
#include "SceneNode.h"


TerrainNode::TerrainNode(const ObjectId Id, WeakBaseRenderComponentPtr renderComponent, RenderPass renderPass)
	: SceneNode(Id, renderComponent, renderPass)
{


	LoadUtility::loadModel(m_Meshes, "..//assets//ParisTerrain.fbx", MeshType::TERRAIN);
	HeightMapImage = LoadUtility::loadHeightMap("..//media//hm_d.jpg", Width, Height);
	NodeShader.reset(INFERNAL_NEW Shaders("..//shaders//dispmap.vs.glsl",
		"..//shaders//dispmap.tcs.glsl",
		"..//shaders//dispmap.tes.glsl",
		"..//shaders//dispmap.fs.glsl"));

	ProjectionMatrixID = glGetUniformLocation(NodeShader->getProgram(), "Projection");
	ViewMatrixID = glGetUniformLocation(NodeShader->getProgram(), "View");
	ModelMatrixID = glGetUniformLocation(NodeShader->getProgram(), "Model");
	lightPosLoc = glGetUniformLocation(NodeShader->getProgram(), "light");
	viewPosLoc = glGetUniformLocation(NodeShader->getProgram(), "viewPos");

	

	for (GLuint i = 0; i < m_Meshes.size();i++)
		m_Meshes[i].SetShader(NodeShader->getProgram());
	lightPos = vec3(0,900,0);
	SetRadius(0);
	SetScale(50);
	m_Props.m_Name = "TerrainNode";
	m_Props.m_BVsphere.radius = 0;
}

void TerrainNode::VOnUpdate(Scene *, unsigned long const elapsedMs)
{

}


void TerrainNode::VRender(Scene *pScene)
{
	if (!pScene->Picking()) {
		NodeShader->Use();

		glUniform1f(DispLevelID, DispLevel);
		glUniform3fv(lightPosLoc, 1, &lightPos[0]);
		glUniform3fv(viewPosLoc, 1, &pScene->GetCamera()->GetCameraPosition()[0]);


		ViewMat = pScene->GetCamera()->GetView();
		ProjectionMat = pScene->GetCamera()->GetProjection();
		glUniformMatrix4fv(ProjectionMatrixID, 1, GL_FALSE, &ProjectionMat[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &pScene->GetTopMatrix()[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMat[0][0]);

		for (int i = 0;i < m_Meshes.size();i++)
		{
			m_Meshes[i].DrawMesh(MeshType::TERRAIN);
		}
	}
	
}


TerrainNode::~TerrainNode() {

	if (HeightMapImage)
		SOIL_free_image_data(HeightMapImage);
	EDITOR_LOG("HeightMap Data Freed")
}
void TerrainNode::SetMinMaxBoundry()
{
	MaxZ = (32 * Scale * (64 + Height)) / Height;
	MaxX = (32 * Scale * (64 + Width)) / Width;

	MinX = -MaxX;
	MinZ = -MaxZ;

	MaxX = MaxX - Scale;
	MaxZ = MaxZ - Scale;
}
void TerrainNode::SetScale(GLuint InScale) {
	Scale = InScale;

	m_Props.m_ToWorld = Transform::scale(Scale, 1.0, Scale)*Transform::translate(0,-20,0);
	//m_Props.m_ToWorld = m_Props.m_ToWorld;;
	SetMinMaxBoundry();
}
GLuint TerrainNode::GetHeight(glm::vec3 Position)
{
	GLuint XLow = floor(Position.x * (Width / 2) / (32 * Scale) + 32 + (Width / 2));
	GLuint ZLow = floor(Position.z * (Height / 2) / (32 * Scale) + 32 + (Height / 2));

	if (XLow < 1 || ZLow < 1)
		return LastValidHeight;
	//GLuint wraps at 0
	if ((XLow > Width - 2) || (ZLow > Height - 2))
		return LastValidHeight;

	LastValidHeight = (GLuint)HeightMapImage[((ZLow*Width) + XLow) * 3];
	return LastValidHeight;
}