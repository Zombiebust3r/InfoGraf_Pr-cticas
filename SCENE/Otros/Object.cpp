#include "Object.h"

Object::Object(vec3 scale, vec3 rotation, vec3 position, FigureType typef) {

	if (typef == cube) {
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
		vec3 IndexBufferObject[] = {
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
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferObject), VertexBufferObject, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexBufferObject), IndexBufferObject, GL_STATIC_DRAW);
		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// Normal attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		//tex coords
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glBindVertexArray(0);
	}
	else if (typef == invertedcube) {
		GLfloat VertexBufferObject[] = {
			//front
			0.5f,  0.5f, -0.5f,  0.0f,  0.0f, 1.0f,  1.0f,  1.0f,
			0.5f, -0.5f, -0.5f,  0.0f,  0.0f, 1.0f,  1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, 1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, 1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, 1.0f,  0.0f,  1.0f,
			0.5f ,  0.5f, -0.5f,  0.0f,  0.0f, 1.0f,  1.0f,  1.0f,
			//back
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  -1.0f,  0.0f,  0.0f,
			0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  -1.0f,  1.0f,  0.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  -1.0f,  1.0f,  1.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  -1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  -1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  -1.0f,  0.0f,  0.0f,
			//left	
			-0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			//right
			0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			//down
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
			//up
			0.5f,  0.5f,  0.5f,  0.0f,  -1.0f,  0.0f,  1.0f,  0.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  -1.0f,  0.0f,  1.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  -1.0f,  0.0f,  0.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  -1.0f,  0.0f,  0.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  -1.0f,  0.0f,  0.0f,  0.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  -1.0f,  0.0f,  1.0f,  0.0f
		};

		vec3 IndexBufferObject[] = {
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
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferObject), VertexBufferObject, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexBufferObject), IndexBufferObject, GL_STATIC_DRAW);
		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// Normal attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		//tex coords
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glBindVertexArray(0);
	}
	Vposition = position;
	Vrotation = rotation;
	Vscale = scale;
}

Object::~Object() {

}

void Object::Draw() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void Object::Move(vec3 translation) {
	Vposition = translation;
}
void Object::Rotate(vec3 rota) {
	Vrotation = rota;
}
void Object::Scale(vec3 scal) {
	Vscale = scal;
}

mat4 Object::GetModelMatrix() {
	mat4 model;
	model = translate(model, Vposition);
	model = rotate(model, radians(Vrotation.x), vec3(1, 0, 0));
	model = rotate(model, radians(Vrotation.y), vec3(0, 1, 0));
	model = scale(model, Vscale);
	return model;
}

vec3 Object::GetPosition() {
	return Vposition;
}

void Object::Delete() {

}
