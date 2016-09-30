#ifndef SHADERS_HPP
#define SHADERS_HPP
#include"include\GL\glew.h"
#include"include\GL\glut.h"



class Shaders
{
	GLuint Program;
public:
	Shaders(const GLchar* vertexPath, const GLchar* fragmentPath);
	Shaders(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* tessEvalPath, const GLchar* tessControlPath);
	void Use();
	GLuint getProgram();
};

#endif