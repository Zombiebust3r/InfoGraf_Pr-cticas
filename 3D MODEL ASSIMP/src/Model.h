#pragma once
#include "Mesh.h"
#include <SOIL.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>


class Model {
public:
	Model() {}
	~Model() {}
	Model(GLchar* path);
	void Draw(Shader shader, GLint drawMode);
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	GLint TextureFromFile(const char* path, string directory);

private:
	std::string directory;
	std::vector<Mesh> meshes;
};
