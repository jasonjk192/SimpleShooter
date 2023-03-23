#include "World.h"

World::World(StateMachine* aStateMachine, Drawer* aDrawer):
	myStateMachine(aStateMachine),
	myDrawer(aDrawer)
{
	myBackgroundAsset = &BackgroundAsset::GetInstance();
	myUIAsset = &UIAsset::GetInstance();
	myMiscAsset = &MiscAsset::GetInstance();

	PlayerShipEntity* playerShip = new PlayerShipEntity({ 0.f, 0.f }, ShipAsset::GetInstance().GetPlayerTexture(4), myDrawer, this);
	playerShip->SetMaxSpeed(30);
	playerShip->SetMaxAcceleration(10);
	playerShip->SetScale(2.f);
	worldEntities.push_back(playerShip);
}

World::~World(void)
{
	for (int i = worldEntities.size() - 1; i >= 0; i--)
		delete worldEntities[i];
	for (int i = newEntities.size() - 1; i >= 0; i--)
		delete newEntities[i];
	worldEntities.clear();
	newEntities.clear();
}

bool World::HandleEvents(SDL_Event* event)
{
	for (auto entity : worldEntities)
		entity->HandleEvents(event);
	return true;
}

bool World::Update(float aTime)
{
	std::cout << worldEntities.size() << std::endl;

	currentEnemySpawnerCooldown -= aTime;
	if (currentEnemySpawnerCooldown <= 0)
	{
		currentEnemySpawnerCooldown = myEnemySpawnerCooldown;
		SDL_FPoint spawnPoint{ 50,50 };
		auto enemy = SpawnEntity<EnemyShipEntity>(spawnPoint, ShipAsset::GetInstance().GetEnemyTexture(0));
		enemy->SetMaxSpeed(30);
		enemy->SetMaxAcceleration(10);
		enemy->SetScale(2.f);
	}

	for (auto entity : worldEntities)
		entity->Update(aTime);

	CheckCollisions();

	DespawnEntities();

	for (auto entity : newEntities)
		worldEntities.push_back(entity);
	newEntities.clear();
		
	return true;
}

bool World::Draw()
{
	for (auto entity : worldEntities)
		entity->Draw();
	return true;
}

void World::CheckCollisions()
{
	for (int i = 0; i < worldEntities.size() - 1; i++)
	{
		for (int j = i + 1; j < worldEntities.size(); j++)
		{
			if (SDLMaths::Distance(worldEntities[i]->GetPosition(), worldEntities[j]->GetPosition()) < 8.f)
			{
				worldEntities[i]->OnCollision(worldEntities[j]);
				worldEntities[j]->OnCollision(worldEntities[i]);
			}
		}
	}
}

void World::DespawnEntities()
{
	int myWorldEntitiesCount = worldEntities.size();
	for (int i = 0; i < myWorldEntitiesCount; i++)
	{
		if(worldEntities[i]->IsMarkedForDelete())
		{
			BaseEntity* tempEntity = std::move(worldEntities[--myWorldEntitiesCount]);
			worldEntities[myWorldEntitiesCount] = std::move(worldEntities[i]);
			worldEntities[i] = std::move(tempEntity);
			delete worldEntities[myWorldEntitiesCount];
		}
	}
	worldEntities.resize(myWorldEntitiesCount);
}