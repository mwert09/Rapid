#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

#include <GL/glew.h>

#include "../../src/Utils/Utils.h"

namespace Rapid	{	namespace Graphics	{
		
class Shader
{
public:

private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView,
	uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformDirection;

public:
	Shader();
	~Shader();
	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColourLocation();
	GLuint GetDiffuseIntensityLocation();
	GLuint GetDirectionLocation();
	void UseShader();
	void ClearShader();
	
private:
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

}}