#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Drawer* aDrawer, SystemParams aSysParam):
	myDrawer(aDrawer),
	myParams(aSysParam),
	myEmissionTime(aSysParam.myFrequency),
	myCurrentParticleCount(0),
	myParticles(aSysParam.myMaxParticleCount)
{}

ParticleSystem::~ParticleSystem(void)
{
}

void ParticleSystem::Update(float aTime)
{
	for (int i=0; i<myCurrentParticleCount; )
	{
		auto particle = &myParticles[i];
		particle->myPosition = SDL_FPoint{ particle->myPosition.x + aTime * particle->myVelocity.x + 0.5f * aTime * aTime * particle->myAcceleration.x,
										particle->myPosition.y + aTime * particle->myVelocity.y + 0.5f * aTime * aTime * particle->myAcceleration.y };
		particle->myRotation = SDLMaths::Angle(particle->myVelocity);
		particle->myLifetime -= aTime;
		if (particle->myLifetime <= 0.f)
			ResetParticle(*particle);
		else
			i++;
	}

	myEmissionTime -= aTime;

	if (myEmissionTime <= 0)
	{
		if (myCurrentParticleCount < myParams.myMaxParticleCount)
			Spawn();
		myEmissionTime = myParams.myFrequency;
	}
}

void ParticleSystem::Spawn()
{
	Particle particle;
	particle.myPosition = myParams.myPosition;
	particle.myVelocity = myParams.myVelocity;
	particle.myAcceleration = myParams.myAcceleration;
	particle.myLifetime = myParams.myLifetime;
	myParticles[myCurrentParticleCount] = particle;
	myCurrentParticleCount++;
}

void ParticleSystem::Draw()
{
	myDrawer->SetBlendMode(1);
	for (auto& particle : myParticles)
	{
		myDrawer->SetTextureColorMod(myParams.myTexture, particle.myColor.r, particle.myColor.g, particle.myColor.b);
		myDrawer->SetTextureAlphaMod(myParams.myTexture, 255 * particle.myLifetime / myParams.myLifetime);
		myDrawer->Draw(myParams.myTexture, particle.myPosition.x, particle.myPosition.y, SDLMaths::rad2deg(particle.myRotation));
	}
	myDrawer->SetTextureColorMod(myParams.myTexture, 255, 255, 255);
	myDrawer->SetTextureAlphaMod(myParams.myTexture, 255);
	myDrawer->SetBlendMode(0);
}

void ParticleSystem::ResetParticle(Particle& particle)
{
	Particle t = std::move(myParticles[--myCurrentParticleCount]);
	myParticles[myCurrentParticleCount] = std::move(particle);
	particle = std::move(t);
}