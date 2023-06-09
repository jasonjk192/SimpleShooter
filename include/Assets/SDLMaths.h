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

	static float Dot(SDL_FPoint& a, SDL_FPoint& b);

	static float Determinant(SDL_FPoint& a, SDL_FPoint& b);

	static float Angle(SDL_FPoint& a);

	static float Angle(SDL_FPoint& a, SDL_FPoint& b);

	static float rad2deg(float rad);

	static float deg2rad(float deg);

	static SDL_FPoint ClampMagnitude(SDL_FPoint& a, float b);

	static SDL_FPoint Lerp(SDL_FPoint& a, SDL_FPoint& b, float t);
};

#endif // SDLMATHS_H