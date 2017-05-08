#include "Lights.h"

Lights::Lights(vec3 pos, vec3 dir, vec3 ambient, vec3 diffuse, vec3 specular, LType lType, int number) : lightPos(pos), lightDirection(dir), lightAmbient(ambient), lightDiffuse(diffuse), lightSpecular(specular), lightType(lType), lightNumber(number) {
}
Lights::~Lights() {}

void Lights::SetAtt(float constant, float lineal, float quadratic) {
	ce1 = constant;
	ce2 = lineal;
	ce3 = quadratic;

}

void Lights::SetAperture(float min, float max) {
	minAperture = cos(radians(min));
	maxAperture = cos(radians(max));

}

void Lights::SetLight(Shader *shad, vec3 CamPos) {
	std::string variable;
	glUniform3f(glGetUniformLocation(shad->Program, "viewPos"), CamPos.x, CamPos.y, CamPos.z);
	switch (lightType) {
	case DIRECTIONAL:
		glUniform3f(glGetUniformLocation(shad->Program, "dlight.direction"), lightDirection.x, lightDirection.y, lightDirection.z);
		glUniform3f(glGetUniformLocation(shad->Program, "dlight.ambient"), lightAmbient.x, lightAmbient.y, lightAmbient.z);
		glUniform3f(glGetUniformLocation(shad->Program, "dlight.diffuse"), lightDiffuse.x, lightDiffuse.y, lightDiffuse.z);
		glUniform3f(glGetUniformLocation(shad->Program, "dlight.specular"), lightSpecular.x, lightSpecular.y, lightSpecular.z);

		break;
	case POINT:
		variable = "plight[" + std::to_string(lightNumber) + "].";
		glUniform3f(glGetUniformLocation(shad->Program, (variable + "position").c_str()), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(shad->Program, (variable + "ambient").c_str()), lightAmbient.x, lightAmbient.y, lightAmbient.z);
		glUniform3f(glGetUniformLocation(shad->Program, (variable + "diffuse").c_str()), lightDiffuse.x, lightDiffuse.y, lightDiffuse.z);
		glUniform3f(glGetUniformLocation(shad->Program, (variable + "specular").c_str()), lightSpecular.x, lightSpecular.y, lightSpecular.z);
		glUniform1f(glGetUniformLocation(shad->Program, (variable + "c1").c_str()), ce1);
		glUniform1f(glGetUniformLocation(shad->Program, (variable + "c2").c_str()), ce2);
		glUniform1f(glGetUniformLocation(shad->Program, (variable + "c3").c_str()), ce3);


		break;
	case SPOT:

		variable = "slight[" + std::to_string(lightNumber) + "].";
		glUniform3f(glGetUniformLocation(shad->Program, (variable + "position").c_str()), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(shad->Program, (variable + "direction").c_str()), lightDirection.x, lightDirection.y, lightDirection.z);
		glUniform3f(glGetUniformLocation(shad->Program, (variable + "ambient").c_str()), lightAmbient.x, lightAmbient.y, lightAmbient.z);
		glUniform3f(glGetUniformLocation(shad->Program, (variable + "diffuse").c_str()), lightDiffuse.x, lightDiffuse.y, lightDiffuse.z);
		glUniform3f(glGetUniformLocation(shad->Program, (variable + "specular").c_str()), lightSpecular.x, lightSpecular.y, lightSpecular.z);
		glUniform1f(glGetUniformLocation(shad->Program, (variable + "c1").c_str()), ce1);
		glUniform1f(glGetUniformLocation(shad->Program, (variable + "c2").c_str()), ce2);
		glUniform1f(glGetUniformLocation(shad->Program, (variable + "c3").c_str()), ce3);
		glUniform1f(glGetUniformLocation(shad->Program, (variable + "innerPhi").c_str()), minAperture);
		glUniform1f(glGetUniformLocation(shad->Program, (variable + "outerPhi").c_str()), maxAperture);
		break;
	default:
		break;

	}
}

void Lights::Rotate(vec3 rotation) {
	lightDirection += rotation;

}

void Lights::SetDirection(vec3 dir) {
	lightDirection = dir;

}

void Lights::SetPosition(vec3 pos) {
	lightPos = pos;

}

vec3 Lights::GetColor() {
	return vec3(0, 0, 0);

}