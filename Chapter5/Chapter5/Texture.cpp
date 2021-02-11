#include "Texture.h"
#include <soil.h> 
#include <GL/glew.h>
#include <iostream>
#include <SDL_log.h>

Texture::Texture() : mWidth(0), mHeight(0), mTextureID(0)
{
}

Texture::~Texture()
{
}

bool Texture::Load(const std::string& fileName)
{
	auto channels = 0;
	auto image = SOIL_load_image(fileName.c_str(), &this->mWidth, &this->mHeight, &channels, SOIL_LOAD_AUTO);
	if (image == nullptr)
	{
		SDL_Log("SOIL failed to load image %s: %s", fileName.c_str(), SOIL_last_result());
	}
	auto format = GL_RGB;
	if (channels == 4)
	{
		format = GL_RGBA;
	}
	glGenTextures(1, &this->mTextureID);
	glBindTexture(GL_TEXTURE_2D, this->mTextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, format, this->mWidth, this->mHeight, 0, format, GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return true;
}

void Texture::Unload()
{
	glDeleteTextures(1, &this->mTextureID);
}

void Texture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D, this->mTextureID);
}
