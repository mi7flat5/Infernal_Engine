#ifndef SHADERS_HPP
#define SHADERS_HPP




class Shaders
{
	GLuint Program;
public:
	Shaders(const GLchar* vertexPath, const GLchar* fragmentPath);
	Shaders(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* tessEvalPath, const GLchar* tessControlPath);
	~Shaders() { glDeleteProgram(Program); }
	void Use();
	GLuint getProgram();

};

#endif