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

GLuint VAO, VBO, shader, uniformModel;

bool direction = true;
float triOffset = 0;
float triMaxOffset = 0.7f;
float triIncrement = 0.0005f;

// Vertex Shader
static const char* vShader = "												\n\
#version 330																\n\
																			\n\
layout (location = 0) in vec3 pos;											\n\
																			\n\
uniform mat4 model;															\n\
																			\n\
void main()																	\n\
{																			\n\
	gl_Position = model * vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);		\n\
}";

// Fragment Shader
static const char* fShader = "										\n\
#version 330														\n\
																	\n\
out	vec4 colour;													\n\
																	\n\
void main()															\n\
{																	\n\
	colour = vec4(1.0f, 0.0f, 0.0f, 1.0);							\n\
}";

void CreateTriangle()
{
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

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
		
		window.Clear();
		glUseProgram(shader);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(triOffset, triOffset, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glUseProgram(0);
		window.Update();
	}
	
	return 0;
}