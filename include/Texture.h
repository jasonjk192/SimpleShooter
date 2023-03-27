#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Texture
{
public:
	Texture();
	Texture(SDL_Renderer* aRenderer, int width = 1, int height = 1, Uint32 format = SDL_PIXELFORMAT_RGBA32, int access = SDL_TEXTUREACCESS_STATIC);
	Texture(SDL_Renderer* aRenderer, const char* anImage);
	Texture(SDL_Renderer* aRenderer, const char* aText, const char* aFontFile, int aFontSize = 24);
	Texture(SDL_Renderer* aRenderer, Texture* aTexture, SDL_Rect* srcRect = nullptr, Uint32 format = SDL_PIXELFORMAT_RGBA32, int access = SDL_TEXTUREACCESS_STATIC);
	~Texture(void);

	SDL_Texture* GetTexture() { return texture; }
	SDL_Point* GetSize() { return size; }

private:
	SDL_Texture* texture;
	SDL_Point* size;
};

#endif // TEXTURE_H