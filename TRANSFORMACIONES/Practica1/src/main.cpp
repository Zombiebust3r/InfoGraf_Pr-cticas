/*
	DANIEL BRUNA TRIVIÑO 2B
*/

//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include "Shader.hpp"
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <math.h>

using namespace std;
using namespace glm;
const GLint WIDTH = 600, HEIGHT = 800;
bool WIREFRAME = false;
const GLchar* vertexPath = "./src/SimpleVertexShader.vertexshader";
const GLchar* fragmentPath = "./src/SimpleFragmentShader.fragmentshader";

//TRANSFORMATIONS:
vec3 myVector;
mat4x4 finalTransformationMatrix = mat4(1.0f);
#define SCALE_VEC vec3(0.5, 0.5, 1)
#define ROTATION_VEC_X vec3(1, 0, 0)
#define ROTATION_VEC_Y vec3(0, 1, 0)
#define ROTATION_VEC_Z vec3(0, 0, 1)
#define MAX_ANGLE 360
#define TRANSLATION_VEC vec3(0.5, 0.5, 0)

float angleToRatate = 0.0f;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

int main() {
	
	//initGLFW
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);

	//comprobar que GLFW estaactivo
	if (!glfwInit())
		::exit(EXIT_FAILURE);

	//set GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//create a window
	window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 1A", nullptr, nullptr);
	if (!window) {
		cout << "Error al crear la ventana" << endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	//set GLEW and inicializate
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) {
		cout << "Error al iniciar glew" << endl;
		glfwTerminate();
		return NULL;
	}

	//set function when callback
	glfwSetKeyCallback(window, key_callback);

	//set windows and viewport
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);


	//cargamos los shader
	//GLuint programID = LoadShaders("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");
	Shader colorShader = Shader::Shader(vertexPath, fragmentPath);
	//float valorDelOffset = 0.0f;
	//float offsetMax = 0.5f;
	//bool incrementando = true;

	// Definir el VBO
	GLfloat VertexBufferObject[] = {
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f
	};

	// Definir el EBO
	GLuint IndexBufferObject[] = {
		0, 1, 2,
		3, 0, 2
	};



	// Crear los VBO, VAO y EBO
	GLuint vBO;
	GLuint eBO;
	GLuint vAO;

	//reservar memoria para el VAO, VBO y EBO
	glGenVertexArrays(1, &vAO);
	glGenBuffers(1, &vBO);
	glGenBuffers(1, &eBO);

	//Establecer el objeto
	glBindVertexArray(vAO);

	//Enlazar el buffer con openGL
	glBindBuffer(GL_ARRAY_BUFFER, vBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferObject), VertexBufferObject, GL_DYNAMIC_DRAW); //falta

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexBufferObject), IndexBufferObject, GL_DYNAMIC_DRAW);
	//Establecer las propiedades de los vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//falta
	glEnableVertexAttribArray(0);

	//liberar el buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//liberar el buffer de vertices
	glBindVertexArray(0);



	//bucle de dibujado
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glClear(GL_COLOR_BUFFER_BIT);

		//establecer el shader
		//glUseProgram(programID);
		colorShader.USE();
		glBindVertexArray(vAO);
		/*
		//pintar el VAO
		
		if (incrementando) {
			if (valorDelOffset < 0.5) {
				valorDelOffset += 0.005;
			}
			else if (valorDelOffset >= 0.5) {
				incrementando = false;
			}
		}
		else if (!incrementando) {
			if (valorDelOffset > 0) {
				valorDelOffset -= 0.005;
			}
			else if (valorDelOffset <= 0) {
				incrementando = true;
			}
		}
		float offsetProgress = valorDelOffset / offsetMax; //Valor entre 0 y 1 en función de donde estas en el offset. 0: offset = 0/ 0.5: offset = 0.25/ 1: offset = 0.5
		float porcenRojo = offsetProgress;	//Valor de rojo (entre 0 y 1 para darle color en RGB)
		float porcenVerde = 1 - offsetProgress;	//Valor de verde (entre 0 y 1 para darle color en RGB)
		GLint variableShader = glGetUniformLocation(colorShader.Program, "offset");
		glUniform1f(variableShader, valorDelOffset);
		variableShader = glGetUniformLocation(colorShader.Program, "porcentajeR");
		glUniform1f(variableShader, porcenRojo);
		variableShader = glGetUniformLocation(colorShader.Program, "porcentajeG");
		glUniform1f(variableShader, porcenVerde);

		*/
		

		//====================================================================================================================================================================================================
		//====================================================================================================================================================================================================
		//TRANSFORMATIONS

		//ROTATION
		//finalTransformationMatrix = scale(mat4(1.0f), SCALE_VEC);
		finalTransformationMatrix = translate(mat4(1.0f), TRANSLATION_VEC);
		cout << "TRANSLATE:" << endl;
		for (int i = 0; i<4; ++i) {
			for (int j = 0; j<4; ++j)
				printf("%f, ", finalTransformationMatrix[i][j]);
			printf("\n");
		}
		finalTransformationMatrix = scale(finalTransformationMatrix, SCALE_VEC);
		cout << "SCALE:" << endl;
		for (int i = 0; i<4; ++i) {
			for (int j = 0; j<4; ++j)
				printf("%f, ", finalTransformationMatrix[i][j]);
			printf("\n");
		}
		finalTransformationMatrix = rotate(finalTransformationMatrix, angleToRatate, ROTATION_VEC_Z);
		cout << "ROTATION:" << endl;
		for (int i = 0; i<4; ++i) {
			for (int j = 0; j<4; ++j)
				printf("%f, ", finalTransformationMatrix[i][j]);
			printf("\n");
		}
		//finalTransformationMatrix = translate(finalTransformationMatrix, TRANSLATION_VEC);

		
		//finalTransformationMatrix = translate(finalTransformationMatrix, TRANSLATION_VEC);
		//finalTransformationMatrix = scale(mat4(1.0f), SCALE_VEC);


		GLuint matrixID = glGetUniformLocation(colorShader.Program, "matrix");
		glUniformMatrix4fv(matrixID, 1, GL_FALSE, value_ptr(finalTransformationMatrix));
		//====================================================================================================================================================================================================
		//====================================================================================================================================================================================================



		//MODIFICAR VERTIX POS:
		//VertexBufferObject[1 * 3 + 0] -= 0.01f;
		//VertexBufferObject[2 * 3 + 0] += 0.01f;
		//glBindBuffer(GL_ARRAY_BUFFER, vBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferObject), VertexBufferObject, GL_DYNAMIC_DRAW); //falta
		
		glClearColor(0.2, 0.38, 0.68, 1.0);
		//glActiveTexture(GL_TEXTURE0);
		if (WIREFRAME) {
			//pintar con lineas
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		} else {
			//pintar con triangulos
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//Delink Buffer
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// liberar la memoria de los VAO, EBO y VBO
	glDeleteVertexArrays(1, &vAO);
	glDeleteBuffers(1, &vBO);
	glDeleteBuffers(1, &eBO);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	::exit(EXIT_SUCCESS);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//TODO, comprobar que la tecla pulsada es escape para cerrar la aplicación y la tecla w para cambiar a modo widwframe
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		WIREFRAME = !WIREFRAME;	//WIREFRAME inverts its value.
	}
	
	//ROTATION
	if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT)) {		//|| action == GLFW_PRESS) --> I don't put this cuz it looks like it starts then stops. It looks awefull :D
		angleToRatate = (angleToRatate - 0.02);
		angleToRatate = fmod(angleToRatate, MAX_ANGLE);
	}
	if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT)) {		//|| action == GLFW_PRESS) --> I don't put this cuz it looks like it starts then stops. It looks awefull :D
		angleToRatate = (angleToRatate + 0.02);
		angleToRatate = fmod(angleToRatate, MAX_ANGLE);
	}
}
