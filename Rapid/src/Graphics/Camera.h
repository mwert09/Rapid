#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

#include <iostream>

namespace Rapid{
	
	class Camera
	{
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Front;
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp;

		GLfloat m_Yaw;
		GLfloat m_Pitch;

		GLfloat m_MovementSpeed;
		GLfloat m_TurnSpeed;

		
	public:
		GLfloat fieldOfView = 60.0f;
	public:
		Camera();
		Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
		~Camera();

		void Update();
		void InputControl(bool* keys, GLfloat deltaTime);
		void MouseControl(GLfloat xChange, GLfloat yChange);
		void HandleScroll(GLfloat xOffset, GLfloat yOffset);
		glm::vec3 GetCameraPosition();
		glm::vec3 GetCameraDirection();
		GLfloat GetFOV();
		glm::mat4 CalculateViewMatrix();
	};

}

