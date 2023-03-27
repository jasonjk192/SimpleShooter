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
#include "Entities/HealthPickupEntity.h"

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

	BaseEntity* GetNearestEntity(BaseEntity* anEntity)
	{
		float nearestDistance = 9999.f;
		BaseEntity* nearestEntity = nullptr;
		for (auto entity : worldEntities)
		{
			if (entity == anEntity) continue;
			if (float distance = SDLMaths::Distance(anEntity->GetPosition(), entity->GetPosition()) < nearestDistance)
			{
				nearestDistance = distance;
				nearestEntity = entity;
			}
		}
		return nearestEntity;
	}

	BaseEntity* GetPlayerShipEntity() { return worldEntities[0]; }

private:
	void CheckPlayerStatus();
	void SpawnEnemyEntities();
	void SpawnPickupEntities();
	void CheckCollisions();
	void DespawnEntities();
	void DrawUI();

	StateMachine* myStateMachine;
	Drawer* myDrawer;

	BackgroundAsset* myBackgroundAsset;
	MiscAsset* myMiscAsset;
	UIAsset* myUIAsset;

	std::vector<BaseEntity*> worldEntities;
	std::vector<BaseEntity*> newEntities;

	float myEnemySpawnerCooldown = 5.f;
	float currentEnemySpawnerCooldown = 0.f;

	float myPickupSpawnerCooldown = 30.f;
	float currentPickupSpawnerCooldown = 0.f;

	SDL_Rect worldBoundary;

	float scrollHorizontal = 0;
};

#endif // WORLD_H