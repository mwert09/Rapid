#pragma once
#include "Light.h"

namespace Rapid
{
	namespace Graphics
	{
		class PointLight : public Light
		{
		public:
			PointLight();
			PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat intensity, GLfloat dIntensity, GLfloat xPos, GLfloat yPos, GLfloat zPos,
						GLfloat con, GLfloat lin, GLfloat exp);
			~PointLight();
			void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation, GLfloat positionLocation, GLfloat constantLocation,
							GLfloat linearLocation, GLfloat exponentLocation);
			
		private:
			glm::vec3 position;
			GLfloat constant, linear, exponent;
		};
	}
}

