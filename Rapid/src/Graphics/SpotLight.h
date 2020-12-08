#pragma once
#include "PointLight.h"

namespace Rapid
{
	namespace Graphics
	{
		class SpotLight : public PointLight
		{
		public:
			glm::vec3 direction;
			GLfloat edge, procEdge;
			bool isOn;
		public:
			SpotLight();
			~SpotLight();

			SpotLight(GLuint shadowWidth, GLuint shadowHeight,
				GLfloat near, GLfloat far, GLfloat red, GLfloat green, GLfloat blue, GLfloat intensity, GLfloat dIntensity, GLfloat xPos, GLfloat yPos, GLfloat zPos,
				GLfloat xDir, GLfloat yDir, GLfloat zDir,
				GLfloat con, GLfloat lin, GLfloat exp,
				GLfloat edg);
			
			void UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation,
				GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint directionLocation,
				GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation,
				GLuint edgeLocation);

			

			void SetFlash(glm::vec3 pos, glm::vec3 dir);
			void Toggle() { isOn != isOn; }
		};
	}
}


