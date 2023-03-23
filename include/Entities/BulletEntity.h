#ifndef BULLETENTITY_H
#define BULLETENTITY_H

#include "Assets/SDLMaths.h"

#include "DynamicEntity.h"
#include "World.h"

class World;

class BulletEntity : public DynamicEntity
{
public:
	BulletEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer, World* aWorld);
	~BulletEntity(void);

	bool Update(float aTime);
	void OnCollision(BaseEntity* anEntity);

	void SetVelocity(SDL_FPoint& aVelocity) { myVelocity = aVelocity; }
	void SetOwner(BaseEntity* anOwner) { myOwner = anOwner; }

private:
	BaseEntity* myOwner;

	float myLifetime;
	World* myWorld;
};

#endif // BULLETENTITY_H