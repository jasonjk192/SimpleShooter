#include "Drawer.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <iostream>

Drawer::Drawer(SDL_Window* aWindow, SDL_Renderer* aRenderer)
: myWindow(aWindow)
, myRenderer(aRenderer)
, renderScale(1.0f)
{}

Drawer::~Drawer(void)
{}

void Drawer::Draw(Texture* aTexture, int aCellX, int aCellY, double aRotationAngle, SDL_RendererFlip aRenderFlip)
{
	SDL_Point* size = aTexture->GetSize();

	SDL_Rect sizeRect;
	SDL_Rect posRect;
	sizeRect.x = 0;
	sizeRect.y = 0;
	sizeRect.w = size->x;
	sizeRect.h = size->y;
	posRect.x = (aCellX + size->x / 2) - (size->x / 2 * renderScale);
	posRect.y = (aCellY + size->y / 2) - (size->y / 2 * renderScale);
	posRect.w = size->x * renderScale;
	posRect.h = size->y * renderScale;
	
	SDL_RenderCopyEx(myRenderer, aTexture->GetTexture(), &sizeRect, &posRect, aRotationAngle, NULL, aRenderFlip);
}

void Drawer::Draw(Texture* aTexture, SDL_Rect* aSrcRect, SDL_Rect* aDstRect, double aRotationAngle, SDL_RendererFlip aRenderFlip)
{
	SDL_Point* size = aTexture->GetSize();
	if (aSrcRect == nullptr)
		aSrcRect = new SDL_Rect{ 0, 0, size->x, size->y};
	if (aDstRect == nullptr)
		aDstRect = new SDL_Rect{ 0, 0, size->x, size->y };
	aDstRect->x += (int)((aDstRect->w / 2.f) - (aDstRect->w / 2.f * renderScale));
	aDstRect->y += (int)((aDstRect->h / 2.f) - (aDstRect->h / 2.f * renderScale));
	aDstRect->w = (int)(aDstRect->w * renderScale);
	aDstRect->h = (int)(aDstRect->h * renderScale);
	SDL_RenderCopyEx(myRenderer, aTexture->GetTexture(), aSrcRect, aDstRect, aRotationAngle, NULL, aRenderFlip);
}

void Drawer::DrawLine(int aX, int aY, int bX, int bY)
{
	SDL_RenderDrawLine(myRenderer, aX, aY, bX, bY);
}

void Drawer::DrawRect(int x, int y, int w, int h, bool isFilled)
{
	const SDL_Rect rect{ x, y, w, h };
	isFilled ? SDL_RenderFillRect(myRenderer, &rect) : SDL_RenderDrawRect(myRenderer, &rect);
}

void Drawer::DrawText(const char* aText, const char* aFontFile, int aX, int aY)
{
	TTF_Font* font = TTF_OpenFont(aFontFile, 24);
	
	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(myRenderer, &r, &g, &b, &a);
	SDL_Color fg = { r,g,b,a };
	SDL_Surface* surface = TTF_RenderText_Solid(font, aText, fg);

	SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(myRenderer, surface);

	SDL_Rect sizeRect;
	sizeRect.x = 0;
	sizeRect.y = 0;
	sizeRect.w = surface->w;
	sizeRect.h = surface->h;

	SDL_Rect posRect;
	posRect.x = aX;
	posRect.y = aY;
	posRect.w = sizeRect.w;
	posRect.h = sizeRect.h;

	SDL_RenderCopy(myRenderer, optimizedSurface, &sizeRect, &posRect);
	SDL_DestroyTexture(optimizedSurface);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}

void Drawer::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(myRenderer, r, g, b, a);
}

void Drawer::SetBlendMode(int blendMode)
{
	SDL_BlendMode mode = SDL_BLENDMODE_NONE;
	if (blendMode == 1)
		mode = SDL_BLENDMODE_BLEND;
	else if (blendMode == 2)
		mode = SDL_BLENDMODE_ADD;
	else if (blendMode == 3)
		mode = SDL_BLENDMODE_MOD;
	SDL_SetRenderDrawBlendMode(myRenderer, mode);
}

void Drawer::SetScale(float scale)
{
	renderScale = scale;
}

void Drawer::SetTextureColorMod(Texture aTexture, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(aTexture.GetTexture(), r, g, b);
}

int Drawer::GetTexturePositionFromRight(Texture* aTexture, int anOffset)
{
	int w, h;
	SDL_GetWindowSize(myWindow, &w, &h);
	return w - aTexture->GetSize()->x - anOffset;
}

int Drawer::GetTexturePositionFromBottom(Texture* aTexture, int anOffset)
{
	int w, h;
	SDL_GetWindowSize(myWindow, &w, &h);
	return h - aTexture->GetSize()->y - anOffset;
}