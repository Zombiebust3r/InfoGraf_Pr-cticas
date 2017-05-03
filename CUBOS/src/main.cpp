//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include "..\Shader.h"
#include <SOIL.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


using namespace std;
using namespace glm;

const GLint WIDTH = 800, HEIGHT = 600;
bool WIDEFRAME = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//void DrawVAO(GLuint VAO);
GLfloat mixValue = 0.6f;
float rotationX = 0.0f;
float rotationY = 0.0f;


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


	

	//bucle de dibujado
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.3f, 1.0f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//========================================================================================================================
		//															TEXTURES
		
		//EJERCICIO 1
		//glBindTexture(GL_TEXTURE_2D, texture);


		myShader.Use();

		//EJERCICIO 2
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(myShader.Program, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(myShader.Program, "ourTexture2"), 1);
		glUniform1f(glGetUniformLocation(myShader.Program, "mixValue"), mixValue);

		//=========================================================================================================================
		//															   3D
		
		//glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		//model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		//model = glm::rotate(model, glm::radians(-50.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.0f, -3.0f));
		projection = glm::perspective(glm::radians(60.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

		GLint modelLocation = glGetUniformLocation(myShader.Program, "model");
		GLint viewLocation = glGetUniformLocation(myShader.Program, "view");
		GLint projectionLocation = glGetUniformLocation(myShader.Program, "projection");
		
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));


		//DO TRANSFORMATION TO THE CUBE:
		glBindVertexArray(VAO);
		for (GLuint i = 0; i < 10; i++) {
			glm::mat4 model;
			model = glm::translate(model, CubesPositionBuffer[i]);
			GLfloat angle = 10.0f * i;

			model = glm::rotate(model, glm::radians(angle), glm::vec3(0.7f, 1.0f, 0.5f));
			model = glm::rotate(model, glm::radians(rotationX), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians((GLfloat)glfwGetTime()*100), glm::vec3(1.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		//=========================================================================================================================

		
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		//pintar con lineas
		//DrawVAO(VAO, myShader, texture);
		
		//intercambia el framebuffer
		glfwSwapBuffers(window);
		//comprueba que algun disparador se halla activado
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
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
		mixValue = 0;
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		/*mixValue -= 0.1f;
		if (mixValue <= 0.0f)
			mixValue = 0.0f;*/
		mixValue = 1;
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
	//TYPE = GL_FILL;
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
