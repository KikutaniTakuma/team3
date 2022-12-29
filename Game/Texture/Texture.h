#pragma once

class Texture {
private:
	const char* fileName;

public:
	Texture(const char *fileName_, int spriteSize_, int width_, int height_);
	Texture();

	void Set(const char* fileName_, int spriteSize_, int width_, int height_);

	int spriteSize;
	int width;
	int height;

	int drawPos;

	int textureHandle;

	const Texture& operator=(const Texture &texture);

	void setLoadTexture();
};