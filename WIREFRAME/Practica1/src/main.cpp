/*
	DANIEL BRUNA TRIVIÑO 2B
*/

//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include <shader.hpp>

using namespace std;
const GLint WIDTH = 600, HEIGHT = 800;
bool WIREFRAME = false;

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
		exit(EXIT_FAILURE);

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
	GLuint programID = LoadShaders("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");

	// Definir el VBO
	GLfloat VertexBufferObject[] = {

		-0.5f, 0.25f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.25f, 0.0f
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferObject), VertexBufferObject, GL_STATIC_DRAW); //falta

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexBufferObject), IndexBufferObject, GL_STATIC_DRAW);
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
		glUseProgram(programID);

		//pintar el VAO
		glBindVertexArray(vAO);

		//pintar con lineas
		if (WIREFRAME) {
			glClearColor(0., 0.8, 0., 1.0);

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawElements(GL_LINE_STRIP, 6, GL_UNSIGNED_INT, 0);
		}
		
		//pintar con triangulos
		else {
			glClearColor(0., 0.8, 0., 1.0);

			glActiveTexture(GL_TEXTURE0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
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
	exit(EXIT_SUCCESS);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//TODO, comprobar que la tecla pulsada es escape para cerrar la aplicación y la tecla w para cambiar a modo widwframe
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		WIREFRAME = !WIREFRAME;	//WIREFRAME inverts its value.
	}
		
}
