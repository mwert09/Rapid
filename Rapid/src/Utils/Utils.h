#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <GL/glew.h>


#include "glm/glm.hpp"

namespace Rapid
{
	namespace Utils
	{
		std::string ReadFile(const char* fileLocation);
		void CalculateAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int vertexCount, unsigned int vLength, unsigned int normalOffset);
	}
}