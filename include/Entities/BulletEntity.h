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
	void Draw();
	void OnCollision(BaseEntity* anEntity);

	void SetVelocity(SDL_FPoint& aVelocity) { myVelocity = aVelocity; }
	void SetOwner(BaseEntity* anOwner) { myOwner = anOwner; }

protected:
	BaseEntity* myOwner;

	float myLifetime;
	World* myWorld;
};

class FriendlyBulletEntity : public BulletEntity
{
public:
	FriendlyBulletEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer, World* aWorld) : BulletEntity(aPosition, aTexture, aDrawer, aWorld) {}
	~FriendlyBulletEntity(void) {}
	void OnCollision(BaseEntity* anEntity);
};

class EnemyBulletEntity : public BulletEntity
{
public:
	EnemyBulletEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer, World* aWorld) : BulletEntity(aPosition, aTexture, aDrawer, aWorld) {}
	~EnemyBulletEntity(void) {}
	void OnCollision(BaseEntity* anEntity);
};

#endif // BULLETENTITY_H