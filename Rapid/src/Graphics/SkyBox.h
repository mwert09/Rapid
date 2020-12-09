#pragma once

#include <vector>
#include <string>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CommonValues.h"
#include "Shader.h"
#include "Mesh.h"

namespace Rapid
{
	namespace Graphics
	{
		class SkyBox
		{
			// VARIABLES
		public:

		private:
			Mesh* skyMesh;
			Shader* skyShader;

			GLuint textureId;
			GLuint uniformProjection, uniformView;
			
			// FUNCTIONS
		public:
			SkyBox();
			~SkyBox();
			SkyBox(std::vector<std::string> faceLocations);
			void DrawSkyBox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
		private:
			
		};
	}
}


