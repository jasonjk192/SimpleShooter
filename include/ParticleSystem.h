#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "Texture.h"
#include "Drawer.h"
#include "Assets/SDLMaths.h"

#include <vector>
#include <iostream>

class ParticleSystem
{
public:
	struct Particle
	{
		SDL_FPoint myPosition{ 0,0 };
		SDL_FPoint myVelocity{ 0,0 };
		SDL_FPoint myAcceleration{ 0,0 };
		float myRotation = 0.f;
		SDL_Color myColor{ 255,255,255,255 };

		float myLifetime = 0.f;
	};

	struct SystemParams
	{
		int myMaxParticleCount = 0;
		float myLifetime = 0;
		float myFrequency = 0;
		SDL_FPoint myPosition{ 0,0 };
		SDL_FPoint myVelocity{0,0};
		SDL_FPoint myAcceleration{ 0,0 };
		Texture* myTexture = nullptr;
	};

	ParticleSystem(Drawer* aDrawer, SystemParams aSysParam);
	~ParticleSystem(void);

	void Update(float aTime);
	void Draw();

	SystemParams* GetParams() { return &myParams; }

private:
	void Spawn();
	void ResetParticle(Particle& particle);

	SystemParams myParams;
	float myEmissionTime;
	float myCurrentParticleCount;

	std::vector<Particle> myParticles;
	Drawer* myDrawer;
};

#endif // PARTICLESYSTEM_H