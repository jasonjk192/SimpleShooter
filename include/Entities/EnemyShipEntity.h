#ifndef ENEMYSHIPENTITY_H
#define ENEMYSHIPENTITY_H

#include "Assets/SDLMaths.h"

#include "Assets/MiscAsset.h"
#include "Assets/ProjectileAsset.h"

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
	void OnCollision(BaseEntity* anEntity);

private:
	World* myWorld;

	static BehaviourTree::NodeStatus Move(float aTime, void* ship, SDL_Event* event);
	static BehaviourTree::NodeStatus PickRandom(float aTime, void* ship, SDL_Event* event);
	static BehaviourTree::NodeStatus Nearby(float aTime, void* ship, SDL_Event* event);
	static BehaviourTree::NodeStatus Follow(float aTime, void* ship, SDL_Event* event);
	static BehaviourTree::NodeStatus Shoot(float aTime, void* ship, SDL_Event* event);

	BehaviourTree::Sequence randomMoveSequence;
	BehaviourTree::Sequence followAndShootSequence;
	BehaviourTree::Selector followOrRandomSelector;

	Action PickRandomDestination = Action(*PickRandom, this);
	Action MoveToDestination = Action(*Move, this);
	Action GetNearbyShip = Action(*Nearby, this);
	Action FollowShip = Action(*Follow, this);
	Action ShootAtShip = Action(*Shoot, this);
};

#endif // ENEMYSHIPENTITY_H