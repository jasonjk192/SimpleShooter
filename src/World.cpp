#include "World.h"

World::World(StateMachine* aStateMachine, Drawer* aDrawer):
	myStateMachine(aStateMachine),
	myDrawer(aDrawer)
{
	myBackgroundAsset = &BackgroundAsset::GetInstance();
	myUIAsset = &UIAsset::GetInstance();
	myMiscAsset = &MiscAsset::GetInstance();
	windowSize = myDrawer->GetWindowSize();

	PlayerShipEntity* playerShip = new PlayerShipEntity({ windowSize.x/2.f, windowSize .y/2.f }, ShipAsset::GetInstance().GetPlayerTexture(4), myDrawer, this);
	playerShip->SetMaxSpeed(300);
	playerShip->SetMaxAcceleration(10);
	playerShip->SetScale(2.f);
	worldEntities.push_back(playerShip);

	worldBoundary = {0, 0, windowSize.x, windowSize.y};
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
	currentEnemySpawnerCooldown -= aTime;
	currentAllySpawnerCooldown -= aTime;
	currentPickupSpawnerCooldown -= aTime;

	if (currentEnemySpawnerCooldown <= 0)
	{
		currentEnemySpawnerCooldown = myEnemySpawnerCooldown;
		SpawnEnemyEntities();
	}
	if (currentAllySpawnerCooldown <= 0)
	{
		currentAllySpawnerCooldown = myAllySpawnerCooldown;
		SpawnAllyEntities();
	}
	if (currentPickupSpawnerCooldown <= 0)
	{
		currentPickupSpawnerCooldown = myPickupSpawnerCooldown;
		SpawnPickupEntities();
	}

	for (auto entity : worldEntities)
	{
		entity->Update(aTime);
		if (PlayerShipEntity* ship = dynamic_cast<PlayerShipEntity*>(entity))
		{
			SDL_FPoint pos = ship->GetPosition();
			SDL_FPoint vel = ship->GetVelocity();
			if (pos.x < worldBoundary.x)
			{
				pos.x = worldBoundary.x;
				vel.x = -vel.x;
				ship->SetPosition(pos);
				ship->SetVelocity(vel);
			}
			else if (pos.x > worldBoundary.w)
			{
				pos.x = worldBoundary.w;
				vel.x = -vel.x;
				ship->SetPosition(pos);
				ship->SetVelocity(vel);
			}
			if (pos.y < worldBoundary.y)
			{
				pos.y = worldBoundary.y;
				vel.y = -vel.y;
				ship->SetPosition(pos);
				ship->SetVelocity(vel);
				
			}
			else if (pos.y > worldBoundary.h)
			{
				pos.y = worldBoundary.h;
				vel.y = -vel.y;
				ship->SetPosition(pos);
				ship->SetVelocity(vel);
			}
		}
		
	}
	
	CheckCollisions();

	CheckPlayerStatus();

	DespawnEntities();

	for (auto entity : newEntities)
		worldEntities.push_back(entity);
	newEntities.clear();

	scrollHorizontal -= aTime*10;
		
	return true;
}

bool World::Draw()
{
	DrawBackground();

	for (auto entity : worldEntities)
		entity->Draw();

	/*myDrawer->SetScale(5);
	for(int i=0;i<5;i++)
		myDrawer->Draw(myBackgroundAsset->GetBackgroundTexture(4), scrollHorizontal*5 + i * bgSize.x * 5, 0);
	myDrawer->SetScale(1);*/
	DrawForeground();
	
	DrawUI();

	return true;
}

void World::CheckPlayerStatus()
{
	auto playerShip = dynamic_cast<PlayerShipEntity*>(worldEntities[0]);
	if (!playerShip)
		myStateMachine->Push(new TransitionState(myStateMachine, myDrawer, new GameLostState(myStateMachine, myDrawer)), new int(0) );
	else
	{
		if(playerShip->GetHealth()==0)
			myStateMachine->Push(new TransitionState(myStateMachine, myDrawer, new GameLostState(myStateMachine, myDrawer)), new int(playerShip->GetScore()) );
	}
}

void World::SpawnEnemyEntities()
{
	SDL_FPoint spawnPoint{ (float)(std::rand() % windowSize.x), (float)(std::rand() % windowSize.y) };
	auto enemy = SpawnEntity<EnemyShipEntity>(spawnPoint, ShipAsset::GetInstance().GetEnemyTexture(0));
	enemy->SetMaxSpeed(30);
	enemy->SetMaxAcceleration(10);
	enemy->SetScale(2.f);
}

void World::SpawnAllyEntities()
{
	SDL_FPoint spawnPoint{ (float)(std::rand() % windowSize.x), (float)(std::rand() % windowSize.y) };
	auto ally = SpawnEntity<AllyShipEntity>(spawnPoint, ShipAsset::GetInstance().GetPlayerTexture(7));
	ally->SetMaxSpeed(30);
	ally->SetMaxAcceleration(10);
	ally->SetScale(2.f);
}

void World::SpawnPickupEntities()
{
	SDL_FPoint spawnPoint{ (float)(std::rand() % windowSize.x), (float)(std::rand() % windowSize.y) };
	auto health = SpawnEntity<HealthPickupEntity>(spawnPoint, MiscAsset::GetInstance().GetIconTexture(2));
}

void World::CheckCollisions()
{
	for (int i = 0; i < worldEntities.size() - 1; i++)
	{
		for (int j = i + 1; j < worldEntities.size(); j++)
		{
			if (worldEntities[i]->CollidesWith(worldEntities[j]))
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

void World::DrawUI()
{
	if(PlayerShipEntity* playerShip = dynamic_cast<PlayerShipEntity*>(worldEntities[0]))
	{
		myDrawer->SetTextureColorMod(myMiscAsset->GetIconTexture(2), 255, 0, 0);
		for (int i = 0; i < playerShip->GetHealth(); i++)
			myDrawer->Draw(myMiscAsset->GetIconTexture(2), windowSize.x - (i * 8) - (i * 4) - 20, 20);
		myDrawer->SetTextureColorMod(myMiscAsset->GetIconTexture(2), 255, 255, 255);
		std::string scoreText = "Score: " + std::to_string(playerShip->GetScore());

		myDrawer->SetColor(255, 255, 255, 255);
		myDrawer->DrawText(scoreText.c_str(), ".\\data\\fonts\\PublicPixel-z84yD.ttf", 20, 20, 8);
	}
}

void World::DrawBackground()
{
	SDL_FPoint offset{ scrollHorizontal ,0 };
	SDL_Point* backgroundSize = myBackgroundAsset->GetBackgroundTexture(4)->GetSize();
	Texture* background = myBackgroundAsset->GetBackgroundTexture(4);

	// Main area (Bottom right)
	for (int x = offset.x; x < windowSize.x; x += backgroundSize->x)
	{
		for (int y = offset.y; y < windowSize.y; y += backgroundSize->y)
		{
			myDrawer->Draw(background, x, y);
		}
	}

	// Top Left
	for (int x = offset.x - backgroundSize->x; x >= -backgroundSize->x; x -= backgroundSize->x)
	{
		for (int y = offset.y - backgroundSize->y; y >= -backgroundSize->y; y -= backgroundSize->y)
		{
			myDrawer->Draw(background, x, y);
		}
	}

	// Bottom Left
	for (int x = offset.x - backgroundSize->x; x >= -backgroundSize->x; x -= backgroundSize->x)
	{
		for (int y = offset.y; y < windowSize.y; y += backgroundSize->y)
		{
			myDrawer->Draw(background, x, y);
		}
	}

	// Top Right
	for (int x = offset.x; x < windowSize.x; x += backgroundSize->x)
	{
		for (int y = offset.y - backgroundSize->y; y >= -backgroundSize->y; y -= backgroundSize->y)
		{
			myDrawer->Draw(background, x, y);
		}
	}
}

void World::DrawForeground()
{
	SDL_FPoint offset{ scrollHorizontal * 2.5f, 0 };
	SDL_Point* backgroundSize = myBackgroundAsset->GetBackgroundTexture(4)->GetSize();
	Texture* background = myBackgroundAsset->GetBackgroundTexture(4);

	myDrawer->SetScale(5);

	// Main area (Bottom right)
	for (int x = offset.x; x < windowSize.x; x += backgroundSize->x * 5)
	{
		for (int y = offset.y; y < windowSize.y; y += backgroundSize->y * 5)
		{
			myDrawer->Draw(background, x, y);
		}
	}

	myDrawer->SetScale(1);
}