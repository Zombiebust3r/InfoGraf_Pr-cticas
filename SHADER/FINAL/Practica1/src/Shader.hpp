#pragma once
//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include "Shader.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

class Shader
{
public:
	GLuint Program;
	Shader();
	~Shader();
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void USE();
};

