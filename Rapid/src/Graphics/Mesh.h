#pragma once

#include <GL/glew.h>

namespace Rapid{namespace Graphics{
	
	class Mesh
	{
	public:
		Mesh();
		~Mesh();
		void CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
		void RenderMesh();
		void ClearMesh();

	private:
		GLuint VAO, VBO, IBO;
		GLsizei indexCount;
	};


	}}
