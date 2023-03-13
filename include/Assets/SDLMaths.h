#ifndef SDLMATHS_H
#define SDLMATHS_H

#include <SDL.h>

class SDLMaths
{
public:
	static float Distance(SDL_FPoint& a, SDL_FPoint& b);

	static SDL_FPoint Direction(SDL_FPoint& a, SDL_FPoint& b);

	static SDL_FPoint Normalize(SDL_FPoint& a);

	static float Magnitude(SDL_FPoint& a);

};

#endif // SDLMATHS_H