#ifndef DRAWER_H
#define DRAWER_H

#include "Texture.h"

#include <SDL.h>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;

class Drawer
{
public:
	Drawer(SDL_Window* aWindow, SDL_Renderer* aRenderer);
	~Drawer(void);

	void Draw(Texture* aTexture, int aCellX = 0, int aCellY = 0, double aRotationAngle = 0, SDL_RendererFlip aRenderFlip = SDL_FLIP_NONE);
	void Draw(Texture* aTexture, SDL_Rect* aSrcRect = nullptr, SDL_Rect* aDstRect = nullptr, double aRotationAngle = 0, SDL_RendererFlip aRenderFlip = SDL_FLIP_NONE);
	void DrawLine(int aX, int aY, int bX, int bY);
	void DrawRect(int x, int y, int w, int h, bool isFilled = false);
	void DrawText(const char* aText, const char* aFontFile, int aX, int aY, int aFontSize = 24);

	void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void SetBlendMode(int blendMode);
	void SetScale(float scale);
	void SetTextureColorMod(Texture* aTexture, Uint8 r, Uint8 g, Uint8 b);
	void SetTextureAlphaMod(Texture* aTexture, Uint8 a);

	int GetTexturePositionFromRight(Texture* aTexture, int anOffset = 0);
	int GetTexturePositionFromBottom(Texture* aTexture, int anOffset = 0);
	float GetScale() const { return renderScale; }
	void GetWindowSize(int *w, int *h) { SDL_GetWindowSize(myWindow, w, h); }
	SDL_Renderer* GetRenderer() { return myRenderer; }

private:
	float renderScale;
	SDL_Window* myWindow;
	SDL_Renderer* myRenderer;
};

#endif // DRAWER_H