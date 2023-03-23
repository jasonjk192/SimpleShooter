#ifndef WORLD_H
#define WORLD_H

#include "Assets/BackgroundAsset.h"
#include "Assets/UIAsset.h"
#include "Assets/ShipAsset.h"
#include "Assets/MiscAsset.h"

#include "StateMachine.h"
#include "Drawer.h"

#include "Entities/PlayerShipEntity.h"
#include "Entities/EnemyShipEntity.h"

#include <vector>

class PlayerShipEntity;

class World
{
public:
	World(StateMachine* aStateMachine, Drawer* aDrawer);
	~World(void);

	bool HandleEvents(SDL_Event* event);
	bool Update(float aTime);
	bool Draw();

	template<typename ENTITY>
	ENTITY* SpawnEntity(SDL_FPoint& aPosition, Texture* aTexture)
	{
		ENTITY* entity = new ENTITY(aPosition,aTexture,myDrawer, this);
		if (entity)
		{
			newEntities.push_back(entity);
			return entity;
		}
		return nullptr;
	};

private:
	void CheckCollisions();
	void DespawnEntities();

	StateMachine* myStateMachine;
	Drawer* myDrawer;

	BackgroundAsset* myBackgroundAsset;
	MiscAsset* myMiscAsset;
	UIAsset* myUIAsset;

	std::vector<BaseEntity*> worldEntities;
	std::vector<BaseEntity*> newEntities;

	float myEnemySpawnerCooldown = 5.f;
	float currentEnemySpawnerCooldown = 0.f;
};

#endif // WORLD_H