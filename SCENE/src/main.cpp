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

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "Model.h"
#include "Camara.h"
#include "Object.h"
#include "material.h"
#include "Lights.h"

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

//CUBE 1:
glm::vec3 cube1Pos = glm::vec3(0, 0, 0);
glm::vec3 cube1Scale = glm::vec3(1, 1, 1); 
glm::vec3 cube1Rotation = glm::vec3(0, 0, 0);
glm::vec3 cube2Pos = glm::vec3(0, 0, 2);
glm::vec3 cube2Scale = glm::vec3(0.1f, 0.1f, 0.1f);
glm::vec3 cube2Rotation = glm::vec3(0, 0, 0);
float cube1OffsetX = 0.0f; float cube1OffsetY = 0.0f; float cube1OffsetZ = 0.0f;

glm::vec3 sceneLightColor = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cubeColor = glm::vec3(0.5, 0.7, 0.6);
vec3 lightDirection = vec3(1.0f, 0.0f, 0.0f);
vec3 focalDir = vec3(1.0f, 0.0f, 0.0f);
float phiInner = cos(radians(13.0f));
float phiOuter = cos(radians(17.0f));

bool rotatingCubeBool = false;

int modelToDisplay = 1;
#define SPIDER 0
#define BOX 1
#define CONCAVE 2
#define WUSON 3

static void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

int main() {
	//initGLFW
//TODO
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);

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

	//PATHS
	const GLchar* vertexPathA = "./src/SimpleVertexShader.vertexshader";
	const GLchar* vertexPathB = "./src/SimpleVertexShaderCubeB.vertexshader";
	const GLchar* fragmentPathA = "./src/SimpleFragmentShader.fragmentshader";
	const GLchar* fragmentPathB = "./src/SimpleFragmentShaderCubeB.fragmentshader";
	const GLchar* fragmentPathPuntual = "./src/SimpleFragmentShaderPuntual.fragmentshader";
	const GLchar* fragmentPathDir = "./src/SimpleFragmentShaderDirectional.fragmentshader";
	const GLchar* fragmentPathFocal = "./src/SimpleFragmentShaderFocal.fragmentshader";
	const GLchar* vertexPathPhong = "./src/VertexShaderPhongTexture.vs";
	const GLchar* fragmentPathPhong = "./src/FragmentShaderPhongTexture.fs";

	//GLuint programID = LoadShaders("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");
	Shader *myShader = new Shader(vertexPathA, fragmentPathA);
	Shader lightShader(vertexPathB, fragmentPathB);
	Shader *bigCubeShader = new Shader(vertexPathA, fragmentPathB);
	Shader P1Shader = Shader::Shader(vertexPathB, fragmentPathB);
	Shader P2Shader = Shader::Shader(vertexPathB, fragmentPathB);
	Shader S1Shader = Shader::Shader(vertexPathB, fragmentPathB);
	Shader S2Shader = Shader::Shader(vertexPathB, fragmentPathB);
	Shader *myShader1 = new Shader(vertexPathPhong, fragmentPathPhong);
	Shader *myShader2 = new Shader(vertexPathPhong, fragmentPathPhong);
	Shader *myShader3 = new Shader(vertexPathPhong, fragmentPathPhong);
	GLuint shaderVar = glGetUniformLocation(myShader->Program, "offset");
	// Definir el buffer de vertices
	
	// Definir el EBO
	GLuint IndexBufferObject[]{
		0,1,3,
		1,2,3 };

	//OLD VBO
	GLfloat VertexBufferObject2[] = {
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
	};

	//NEW VBO
	GLfloat VertexBufferObject[] = {
		//front
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		0.5f ,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		//back
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		//left	
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		//right
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		//down
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		//up
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f
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

	//http://devernay.free.fr/cours/opengl/materials.html

	//Directional
	vec3 dPosition = vec3(0, 1, 0);
	vec3 dDir = vec3(0, 1, 0);
	vec3 dAmbient = vec3(1, 1, 1);
	vec3 dDiffuse = vec3(1, 1, 1);
	vec3 dSpecular = vec3(1, 1, 1);
	Lights dLight(dPosition, dDir, dAmbient, dDiffuse, dSpecular, DIRECTIONAL, 0);
	dLight.SetAtt(1.00f, 0.05f, 0.05f);
	
	//Point
	vec3 p1Position = vec3(-4, 1, -3);
	vec3 p1Dir = vec3(0, 0, 0);
	vec3 p1Ambient = vec3(1, 1, 0);
	vec3 p1Diffuse = vec3(1, 1, 0);
	vec3 p1Specular = vec3(1, 1, 0);
	Lights p1Light(p1Position, p1Dir, p1Ambient, p1Diffuse, p1Specular, POINT, 0);
	p1Light.SetAtt(1.00f, 0.05f, 0.05f);

	vec3 p2Position = vec3(4, -1, -3);
	vec3 p2Dir = vec3(0, 0, 0);
	vec3 p2Ambient = vec3(0, 0, 1);
	vec3 p2Diffuse = vec3(0, 0, 1);
	vec3 p2Specular = vec3(0, 0, 1);
	Lights p2Light(p2Position, p2Dir, p2Ambient, p2Diffuse, p2Specular, POINT, 1);
	p2Light.SetAtt(1.00f, 0.01f, 0.01f);

	//Focal
	vec3 s1Position = vec3(-5, 0, 0);
	vec3 s1Dir = vec3(0, 1, 0);
	vec3 s1Ambient = vec3(1, 0, 0);
	vec3 s1Diffuse = vec3(1, 0, 0);
	vec3 s1Specular = vec3(1, 0, 0);
	Lights s1Light(s1Position, s1Dir, s1Ambient, s1Diffuse, s1Specular, SPOT, 0);
	s1Light.SetAtt(1.00, 0.05, 0.05);
	s1Light.SetAperture(20.0f, 30.0f);

	vec3 s2Position = vec3(4, 0, 0);
	vec3 s2Dir = vec3(0.5, 1.75, -2);
	vec3 s2Ambient = vec3(1, 1, 0);
	vec3 s2Diffuse = vec3(1, 1, 0);
	vec3 s2Specular = vec3(1, 1, 0);
	Lights s2Light(s2Position, s2Dir, s2Ambient, s2Diffuse, s2Specular, SPOT, 1);
	s2Light.SetAtt(1.00, 0.01, 0.01);
	s2Light.SetAperture(10.0f, 20.0f);

	vec3 lightScale = vec3(0.1, 0.1, 0.1);
	vec3 lightRotate = vec3(1, 1, 1);



	Object cubeA(cube1Scale, cube1Rotation, cube1Pos, Object::cube);
	Object cubeB(cube2Scale, cube2Rotation, cube2Pos, Object::cube);
	
	//directional cube
	Object dCube(lightScale, lightRotate, dPosition, Object::cube);
	//point cubes
	Object p1Cube(lightScale, lightRotate, p1Position, Object::cube);
	Object p2Cube(lightScale, lightRotate, p2Position, Object::cube);
	//spotlight cubes
	Object s1Cube(lightScale, lightRotate, s1Position, Object::cube);
	Object s2Cube(lightScale, lightRotate, s2Position, Object::cube);

	vec3 bigCubePos = vec3(1, 0, 1);
	vec3 bigCubeScale = vec3(15, 15, 15);
	vec3 bigCubeRot = vec3(1, 1, 1);
	Object bigCube(bigCubeScale, bigCubeRot, bigCubePos, Object::cube);

	Material material("./src/Materials/difuso.png", "./src/Materials/especular.png", 32);
	material.SetMaterial(myShader2);
	Material bigCubeMaterial("./src/Materials/difuso2.png", "./src/Materials/especular2.png", 32);
	bigCubeMaterial.SetMaterial(myShader3);

	//bucle de dibujado
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();
		
		

		camara.DoMovement(window);

		lightShader.Use();

		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		vec3 movementVector = glm::vec3(cube1Pos.x + cube1OffsetX, cube1OffsetY + cube1OffsetY, cube1Pos.z + cube1OffsetZ);
		vec3 rotationVector = glm::vec3(rotationX, rotationY, 0.0f);
		view = camara.LookAt();
		projection = glm::perspective(glm::radians(camara.GetFOV()), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		
		

		cubeB.Move(glm::vec3(cube2Pos.x, cube2Pos.y, cube2Pos.z));
		cubeB.Rotate(glm::vec3(0, 0, 0));
		model = cubeB.GetModelMatrix();

		GLint modelLocationB = glGetUniformLocation(lightShader.Program, "model");
		GLint viewLocationB = glGetUniformLocation(lightShader.Program, "view");
		GLint projectionLocationB = glGetUniformLocation(lightShader.Program, "projection");
		GLint lightColorLocation = glGetUniformLocation(lightShader.Program, "lightColor");

		glUniformMatrix4fv(projectionLocationB, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLocationB, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLocationB, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(lightColorLocation, sceneLightColor.x, sceneLightColor.y, sceneLightColor.z);
		//cubeB.Draw();
		
		//LIGHTS CUBES:
		//Point
		P1Shader.Use();
		mat4 p1model;
		p1model = p1Cube.GetModelMatrix();
		glUniform3f(glGetUniformLocation(P1Shader.Program, "lightColor"), p1Ambient.x, p1Ambient.y, p1Ambient.z);
		glUniformMatrix4fv(glGetUniformLocation(P1Shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(P1Shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(P1Shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(p1model));
		p1Cube.Draw();

		P2Shader.Use();
		mat4 p2model;
		p2model = p2Cube.GetModelMatrix();
		glUniform3f(glGetUniformLocation(P2Shader.Program, "lightColor"), p2Ambient.x, p2Ambient.y, p2Ambient.z);
		glUniformMatrix4fv(glGetUniformLocation(P2Shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(P2Shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(P2Shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(p2model));
		p2Cube.Draw();

		//SPOT
		S1Shader.Use();
		mat4 s1model;
		s1model = s1Cube.GetModelMatrix();
		glUniform3f(glGetUniformLocation(P2Shader.Program, "lightColor"), s1Ambient.x, s1Ambient.y, s1Ambient.z);
		glUniformMatrix4fv(glGetUniformLocation(P2Shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(P2Shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(P2Shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(s1model));
		s1Cube.Draw();

		S2Shader.Use();
		mat4 s2model;
		s2model = s2Cube.GetModelMatrix();
		glUniform3f(glGetUniformLocation(P2Shader.Program, "lightColor"), s2Ambient.x, s2Ambient.y, s2Ambient.z);
		glUniformMatrix4fv(glGetUniformLocation(P2Shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(P2Shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(P2Shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(s2model));
		s2Cube.Draw();

		myShader1->Use();
		bigCubeMaterial.SetShininess(myShader1);
		bigCubeMaterial.ActivateTextures();

		dLight.SetLight(myShader1, posCamera);
		p1Light.SetLight(myShader1, posCamera);
		p2Light.SetLight(myShader1, posCamera);
		s1Light.SetLight(myShader1, posCamera);
		s2Light.SetLight(myShader1, posCamera);

		GLint modelLoc1 = glGetUniformLocation(myShader1->Program, "model");
		GLint viewLoc1 = glGetUniformLocation(myShader1->Program, "view");
		GLint projectionLoc1 = glGetUniformLocation(myShader1->Program, "projection");

		glUniformMatrix4fv(viewLoc1, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc1, 1, GL_FALSE, glm::value_ptr(projection));

		mat4 model1;
		model1 = bigCube.GetModelMatrix();
		glUniformMatrix4fv(modelLoc1, 1, GL_FALSE, glm::value_ptr(model1));
		bigCube.Draw();


		myShader2->Use();

		dLight.SetLight(myShader2, posCamera);
		p1Light.SetLight(myShader2, posCamera);
		p2Light.SetLight(myShader2, posCamera);
		s1Light.SetLight(myShader2, posCamera);
		s2Light.SetLight(myShader2, posCamera);

		material.SetShininess(myShader2);
		material.ActivateTextures();

		GLint modelLoc2 = glGetUniformLocation(myShader2->Program, "model");
		GLint viewLoc2 = glGetUniformLocation(myShader2->Program, "view");
		GLint projectionLoc2 = glGetUniformLocation(myShader2->Program, "projection");

		glUniformMatrix4fv(viewLoc2, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc2, 1, GL_FALSE, glm::value_ptr(projection));

		mat4 model2;
		cubeA.Move(movementVector);
		cubeA.Rotate(rotationVector);
		
		if (rotatingCubeBool) {
			float rotatingCubeAngle = (float)glfwGetTime() * 100;
			cubeA.Rotate(glm::vec3(rotatingCubeAngle, rotatingCubeAngle, 0));
		}
		
		model2 = cubeA.GetModelMatrix();
		glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model2));
		cubeA.Draw();

		//OLD BRICK CUBE
		//myShader2->Use();
		//
		//dLight.SetLight(myShader2, posCamera);
		//p1Light.SetLight(myShader2, posCamera);
		//p2Light.SetLight(myShader2, posCamera);
		//s1Light.SetLight(myShader2, posCamera);
		//s2Light.SetLight(myShader2, posCamera);

		////material.ActivateTextures();
		//material.SetShininess(myShader2);
		//material.ActivateTextures();

		//GLint modelLocation = glGetUniformLocation(myShader2->Program, "model");
		//GLint viewLocation = glGetUniformLocation(myShader2->Program, "view");
		//GLint projectionLocation = glGetUniformLocation(myShader2->Program, "projection");

		//glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
		//glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		//GLint lightColorLocationA = glGetUniformLocation(myShader->Program, "lightColor");
		//glUniform3f(lightColorLocationA, sceneLightColor.x, sceneLightColor.y, sceneLightColor.z);
		//GLint lightPositionLocation = glGetUniformLocation(myShader->Program, "lightPosition");
		//glUniform3f(lightPositionLocation, cube2Pos.x, cube2Pos.y, cube2Pos.z);
		//GLint cubeColorLocation = glGetUniformLocation(myShader->Program, "cubeColor");
		//glUniform3f(cubeColorLocation, cubeColor.x, cubeColor.y, cubeColor.z);
		//vec3 camaraPosition = camara.GetCamPosition();
		//GLint cameraPositionLocation = glGetUniformLocation(myShader->Program, "cameraPosition");
		//glUniform3f(cameraPositionLocation, camaraPosition.x, camaraPosition.y, camaraPosition.z);
		//
		////Directional Light
		//GLint lightDirectionLocation = glGetUniformLocation(myShader->Program, "lightDirection");
		//glUniform3f(lightDirectionLocation, lightDirection.x, lightDirection.y, lightDirection.z);

		////Focal Light
		////GLint focalDirectionLocation = glGetUniformLocation(myShader.Program, "focalDir");
		///*glUniform3f(focalDirectionLocation, focalDir.x, focalDir.y, focalDir.z);
		//GLint phiInnerLocation = glGetUniformLocation(myShader.Program, "phiInner");
		//glUniform1f(phiInnerLocation, phiInner);
		//GLint phiOuterLocation = glGetUniformLocation(myShader.Program, "phiOuter");
		//glUniform1f(phiOuterLocation, phiOuter);*/


		//cubeA.Move(movementVector);
		//cubeA.Rotate(rotationVector);
		//model = cubeA.GetModelMatrix();
		//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
		//cubeA.Draw();

		myShader3->Use();
		bigCubeMaterial.SetShininess(myShader3);
		bigCubeMaterial.ActivateTextures();

		dLight.SetLight(myShader3, posCamera);
		p1Light.SetLight(myShader3, posCamera);
		p2Light.SetLight(myShader3, posCamera);
		s1Light.SetLight(myShader3, posCamera);
		s2Light.SetLight(myShader3, posCamera);

		GLint modelLocation = glGetUniformLocation(bigCubeShader->Program, "model");
		GLint viewLocation = glGetUniformLocation(bigCubeShader->Program, "view");
		GLint projectionLocation = glGetUniformLocation(bigCubeShader->Program, "projection");

		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

		model1 = bigCube.GetModelMatrix();
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model1));
		bigCube.Draw();
		

		//intercambia el framebuffer
		glfwSwapBuffers(window);
	}
	

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
	if (key == GLFW_KEY_KP_8 && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		cube1OffsetY += 0.1f;
	}
	if (key == GLFW_KEY_KP_2 && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		cube1OffsetY -= 0.1f;
	}
	if (key == GLFW_KEY_KP_6 && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		cube1OffsetX += 0.1f;
	}
	if (key == GLFW_KEY_KP_4 && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		cube1OffsetX -= 0.1f;
	}
	if (key == GLFW_KEY_KP_7 && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		cube1OffsetZ -= 0.1f;
	}
	if (key == GLFW_KEY_KP_9 && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		cube1OffsetZ += 0.1f;
	}
	if (key == GLFW_KEY_KP_1 && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		rotatingCubeBool = !rotatingCubeBool;
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
	
}

void mouse_callback(GLFWwindow* window, double posX, double posY) {
	camara.MouseMove(window, posX, posY);
	
	
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camara.MouseScroll(window, xoffset, yoffset);

}

