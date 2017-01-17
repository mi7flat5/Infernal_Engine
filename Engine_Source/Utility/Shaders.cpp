#include"Engine.h"
#include "Shaders.hpp"



	// Constructor generates the shader
Shaders::Shaders(const GLchar* vertexPath, const GLchar* fragmentPath)
	{
		// 1. Retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensures ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::badbit);
		try
		{
			// Open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// Read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// Convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;//TODO Add to logging
			EDITOR_LOG("SHADER::FILE_NOT_SUCCESFULLY_READ")
		}
		const GLchar* vShaderCode = vertexCode.c_str();
		const GLchar * fShaderCode = fragmentCode.c_str();
		// 2. Compile shaders
		GLuint vertex, fragment;
		GLint success;
		GLchar infoLog[512];
		// Vertex Shader
		
			vertex = glCreateShader(GL_VERTEX_SHADER);

		
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		// Print compile errors if any
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;//TODO Add to logging
			EDITOR_LOG("VERTEX::COMPILATION_FAILED" + (char)infoLog)
		}
		// Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		// Print compile errors if any
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;//TODO Add to logging
			EDITOR_LOG("FRAGMENT::COMPILATION_FAILED" + std::string(infoLog))
		}
		// Shader Program
		this->Program = glCreateProgram();
		glAttachShader(this->Program, vertex);
		glAttachShader(this->Program, fragment);
		glLinkProgram(this->Program);
		// Print linking errors if any
		glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;//TODO Add to logging
			EDITOR_LOG("PROGRAM::LINKING_FAILED" + (char)infoLog)
		}
		// Delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	
}
Shaders::Shaders(const GLchar * vertexPath, const GLchar * tessControlPath, const GLchar * tessEvalPath, const GLchar * fragmentPath)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string TCScode;
	std::string TEScode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream TCSfile;
	std::ifstream TESfile;
	// ensures ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	TCSfile.exceptions(std::ifstream::badbit);
	TESfile.exceptions(std::ifstream::badbit);
	try
	{
		// Open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		TCSfile.open(tessControlPath);
		TESfile.open(tessEvalPath);

		std::stringstream vShaderStream, fShaderStream, TCSstream, TESstream;
		// Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		TCSstream << TCSfile.rdbuf();
		TESstream << TESfile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		TCSfile.close();
		TESfile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		TCScode = TCSstream.str();
		TEScode = TESstream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;//TODO Add to logging
		EDITOR_LOG("FILE_NOT_SUCCESFULLY_READ")
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar * fShaderCode = fragmentCode.c_str();
	const GLchar * TCshaderCode = TCScode.c_str();
	const GLchar * TEshaderCode = TEScode.c_str();

	
	// 2. Compile shaders
	GLuint vertex, fragment, TCS, TES;
	GLint success;
	GLchar infoLog[512];
	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// Print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;//TODO Add to logging
		
		EDITOR_LOG("COMPILATION_FAILED" + std::string(infoLog))
	}
	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// Print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;//TODO Add to logging
		EDITOR_LOG("FRAGMENT" + std::string(infoLog))
	}
	//Tesselation control shader
	TCS = glCreateShader(GL_TESS_CONTROL_SHADER);
	glShaderSource(TCS, 1, &TCshaderCode, NULL);
	glCompileShader(TCS);
	// Print compile errors if any
	glGetShaderiv(TCS, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "TESSELEATION_CONTROL::COMPILATION_FAILED\n" << infoLog << std::endl;//TODO Add to logging
		EDITOR_LOG("TESSELEATION_CONTROL" + std::string(infoLog))
	}
	//Tesselation evaluation shader
	//Tesselation control shader
	TES = glCreateShader(GL_TESS_EVALUATION_SHADER);
	glShaderSource(TES, 1, &TEshaderCode, NULL);
	glCompileShader(TES);
	// Print compile errors if any
	glGetShaderiv(TES, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::TESSELEATION_EVALUATION::COMPILATION_FAILED\n" << infoLog << std::endl;//TODO Add to logging
		EDITOR_LOG("TESSELEATION_EVALUATION" + std::string(infoLog))
	}

	// Shader Program
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glAttachShader(this->Program, TCS);
	glAttachShader(this->Program, TES);
	glLinkProgram(this->Program);
	// Print linking errors if any
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;//TODO Add to logging

		EDITOR_LOG(std::string("LINKING_FAILED"+std::string(infoLog)))
	}
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glDeleteShader(TCS);
	glDeleteShader(TES);
}
// Uses the current shader
void Shaders::Use()
{
	glUseProgram(this->Program);
}
GLuint Shaders::getProgram() {return Program;}

