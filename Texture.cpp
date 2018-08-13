#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture.h"



Texture::Texture(std::string fileName)
{
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(fileName.c_str(), &width, &height, NULL, 4);

	glGenTextures(1, &mID);

	glBindTexture(GL_TEXTURE_2D, mID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}


Texture::~Texture()
{
}
