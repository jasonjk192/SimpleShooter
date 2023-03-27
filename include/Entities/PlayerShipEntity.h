#ifndef PLAYERSHIPENTITY_H
#define PLAYERSHIPENTITY_H

#include "Assets/SDLMaths.h"

#include "Assets/ProjectileAsset.h"

#include "BulletEntity.h"
#include "GameCharacterEntity.h"

#include "World.h"

class World;

class PlayerShipEntity : public GameCharacterEntity
{
public:
	PlayerShipEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer, World* aWorld);
	~PlayerShipEntity(void);

	bool HandleEvents(SDL_Event* event);
	bool Update(float aTime);
	void Draw();
	void OnCollision(BaseEntity* anEntity);

	void AddScore(int aScore) { myScore += aScore; }
	int GetScore() const { return myScore; }

private:
	void Shoot();

	World* myWorld;

	int myScore;
};

#endif // PLAYERSHIPENTITY_H