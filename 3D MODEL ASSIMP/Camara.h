#pragma once
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <GLFW\glfw3.h>
#include <gtc/type_ptr.hpp>
#include <cmath>
#include <iostream>

class Camara
{
public:
	Camara();
	Camara(glm::vec3 position, glm::vec3 direction, GLfloat p_sensitivity, GLfloat p_fov);
	~Camara();

	void DoMovement(GLFWwindow* window);
	void MouseMove(GLFWwindow* window, double xpos, double ypos);
	void MouseScroll(GLFWwindow* window, double xScroll, double yScroll);
	glm::mat4 LookAt();
	GLfloat GetFOV();

private:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraDirection;
	glm::vec3 cameraTarget;
	GLfloat deltaTime;
	GLfloat lastFrame;
	GLfloat lastMx;
	GLfloat lastMy;
	GLfloat sensitivity;
	GLboolean firstMouse;
	GLfloat pitch;
	GLfloat yaw;
	GLfloat fov;

};

Camara::Camara() {
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);;
	cameraUp = glm::vec3(0.0f, 0.0f, 0.0f);;
	deltaTime = 0.0f;
	lastFrame = 0.0f;
	lastMx = 0.0f;
	lastMy = 0.0f;
	sensitivity = 0.0f;
	firstMouse = true;
	pitch = 0.0f;
	yaw = 0.0f;
	fov = 0.0f;
}

Camara::~Camara()
{
}

Camara::Camara(glm::vec3 position, glm::vec3 direction, GLfloat p_sensitivity, GLfloat p_fov) : cameraPos(position), cameraDirection(direction),sensitivity(p_sensitivity), fov(p_fov) {
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);;
	cameraUp = glm::vec3(0.0f, 0.0f, 0.0f);;
	deltaTime = 0.0f;
	lastFrame = 0.0f;
	lastMx = 0.0f;
	lastMy = 0.0f;
	sensitivity = 0.0f;
	firstMouse = true;
	pitch = 0.0f;
	yaw = 0.0f;
	fov = 0.0f;
}



void Camara::MouseMove(GLFWwindow* window, double xpos, double ypos) {

}

glm::mat4 Camara::LookAt() {
	cameraDirection = glm::normalize(cameraPos - cameraTarget);			//Directional Vector: Inverted
	glm::vec3 tempRightVector = glm::normalize(glm::cross(cameraUp, cameraDirection));	//Right vector from our camera: perpendicular to cameraDirection and tempUp.
	glm::vec3 tempUpVector = glm::cross(cameraDirection, tempRightVector);					//True Up vector to complete the new coordinate system.

	glm::mat4 lookAtMatrix = glm::mat4(glm::vec4(tempRightVector, 0), glm::vec4(tempUpVector, 0), glm::vec4(cameraDirection, 0), glm::vec4(0, 0, 0, 1));
	glm::mat4 temp = glm::mat4(glm::vec4(1, 0, 0, -cameraPos.x), glm::vec4(0, 1, 0, -cameraPos.y), glm::vec4(0, 0, 1, -cameraPos.z), glm::vec4(0, 0, 0, 1));
	lookAtMatrix = lookAtMatrix * temp;
	return lookAtMatrix;
}