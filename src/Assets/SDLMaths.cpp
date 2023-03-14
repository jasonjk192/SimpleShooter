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

float SDLMaths::Angle(SDL_FPoint& a)
{
	return atan2(a.y, a.x);
}

float SDLMaths::rad2deg(float rad)
{
	return rad * 180.f / 3.1415927f;
}

float SDLMaths::deg2rad(float deg)
{
	return deg * 3.1415927f / 180.f;
}

SDL_FPoint SDLMaths::ClampMagnitude(SDL_FPoint& a, float b)
{
	float mag = Magnitude(a);
	if (mag > b)
		return { a.x * b / mag, a.y * b / mag };
	else
		return a;
}