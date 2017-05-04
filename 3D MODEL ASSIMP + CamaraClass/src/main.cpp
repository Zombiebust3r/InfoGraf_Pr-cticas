//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
#include <cmath>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include "Shader.h"
#include <SOIL.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Model.h"
#include "Camara.h"
#include "Object.h"


using namespace std;
using namespace glm;

const GLint WIDTH = 800, HEIGHT = 600;
GLfloat lastPosX = WIDTH/2;
GLfloat lastPosY = HEIGHT/2;
GLfloat myYaw = -90.0f;	//I put "myYaw" and "myPitch" as name because with "yaw" and "pitch it said it was ambiguous.
GLfloat myPitch = 0.0f;
GLfloat fov = 60.0f;
bool firstMouse = true;

bool WIDEFRAME = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double posX, double posY);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//void DrawVAO(GLuint VAO);
GLfloat mixValue = 0.6f;
float rotationX = 0.0f;
float rotationY = 0.0f;
glm::vec3 posCamera = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 frontCam = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 targetCamera = glm::vec3(0.0f, 0.0f, 0.0f);
GLfloat radio = 8.0f;
GLfloat deltaTime = 0.0f;
GLfloat previousFrame = 0.0f;

glm::mat4 LookAt(glm::vec3 target, glm::vec3 pos, glm::vec3 up);
void DoMovement(GLFWwindow* window);
#define SENSITIVITY 0.05f
Camara camara(posCamera, glm::normalize(posCamera - targetCamera), SENSITIVITY, 60.0f);  //POS, DIRECTION, SENSITIVITY, FOV
//Object *cube1 = new Object(glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), Object::cube);

int modelToDisplay = 1;
#define SPIDER 0
#define BOX 1
#define CONCAVE 2
#define WUSON 3

int main() {
	//initGLFW
//TODO
	GLFWwindow* window;

	if (!glfwInit()) exit(EXIT_FAILURE);

	//set GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//create a window
//TODO
	window = glfwCreateWindow(WIDTH, HEIGHT, "Practica VAO.", nullptr, nullptr);
	if (!window) {
		cout << "Error al crear ventana." << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//set GLEW and inicializate
//TODO
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		cout << "Error al iniciar glew." << endl;
		glfwTerminate();
		return NULL;
	}
	//set function when callback
//TODO
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);

	//GLuint programID = LoadShaders("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");
	Shader myShader("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");
	GLuint shaderVar = glGetUniformLocation(myShader.Program, "offset");
	// Definir el buffer de vertices
	
	// Definir el EBO
	GLuint IndexBufferObject[]{
		0,1,3,
		1,2,3 };

	//OLD VBO
	GLfloat VertexBufferObject[] = {
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
	};

	//NEW VBO
	GLfloat VertexBufferCube[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f , -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f , -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f , -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f , -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f , -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	vec3 CubesPositionBuffer[] = {
		vec3(0.0f ,  0.0f,  0.0f),
		vec3(2.0f ,  5.0f, -15.0f),
		vec3(-1.5f, -2.2f, -2.5f),
		vec3(-3.8f, -2.0f, -12.3f),
		vec3(2.4f , -0.4f, -3.5f),
		vec3(-1.7f,  3.0f, -7.5f),
		vec3(1.3f , -2.0f, -2.5f),
		vec3(1.5f ,  2.0f, -2.5f),
		vec3(1.5f ,  0.2f, -1.5f),
		vec3(-1.3f,  1.0f, -1.5f)
	};

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferCube), VertexBufferCube, GL_STATIC_DRAW);
	//Pre 5.1 EJERCICIO 2: --> glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferObject), VertexBufferObject, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CubesPositionBuffer), CubesPositionBuffer, GL_STATIC_DRAW);
	//Pre 5.1 EJERCICIO 2: --> glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexBufferObject), IndexBufferObject, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);


	// EJERCICIO 1
	/*GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
										   // Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load image, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);*/



	// EJERCICIO 2
	GLuint texture1;
	GLuint texture2;

	// -------------------------------------------------------------------------------------------------------------------------------------
	// Texture 1
	// -------------------------------------------------------------------------------------------------------------------------------------
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("./src/texture.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	
									 
	// -------------------------------------------------------------------------------------------------------------------------------------
	// Texture 2
	// -------------------------------------------------------------------------------------------------------------------------------------
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("./src/sloth.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// EJERCICIO 3
	vec3 vector(3);
	mat2 matriz;

	//===============================================================================================================================================
	//===============================================================================================================================================
																	//CAMERA CONTROL
	//glm::vec3 cameraDirection = glm::normalize(posCamera - targetCamera);	//Directional Vector: Inverted
	//glm::vec3 tempUp = glm::vec3(0.0f, 1.0f, 0.0f);									//Temporal Up vector to make a cross product with cameraDirection.
	//glm::vec3 cameraRight = glm::normalize(glm::cross(tempUp, cameraDirection));	//Right vector from our camera: perpendicular to cameraDirection and tempUp.
	//glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);					//True Up vector to complete the new coordinate system.

	//===============================================================================================================================================
	//===============================================================================================================================================
																		//MODEL

	Model myModel("./src/Objects/spider.obj");
	Model boxModel("./src/Objects/Box.obj");
	Model concaveModel("./src/Objects/concave_polygon.obj");
	Model wusonModel("./src/Objects/WusonOBJ.obj");


	//===============================================================================================================================================
	//===============================================================================================================================================


	//bucle de dibujado
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();

		/*GLfloat actualFrame = glfwGetTime();
		deltaTime = actualFrame - previousFrame;
		previousFrame = actualFrame;*/
		//DoMovement(window);
		camara.DoMovement(window);

//TEXTURES

		//========================================================================================================================
		//															TEXTURES
		
		//EJERCICIO 1
		//glBindTexture(GL_TEXTURE_2D, texture);


		myShader.Use();

		////EJERCICIO 2
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(myShader.Program, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(myShader.Program, "ourTexture2"), 1);
		glUniform1f(glGetUniformLocation(myShader.Program, "mixValue"), mixValue);

//3D

		//=========================================================================================================================
		//															   3D
		
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(-50.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		GLfloat X = sin(glfwGetTime()) * radio;
		GLfloat Z = cos(glfwGetTime()) * radio;
		//view = glm::lookAt(posCamera, posCamera + frontCam, up);   //view = glm::lookAt(glm::vec3(camaraX, 0.0f, camaraZ), targetCamera, up);	//Movement - Rotation
		//view = glm::lookAt(glm::vec3(X, 0.0f, Z), targetCamera, up);
		//glm::mat4 tempMat = LookAt(targetCamera, glm::vec3(X, 0.0f, Z), up);
		view = camara.LookAt();
		//view = tempMat;

		projection = glm::perspective(glm::radians(camara.GetFOV()), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

		//cube1->Draw(view, projection);

		GLint modelLocation = glGetUniformLocation(myShader.Program, "model");
		GLint viewLocation = glGetUniformLocation(myShader.Program, "view");
		GLint projectionLocation = glGetUniformLocation(myShader.Program, "projection");
		
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));


		////DO TRANSFORMATION TO THE CUBE:
		glBindVertexArray(VAO);
		for (GLuint i = 0; i < 10; i++) {
			glm::mat4 model;
			model = glm::translate(model, CubesPositionBuffer[i]);
			GLfloat angle = 10.0f * i;

			model = glm::rotate(model, glm::radians(angle), glm::vec3(0.7f, 1.0f, 0.5f));
			model = glm::rotate(model, glm::radians(rotationX), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
			//model = glm::rotate(model, glm::radians((GLfloat)glfwGetTime()*100), glm::vec3(1.0f, 1.0f, 0.0f));		//Rotación constante
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		//=========================================================================================================================

		
		glBindVertexArray(0);
		
		//3DMODEL DRAWING
		/*
		myModel.Draw(myShader, GL_STATIC_DRAW);//MODEL DRAWING --> SPIDER
		switch (modelToDisplay)
		{
		case BOX:
			boxModel.Draw(myShader, GL_STATIC_DRAW);//MODEL DRAWING
			break;
		case CONCAVE:
			concaveModel.Draw(myShader, GL_STATIC_DRAW);//MODEL DRAWING
			break;
		case WUSON:
			wusonModel.Draw(myShader, GL_STATIC_DRAW);//MODEL DRAWING
			break;
		default:
			break;
		}*/ 
		

		

		//double mouseXPos, mouseYPos;
		//glfwGetCursorPos(window, &mouseXPos, &mouseYPos);
		//camara.MouseMove(window, mouseXPos, mouseYPos);

		//intercambia el framebuffer
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}


glm::mat4 LookAt(glm::vec3 target, glm::vec3 pos, glm::vec3 up) {
	glm::vec3 tempDirectionVector = glm::normalize(pos - target);			//Directional Vector: Inverted
	glm::vec3 tempRightVector = glm::normalize(glm::cross(up, tempDirectionVector));	//Right vector from our camera: perpendicular to cameraDirection and tempUp.
	glm::vec3 tempUpVector = glm::cross(tempDirectionVector, tempRightVector);					//True Up vector to complete the new coordinate system.

	glm::mat4 lookAtMatrix = glm::mat4(glm::vec4(tempRightVector, 0), glm::vec4(tempUpVector, 0), glm::vec4(tempDirectionVector, 0), glm::vec4(0, 0, 0, 1));
	glm::mat4 temp = glm::mat4(glm::vec4(1, 0, 0, -pos.x), glm::vec4(0, 1, 0, -pos.y), glm::vec4(0, 0, 1, -pos.z), glm::vec4(0, 0, 0, 1));
	lookAtMatrix = lookAtMatrix * temp;
	return lookAtMatrix;
}

void DoMovement(GLFWwindow* window) {
	// Camera controls
	GLfloat cameraSpeed = 5.0f * deltaTime;
	int state = 0;
	if ((state = glfwGetKey(window, GLFW_KEY_W)) == GLFW_PRESS) {
		posCamera += cameraSpeed * frontCam;
	}
	if ((state = glfwGetKey(window, GLFW_KEY_A)) == GLFW_PRESS) {
		posCamera -= glm::normalize(glm::cross(frontCam, up)) * cameraSpeed;
	}
	if ((state = glfwGetKey(window, GLFW_KEY_S)) == GLFW_PRESS) {
		posCamera -= cameraSpeed * frontCam;
	}
	if ((state = glfwGetKey(window, GLFW_KEY_D)) == GLFW_PRESS) {
		posCamera += glm::normalize(glm::cross(frontCam, up)) * cameraSpeed;
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (!WIDEFRAME && key == GLFW_KEY_W && action == GLFW_PRESS)
		WIDEFRAME = true;
	//WIDEFRAME = !WIDEFRAME;
	else if (WIDEFRAME && key == GLFW_KEY_W && action == GLFW_PRESS)
		WIDEFRAME = false;

	//EJERCICIO 2
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		/*mixValue += 0.1f;
		if (mixValue >= 1.0f)
			mixValue = 1.0f;*/
		//mixValue = 0;
		modelToDisplay = BOX;
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		/*mixValue -= 0.1f;
		if (mixValue <= 0.0f)
			mixValue = 0.0f;*/
		//mixValue = 1;
		modelToDisplay = CONCAVE;
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		modelToDisplay = WUSON;

	}
	if (key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		rotationX -= 0.5f;
	}
	if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		rotationX += 0.5f;
	}
	if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		rotationY += 0.5f;
	}
	if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		rotationY -= 0.5f;
	}
	//GLfloat cameraSpeed = 5.0f * deltaTime;
	//if (key == GLFW_KEY_W) {
	//	posCamera += cameraSpeed * frontCam;
	//}
	//if (key == GLFW_KEY_S) {
	//	posCamera -= cameraSpeed * frontCam;
	//}
	//if (key == GLFW_KEY_A) {
	//	posCamera -= glm::normalize(glm::cross(frontCam, up)) * cameraSpeed;
	//}
	//if (key == GLFW_KEY_D) {
	//	posCamera += glm::normalize(glm::cross(frontCam, up)) * cameraSpeed;
	//}

	//TYPE = GL_FILL;
}

void mouse_callback(GLFWwindow* window, double posX, double posY) {
	camara.MouseMove(window, posX, posY);
	
	//if (firstMouse)
	//{
	//	lastPosX = posX;
	//	lastPosY = posY;
	//	firstMouse = false;
	//}
	//
	//GLfloat xOffset = posX - lastPosX;
	//GLfloat yOffset = lastPosY - posY; //Reversed cuz' y axis goes from the bottom to the top.
	//lastPosX = posX;
	//lastPosY = posY;
	//GLfloat sensitivity = 0.05f;
	//xOffset *= sensitivity;
	//yOffset *= sensitivity;
	//myYaw += xOffset;
	//myPitch += yOffset;

	////Constraints: (No constraint on the yaw since it would limit how much can the user turn the view left or right.
	//if (myPitch > 89.0f) {
	//	myPitch = 89.0f;	//Prevents going reverse.
	//}
	//if (myPitch < -89.0f) {
	//	myPitch = -89.0f;	//Prevents going reverse.
	//}

	//glm::vec3 front;
	//front.x = cos(glm::radians(myYaw)) * cos(glm::radians(myPitch));
	//front.y = sin(glm::radians(myPitch));
	//front.z = sin(glm::radians(myYaw)) * cos(glm::radians(myPitch));
	//frontCam = glm::normalize(front);
	
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	cout << "callback: " << xoffset << endl;
	camara.MouseScroll(window, xoffset, yoffset);
	//fov = camara.GetFOV();
	/*if (fov >= 1.0f && fov <= 45.0f) {
		fov -= yoffset;
	}
	if (fov <= 1.0f) {
		fov = 1.0f;
	}
	if (fov >= 45.0f) {
		fov = 45.0f;
	}*/

}

//void DrawVAO(GLuint VAO, Shader myShader, GLuint texture) {
////	glBindVertexArray(VAO);
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//	/*if (WIDEFRAME)
//		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //GL_LINE -->lineas
//	else
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//*/
//	glBindTexture(GL_TEXTURE_2D, texture);
//	myShader.Use();
//	glBindVertexArray(VAO);
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//	glBindVertexArray(0);
//
//}
