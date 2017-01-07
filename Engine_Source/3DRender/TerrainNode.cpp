#include "Engine.h"
#include "..//3DRender//SceneNode.h"
void TerrainNode::VOnUpdate(Scene *, unsigned long const elapsedMs)
{

}
bool TerrainNode::VPreRender(Scene *pScene)
{
	NodeShader->Use();
	ViewMat = pScene->GetCamera()->GetView();
	ProjectionMat = pScene->GetCamera()->GetProjection();
	glUniform1f(DispLevelID, DispLevel);
	glUniform3fv(lightPosLoc,1, &lightPos[0]);
	glUniformMatrix4fv(ProjectionMatrixID, 1, GL_FALSE, &ProjectionMat[0][0]);
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMat[0][0]);

	return true;
}

void TerrainNode::VRender(Scene *pScene)
{
	for (int i = 0;i < m_Meshes.size();i++)
	{
		m_Meshes[i].DrawMesh( MeshType::TERRAIN);
	}

}

void TerrainNode::VPostRender(Scene *pScene)
{

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

	ModelMatrix = Transform::scale(Scale, 1.0, Scale);
	ModelMatrix = ModelMatrix * Transform::translate(0, -20, 0);
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