#pragma once
#include <string>

#include <GLFW/glfw3.h>

class Context
{
public:
	Context() = default;
	Context(unsigned int width, unsigned int height, std::string title);
	~Context();
	
	void Use();

	void SwapBuffers();

	inline bool open() { 
		if (glfwWindowShouldClose(m_window)) m_open=false; 
		else m_open = true; 
		return m_open;
	}

	unsigned int getWidth() { return m_width; }
	unsigned int getHeight() { return m_height; }

private:

	GLFWwindow * m_window;

	unsigned int m_width;
	unsigned int m_height;
	std::string m_title;

	bool m_open;
};

