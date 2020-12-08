#pragma once
#include "Light.h"

namespace Rapid{namespace Graphics{
	
class DirectionalLight : public Light
{
public:
	DirectionalLight();
	~DirectionalLight();
	
	DirectionalLight(GLfloat shadowWidth, GLfloat shadowHeight, GLfloat red, GLfloat green, GLfloat blue,
					 GLfloat intensity, GLfloat dIntensity,
					 GLfloat xDir, GLfloat yDir, GLfloat zDir);
	
	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation);
	void UpdateLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation);

	glm::mat4 CalculateLightTransform();

public:
	glm::vec3 direction;
};

}}

