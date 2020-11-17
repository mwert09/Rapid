#include "Utils.h"

namespace Rapid
{
	namespace Utils
	{
		
		std::string ReadFile(const char* fileLocation)
		{
			std::string content;
			std::ifstream fileStream(fileLocation, std::ios::in);

			if(!fileStream.is_open())
			{
				std::cout << "Failed to read" << fileLocation << "! File does not exist. - Dosya Okunamadi!" << std::endl;
				return "";
			}
			std::string line = "";
			while(!fileStream.eof())
			{
				std::getline(fileStream, line);
				content.append(line + "\n");
			}

			fileStream.close();
			return content;
		}

		void CalculateAverageNormals(unsigned* indices, unsigned indiceCount, GLfloat* vertices, unsigned vertexCount, unsigned vLength, unsigned normalOffset)
		{
			for(size_t i = 0; i < indiceCount; i += 3)
			{
				unsigned int in0 = indices[i] * vLength;
				unsigned int in1 = indices[i + 1] * vLength;
				unsigned int in2 = indices[i + 2] * vLength;
				glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
				glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
				glm::vec3 normal = glm::cross(v1, v2);
				normal = glm::normalize(normal);
				in0 += normalOffset;
				in1 += normalOffset;
				in2 += normalOffset;
				vertices[in0] += normal.x;
				vertices[in0 + 1] += normal.y;
				vertices[in0 + 2] += normal.z;
				vertices[in1] += normal.x;
				vertices[in1 + 1] += normal.y;
				vertices[in1 + 2] += normal.z;
				vertices[in2] += normal.x;
				vertices[in2 + 1] += normal.y;
				vertices[in2 + 2] += normal.z;
			}
			for(size_t i = 0; i < vertexCount / vLength; i++)
			{
				unsigned int nOffset = i * vLength + normalOffset;
				glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
				vec = glm::normalize(vec);
				vertices[nOffset] = vec.x;
				vertices[nOffset + 1] = vec.y;
				vertices[nOffset + 2] = vec.z;
			}
		}

	}
}