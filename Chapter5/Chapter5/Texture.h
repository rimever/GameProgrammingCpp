#pragma once

#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	bool Load(const std::string& fileName);
	void Unload();

	void SetActive();

	int GetWidth() const { return this->mWidth; }
	int GetHeight() const { return this->mHeight; }

private:
	int mWidth;
	int mHeight;
	unsigned int mTextureID;
};
