#ifndef PLAYERSHIPENTITY_H
#define PLAYERSHIPENTITY_H

#include "Assets/SDLMaths.h"

#include "Assets/MiscAsset.h"

#include "BulletEntity.h"
#include "DynamicEntity.h"

#include "World.h"

class World;

class PlayerShipEntity : public DynamicEntity
{
public:
	PlayerShipEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer, World* aWorld);
	~PlayerShipEntity(void);

	bool HandleEvents(SDL_Event* event);
	bool Update(float aTime);
	void Draw();

private:
	void Shoot();

	World* myWorld;

	float myShootCooldown = 0.5f;
	float currentShootCooldown = 0.f;
};

#endif // PLAYERSHIPENTITY_H