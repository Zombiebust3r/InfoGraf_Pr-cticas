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
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	deltaTime = 0.0f;
	lastFrame = 0.0f;
	lastMx = 400.0f;
	lastMy = 300.0f;
	sensitivity = 0.0f;
	firstMouse = true;
	pitch = 0.0f;
	yaw = -90.0f;
}

Camara::~Camara()
{
}

Camara::Camara(glm::vec3 position, glm::vec3 direction, GLfloat p_sensitivity, GLfloat p_fov) : cameraPos(position), cameraDirection(direction),sensitivity(p_sensitivity), fov(p_fov) {
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	deltaTime = 0.0f;
	lastFrame = 0.0f;
	lastMx = 400.0f;
	lastMy = 300.0f;
	sensitivity = 0.0f;
	firstMouse = true;
	pitch = 0.0f;
	yaw = -90.0f;
}



void Camara::MouseMove(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse)
	{
		lastMx = xpos;
		lastMy = ypos;
		firstMouse = false;
	}

	GLfloat xOffset = xpos - lastMx;
	GLfloat yOffset = lastMy - ypos; //Reversed cuz' y axis goes from the bottom to the top.
	lastMx = xpos;
	lastMy = ypos;
	GLfloat sensitivity = 0.05f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;
	yaw += xOffset;
	pitch += yOffset;

	//Constraints: (No constraint on the yaw since it would limit how much can the user turn the view left or right.
	if (pitch > 89.0f) {
		pitch = 89.0f;	//Prevents going reverse.
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;	//Prevents going reverse.
	}

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void Camara::MouseScroll(GLFWwindow* window, double xScroll, double yScroll) {
	cout << fov << endl;
	cout << xScroll << " <-- x : y --> " << yScroll << endl;
	if (fov >= 1.0f && fov <= 90.0f) {
		fov -= xScroll;
	}
	if (fov <= 1.0f) {
		fov = 1.0f;
	}
	if (fov >= 90.0f) {
		fov = 90.0f;
	}
}

void Camara::DoMovement(GLFWwindow* window) {
	GLfloat actualFrame = glfwGetTime();
	deltaTime = actualFrame - lastFrame;
	lastFrame = actualFrame;
	
	// Camera controls
	GLfloat cameraSpeed = 5.0f * deltaTime;
	int state = 0;
	if ((state = glfwGetKey(window, GLFW_KEY_W)) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront;
	}
	if ((state = glfwGetKey(window, GLFW_KEY_A)) == GLFW_PRESS) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if ((state = glfwGetKey(window, GLFW_KEY_S)) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
	}
	if ((state = glfwGetKey(window, GLFW_KEY_D)) == GLFW_PRESS) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
}

glm::mat4 Camara::LookAt() {
	cameraDirection = glm::normalize(cameraPos - cameraTarget);			//Directional Vector: Inverted
	glm::vec3 tempRightVector = glm::normalize(glm::cross(cameraUp, cameraDirection));	//Right vector from our camera: perpendicular to cameraDirection and tempUp.
	glm::vec3 tempUpVector = glm::cross(cameraDirection, tempRightVector);					//True Up vector to complete the new coordinate system.

	glm::mat4 lookAtMatrix = glm::mat4(glm::vec4(tempRightVector, 0), glm::vec4(tempUpVector, 0), glm::vec4(cameraDirection, 0), glm::vec4(0, 0, 0, 1));
	glm::mat4 temp = glm::mat4(glm::vec4(1, 0, 0, -cameraPos.x), glm::vec4(0, 1, 0, -cameraPos.y), glm::vec4(0, 0, 1, -cameraPos.z), glm::vec4(0, 0, 0, 1));
	lookAtMatrix = lookAtMatrix * temp;
	lookAtMatrix = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	/*
	In this bit of code we calculate the look at matrix manually instead of using the glm version.
	We use all the data calculated by the class camara and returns the matrix as a mat4 so it can be used in the modification of the view matrix every frame.
	*/
	
	return lookAtMatrix;
	
}

GLfloat Camara::GetFOV() {
	return fov;
}