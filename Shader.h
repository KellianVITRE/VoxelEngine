#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <glm.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ShaderProgram {
public:
	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	~ShaderProgram();

	void Bind();
	void Unbind();

	void SetUniformMat4(glm::mat4 matrix, const char* location);
private:
	GLuint m_program;
	GLuint m_vertexShader;
	GLuint m_fragmentShader;
};