#include "Context.h"

Context::Context(unsigned int width, unsigned int height, std::string title)
	: m_width(width), m_height(height), m_title(title)
{
	m_window = glfwCreateWindow((int)width, (int)height, title.c_str(), NULL, NULL);
}

Context::~Context()
{
	glfwTerminate();
	delete[] m_window;
}

void Context::Use()
{
	glfwMakeContextCurrent(m_window);
}

void Context::SwapBuffers()
{
	glfwSwapBuffers(m_window);
}


