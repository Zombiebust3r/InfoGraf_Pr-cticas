#pragma once
#define GLEW_STATIC
#include <GL\glew.h>
#include <glm.hpp>
#include "Shader.h"
#include<glm.hpp>
#include <gtc\matrix_transform.hpp>

using namespace glm;

enum LType {
	DIRECTIONAL = 0,
	POINT = 1,
	SPOT = 2
};

class Lights {
public:

	Lights(vec3 pos, vec3 dir, vec3 ambient, vec3 diffuse, vec3 specular, LType lType, int number);
	~Lights();
	void SetAtt(float constant, float lineal, float quadratic);
	void SetLight(Shader *shad, vec3 CamPos);
	void Rotate(vec3 rotation);
	void SetDirection(vec3 dir);
	void SetAperture(float min, float max);
	void SetPosition(vec3 pos);
	vec3 GetColor();

private:
	vec3 lightDirection;
	vec3 lightPos;
	vec3 lightAmbient;
	vec3 lightDiffuse;
	vec3 lightSpecular;
	LType lightType;
	float minAperture;
	float maxAperture;
	float ce1, ce2, ce3;
	int lightNumber;
};

