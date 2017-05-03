#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <GL\glew.h>
#include <gtc\matrix_transform.hpp>
#include <glm.hpp>
#include <assimp\types.h>
#include "Shader.h"

using namespace std;
using namespace glm;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	GLuint id;
	string type;
	aiString path;
};

class Mesh {
public:
	Mesh() {}
	~Mesh() {}
	Mesh(std::vector<Vertex> vert, std::vector<GLuint> ind, std::vector<Texture> text);
	void setupMesh();
	void Draw(Shader MeshShader, GLint DrawMode);
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

private:
	GLuint VBO, VAO, EBO;
};
