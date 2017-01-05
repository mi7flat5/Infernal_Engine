#include"Engine.h"
#include "..//3DRender/GraphicsDebug.h"
#include "..//Utility/Shaders.hpp"

#include<iostream>

GraphicsDebug::GraphicsDebug(glm::vec3 &Point)
{
	ModelShader = new Shaders("shaders/dbgVert.glsl", "shaders/ColliderFrag.glsl");
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &Point, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
	

	ProjectionMatrixID = glGetUniformLocation(ModelShader->getProgram(), "Projection");
	ViewMatrixID = glGetUniformLocation(ModelShader->getProgram(), "View");
	ModelMatrixID = glGetUniformLocation(ModelShader->getProgram(), "M");
	dbgPoints.push_back(Point);
	PrimType = dbgType::POINT;
}
GraphicsDebug::GraphicsDebug(std::vector<glm::vec3> &Points,dbgType Type)
{
	ModelShader = new Shaders("..//shaders//dbgVert.glsl", "..//shaders/dbgFrag.glsl");
	if (!ModelShader)
		std::cout << "\nMissing shader";
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, Points.size()*sizeof(glm::vec3), &Points[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
	

	ProjectionMatrixID = glGetUniformLocation(ModelShader->getProgram(), "Projection");
	ViewMatrixID = glGetUniformLocation(ModelShader->getProgram(), "View");
	ModelMatrixID = glGetUniformLocation(ModelShader->getProgram(), "Model");
	PrimType = Type;
	dbgPoints = Points;
}
void GraphicsDebug::Draw(mat4& p,mat4& v,mat4& m) {
	glBindVertexArray(this->VAO);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		ModelShader->Use();
	glUniformMatrix4fv(ProjectionMatrixID, 1, GL_FALSE, &p[0][0]);
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &v[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &m[0][0]);

	glPointSize(4.0);
	glLineWidth(9.0);
	if (PrimType == dbgType::POINT)
		glDrawArrays(GL_POINTS, 0, dbgPoints.size());
	else glDrawArrays(GL_LINES, 0, dbgPoints.size());

	glDisable(GL_BLEND);
	glBindVertexArray(0);

}


GraphicsDebug::~GraphicsDebug()
{
}
