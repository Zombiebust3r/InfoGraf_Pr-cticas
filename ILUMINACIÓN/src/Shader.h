#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

class Shader
{
public:
	GLuint Program;
	Shader() {}
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();
	void Use();
};

