#include "Texture.h"

#include <iostream>

Texture::Texture() :
	texture(nullptr),
	size(nullptr)
{}

Texture::Texture(SDL_Renderer* aRenderer, int width, int height, Uint32 format, int access)
{
	size = new SDL_Point{ width, height };
	texture = SDL_CreateTexture(aRenderer, format, access, width, height);
}

Texture::Texture(SDL_Renderer* aRenderer, const char* anImage) :
	texture(nullptr),
	size(nullptr)
{
	SDL_Surface* surface = IMG_Load(anImage);

	if (!surface)
	{
		std::cout << "Unable to load: " << anImage << std::endl;
		return;
	}

	texture = SDL_CreateTextureFromSurface(aRenderer, surface);
	size = new SDL_Point();
	size->x = surface->w;
	size->y = surface->h;

	SDL_FreeSurface(surface);
}

Texture::Texture(SDL_Renderer* aRenderer, const char* aText, const char* aFontFile) :
	texture(nullptr),
	size(nullptr)
{
	TTF_Font* font = TTF_OpenFont(aFontFile, 24);
	if (!font)
	{
		std::cout << "Cannot read font file!" << std::endl;
		return;
	}

	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(aRenderer, &r, &g, &b, &a);
	SDL_Color fontColor = { r,g,b,a };

	SDL_Surface* surface = TTF_RenderText_Solid(font, aText, fontColor);
	if (!surface)
		return;

	texture = SDL_CreateTextureFromSurface(aRenderer, surface);
	size = new SDL_Point();
	size->x = surface->w;
	size->y = surface->h;

	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}

Texture::Texture(SDL_Renderer* aRenderer, Texture* aTexture, SDL_Rect* srcRect, Uint32 format, int access)
{
	if (srcRect == nullptr)
	{
		size = new SDL_Point{ aTexture->GetSize()->x, aTexture->GetSize()->y };
		srcRect = new SDL_Rect{0,0,size->x,size->y};
	}
	else
		size = new SDL_Point{ srcRect->w, srcRect->h };

	texture = SDL_CreateTexture(aRenderer, format, access, size->x, size->y);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(aRenderer, texture);
	SDL_RenderCopy(aRenderer, aTexture->GetTexture(), srcRect, NULL);
	SDL_SetRenderTarget(aRenderer, NULL);
}

Texture::~Texture(void)
{
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
}
