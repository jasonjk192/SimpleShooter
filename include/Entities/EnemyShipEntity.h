#ifndef ENEMYSHIPENTITY_H
#define ENEMYSHIPENTITY_H

#include "Assets/SDLMaths.h"

#include "Assets/MiscAsset.h"

#include "BulletEntity.h"
#include "AIShipEntity.h"

#include "World.h"

class World;

class EnemyShipEntity : public AIShipEntity
{
public:
	EnemyShipEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer, World* aWorld);
	~EnemyShipEntity(void);

	bool HandleEvents(SDL_Event* event);
	bool Update(float aTime);
	void Draw();

private:
	void Shoot();

	World* myWorld;

	float myShootCooldown = 0.5f;
	float currentShootCooldown = 0.f;

	static BehaviourTree::NodeStatus Move(float aTime, void* ship, SDL_Event* event);
	static BehaviourTree::NodeStatus PickRandom(float aTime, void* ship, SDL_Event* event);

	BehaviourTree::Sequence randomMoveSequence;
	Action PickRandomDestination = Action(*PickRandom, this);
	Action MoveToDestination = Action(*Move, this);
};

#endif // ENEMYSHIPENTITY_H