#pragma once
#include <GL\glew.h>
#include<glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
using namespace glm;
using namespace std;
#include "Shader.h"
#include <string>

class Object {

public:
	enum FigureType {
		cube = 0,
	};

	//SCALE, ROTATION, POSITION, TYPE
	Object(vec3 scale, vec3 rotation, vec3 position, FigureType typef);
	~Object();

	void Draw(glm::mat4 view, glm::mat4 projection);
	void Move(vec3 translation);
	void Rotate(vec3 rota);
	void Scale(vec3 scal);
	void Delete();
	mat4 GetModelMatrix();
	vec3 GetPosition();
	Shader cubeShader;

private:
	GLuint VBO, VAO, EBO;
	vec3 position;
	vec3 scale;
	vec3 rotation;
	std::string vertexShaderDir = "";
	glm::mat4 modelMatrix;
	
	FigureType typef;
	
};
