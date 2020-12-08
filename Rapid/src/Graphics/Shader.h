#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../src/Utils/Utils.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "CommonValues.h"

namespace Rapid	{	namespace Graphics	{
		
class Shader
{
public:

private:
	int pointLightCount;
	int spotLightCount;
	
	GLuint shaderID, uniformProjection, uniformModel, uniformView,
		uniformEyePosition, uniformSpecularIntensity, uniformShininess, uniformDiffuse, uniformSpecular,
		uniformDirectionalLightTransform, uniformDirectionalShadowMap, uniformTexture,
		uniformOmniLightPos, uniformFarPlane;

	GLuint uniformLightMatrices[6];

	struct
	{
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformDirection;
	}uniformDirectionalLight;

	GLuint uniformPointLightCount;
	struct
	{
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;
	}uniformPointLight[MAX_POINT_LIGHTS];

	GLuint uniformSpotLightCount;
	struct
	{
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;

		GLuint uniformDirection;
		GLuint uniformEdge;
		
	}uniformSpotLight[MAX_SPOT_LIGHTS];

	struct
	{
		GLuint shadowMap;
		GLuint farPlane;
	}uniformOmniShadowMap[MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS];
	
public:
	Shader();
	~Shader();
	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
	void CreateFromFiles(const char* vertexLocation, const char* geometryLocation, const char* fragmentLocation);
	void Validate();
	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColourLocation();
	GLuint GetDiffuseIntensityLocation();
	GLuint GetDirectionLocation();
	GLuint GetSpecularIntensityLocation();
	GLuint GetShininessLocation();
	GLuint GetEyePositionLocation();
	GLuint getUniformDiffuse();
	GLuint GetuniformSpecular();
	GLuint GetOmniLightPosLocation();
	GLuint GetFarPlanePosLocation();
	
	void SetDirectionalLight(DirectionalLight* dLight);
	void UpdateDirectionalLight(DirectionalLight* dLight, float directionalLightRedValue, float directionalLightGreenValue, float directionalLightBlueValue,
		float directionalLightIntensity, float directionalLightDiffuseIntensity,
		float directionalLightXDir, float directionalLightYDir, float directionalLightZDir);
	void UpdateSpotLight(SpotLight* sLight, int index, float directionalLightRedValue, float directionalLightGreenValue, float directionalLightBlueValue,
		float directionalLightIntensity, float directionalLightDiffuseIntensity,
		float directionalLightXDir, float directionalLightYDir, float directionalLightZDir);
	void SetPointLights(PointLight* pLight, unsigned int lightCount, unsigned int textureUnit, unsigned int offset);
	void SetSpotLights(SpotLight* sLight, unsigned int lightCount, unsigned int textureUnit, unsigned int offset);
	void SetTexture(GLuint textureUnit);
	void SetDirectionalShadowMap(GLuint textureUnit);
	void SetDirectionalLightTransform(glm::mat4* ltransform);
	void SetLightMatrices(std::vector<glm::mat4> lightMatrices);
	void UseShader();
	void ClearShader();
	
private:
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void CompileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

	void CompileProgram();
};

}}