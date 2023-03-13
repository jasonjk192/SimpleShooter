#include "Assets/SDLMaths.h"

float SDLMaths::Distance(SDL_FPoint& a, SDL_FPoint& b)
{
	return sqrtf( powf( a.x-b.x, 2.f) + powf(a.y - b.y, 2.f));
}

SDL_FPoint SDLMaths::Direction(SDL_FPoint& a, SDL_FPoint& b)
{
	return {a.x-b.x, a.y-b.y};
}

SDL_FPoint SDLMaths::Normalize(SDL_FPoint& a)
{
	float s = Magnitude(a);
	return {a.x/s, a.y/s};
}

float SDLMaths::Magnitude(SDL_FPoint& a)
{
	return sqrtf(a.x*a.x + a.y*a.y);
}