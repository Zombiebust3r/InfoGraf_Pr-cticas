#version 330 core

#define NUM_MAX_PLIGHTS 2
#define NUM_MAX_SLIGHTS 2

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
};   

struct PLight {

  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float c1;
  float c2;
  float c3;
};

struct DLight {

  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct SLight {
  vec3 position;
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float c1;
  float c2;
  float c3;
  float innerPhi;
  float outerPhi;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
out vec4 color;
  
uniform vec3 viewPos;
uniform Material material;
uniform DLight dlight;
uniform PLight plight[NUM_MAX_PLIGHTS];
uniform SLight slight[NUM_MAX_SLIGHTS];

vec3 DirectionalLight(DLight light, vec3 Normal, vec3 viewDirection);
vec3 PointLight(PLight light, vec3 Normal, vec3 viewDirection);
vec3 SpotLight(SLight light, vec3 Normal, vec3 viewDirection);

void main(){
	
	vec3 normalV = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	
	vec3 result = DirectionalLight(dlight, normalV, viewDir);
	for (int i = 0; i < NUM_MAX_PLIGHTS; i++){
		result += PointLight(plight[i], normalV, viewDir); 
	}
	
	for (int i = 0; i < NUM_MAX_SLIGHTS; i++){
		result += SpotLight(slight[i], normalV, viewDir); 
	}
	
	color = vec4(result, 1.0);
} 

vec3 DirectionalLight(DLight light, vec3 Normal, vec3 viewDirection){
	
	float ambientStrength = 0.1f;
	float diffStrength = 1.0f;
	float specStrength = 1.0f;
	
    vec3 ambient = ambientStrength * vec3(texture(material.diffuse, TexCoords)) * light.ambient;
	
	vec3 Ldiff = normalize(-light.direction);
	float diff = max(dot(Normal, Ldiff), 0);
	vec3 diffuse = diffStrength * diff * vec3(texture(material.diffuse, TexCoords)) * light.diffuse;
	
	vec3 espV = normalize(viewPos - FragPos);
	vec3 espR = reflect(-Ldiff, Normal);
	float esp = pow(max(dot(espR, espV), 0), material.shininess);
	vec3 specular = specStrength * esp * vec3(texture(material.specular, TexCoords)) * light.specular;
	
	vec3 result = ambient + specular + diffuse;
    return result;
}

vec3 PointLight(PLight light, vec3 Normal, vec3 viewDirection){


	float ambientStrength = 1.0f;
	float diffStrength = 1.0f;
	float specStrength = 1.0f;
	//amb
	vec3 ambient = ambientStrength * vec3(texture(material.diffuse, TexCoords)) * light.ambient;
	//diff
	vec3 Ldiff = normalize(light.position - FragPos);
	float diff = max(dot(Normal, Ldiff), 0);
	vec3 diffuse = diffStrength * diff * vec3(texture(material.diffuse, TexCoords)) * light.diffuse;
	//esp
	vec3 espV = normalize(viewPos - FragPos);
	vec3 espR = reflect(-Ldiff, Normal);
	float esp = pow(max(dot(espV, espR), 0), material.shininess);
	vec3 specular = specStrength * esp * vec3(texture(material.specular, TexCoords)) * light.specular;
	
	float distance = length(light.position - FragPos);
	float attenuation = 1 / (light.c1 * 1 + light.c2 * distance + light.c3 *pow(distance,2));
	
	vec3 result = (ambient + diffuse + specular)* attenuation;
	return result;
}

vec3 SpotLight(SLight light, vec3 Normal, vec3 viewDirection){

	vec3 lDir = normalize (light.position - FragPos);
	float theta = dot(lDir, normalize(-light.direction));
	float epsilon = light.innerPhi - light.outerPhi;
	float intensity = clamp((theta - light.outerPhi) / epsilon, 0.0, 1.0);    
	
	float ambientStrength = 1.0f;
	float diffStrength = 1.0f;
	float specStrength = 1.0f;
	
	vec3 ambient = ambientStrength * vec3(texture(material.diffuse, TexCoords))* light.ambient;
	
	float diff = max(dot(Normal, lDir), 0);
	vec3 diffuse = diffStrength * diff * vec3(texture(material.diffuse, TexCoords)) * light.diffuse;
	
	vec3 espV = normalize(viewPos - FragPos);
	vec3 espR = reflect(-lDir, Normal);
	float esp = pow(max(dot(espR, espV), 0), material.shininess);
	vec3 specular = specStrength * esp * vec3(texture(material.specular, TexCoords)) * light.specular;
	
	float distance = length(light.position - FragPos);
	float attenuation = 1 / (light.c1 * 1 + light.c2 * distance + light.c3 *pow(distance,2));
	
	vec3 result = (ambient + diffuse + specular)* intensity * attenuation;
	return result;
}