#pragma once

#include <string>
#include <glm.hpp>
#include <GL/glew.h>

class Texture
{
public:
	Texture(std::string fileName);
	~Texture();
	
	inline void Bind(int slot) const { glActiveTexture(GL_TEXTURE0 + slot); glBindTexture(GL_TEXTURE_2D, mID); }
	inline void Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

private:
	GLuint mID;
	int width;
	int height;
	int bpp;
};

