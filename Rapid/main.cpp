/*
 *                  Rapid Render Engine - Core
 *                          Mert Kilic
 *
 * 
 */
#include <iostream>
#include <string.h>
#include <cmath>

#include "src/Graphics/Shader.h"
#include "src/Graphics/Window.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Rapid;
using namespace Graphics;

GLuint VAO, VBO, IBO, shader, uniformModel;
const float toRadians = 3.14159265f / 180.0f;

bool direction = true;
float triOffset = 0;
float triMaxOffset = 0.7f;
float triIncrement = 0.0005f;

float curAngle = 0.0f;

bool sizeDirection = true;
float curSize = 0.4f;
float maxSize = 0.8f;
float minSize = 0.1f;

// Vertex Shader
static const char* vShader = "												\n\
#version 330																\n\
																			\n\
layout (location = 0) in vec3 pos;											\n\
																			\n\
out vec4 vCol;																\n\
																			\n\
uniform mat4 model;															\n\
																			\n\
void main()																	\n\
{																			\n\
	gl_Position = model * vec4(pos, 1.0);									\n\
	vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);								\n\
																			\n\
}";

// Fragment Shader
static const char* fShader = "										\n\
#version 330														\n\
																	\n\
in vec4 vCol;														\n\
																	\n\
out	vec4 colour;													\n\
																	\n\
void main()															\n\
{																	\n\
	colour = vCol;													\n\
}";

void CreateTriangle()
{
	unsigned int indices[] = {
		0,3,1,
		1,3,2,
		2,3,0,
		0,1,2
	};
	
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);
	
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);
	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		std::cout << "Error compiling the " << shaderType << " shader - Shader derlenirken hata : '" << eLog << "'" << std::endl;
		glDeleteShader(theShader);
		return;
	}

	glAttachShader(theProgram, theShader);
}

void CompileShaders()
{
	shader = glCreateProgram();
	if (!shader)
	{
		std::cout << "Error creating shader program! - Shader programi yaratilirken sorun olustu!" << std::endl;
		return;
	}
	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		std::cout << "Error linking program - Program baglanirken hata : '" << eLog << "'" << std::endl;
		glDeleteShader(shader);
		return;
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		std::cout << "Error validating program - Program dogrulanirken hata : '" << eLog << "'" << std::endl;
		glDeleteShader(shader);
		return;
	}
	uniformModel = glGetUniformLocation(shader, "model");
}

int main()
{
	Window window("Rapid", 800, 600);

	glEnable(GL_DEPTH_TEST);
	
	CreateTriangle();
	CompileShaders();
	
	// Render Loop
	while (!window.Closed())
	{

		if (direction)
		{
			triOffset += triIncrement;
		}
		else
		{
			triOffset -= triIncrement;
		}

		if (abs(triOffset) >= triMaxOffset)
		{
			direction = !direction;
		}

		curAngle += 0.01f;
		if(curAngle >= 360)
		{
			curAngle -= 360;
		}

		if(sizeDirection)
		{
			curSize += 0.001f;
		}else
		{
			curSize -= 0.001f;
		}

		if(curSize >= maxSize || curSize <= minSize)
		{
			sizeDirection = !sizeDirection;
		}
		
		window.Clear();
		glUseProgram(shader);
		
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glUseProgram(0);
		window.Update();
	}
	
	return 0;
}