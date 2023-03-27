#include "World.h"

World::World(StateMachine* aStateMachine, Drawer* aDrawer):
	myStateMachine(aStateMachine),
	myDrawer(aDrawer)
{
	myBackgroundAsset = &BackgroundAsset::GetInstance();
	myUIAsset = &UIAsset::GetInstance();
	myMiscAsset = &MiscAsset::GetInstance();

	int winW, winH;
	myDrawer->GetWindowSize(&winW, &winH);

	PlayerShipEntity* playerShip = new PlayerShipEntity({ winW/2.f, winH/2.f }, ShipAsset::GetInstance().GetPlayerTexture(4), myDrawer, this);
	playerShip->SetMaxSpeed(300);
	playerShip->SetMaxAcceleration(10);
	playerShip->SetScale(2.f);
	worldEntities.push_back(playerShip);

	worldBoundary = {0,0,winW,winH};
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
	currentPickupSpawnerCooldown -= aTime;
	if (currentEnemySpawnerCooldown <= 0)
	{
		currentEnemySpawnerCooldown = myEnemySpawnerCooldown;
		SpawnEnemyEntities();
	}

	if (currentPickupSpawnerCooldown <= 0)
	{
		currentPickupSpawnerCooldown = myPickupSpawnerCooldown;
		SpawnPickupEntities();
	}

	for (auto entity : worldEntities)
	{
		entity->Update(aTime);
		SDL_FPoint pos = entity->GetPosition();
		if (PlayerShipEntity* ship = dynamic_cast<PlayerShipEntity*>(entity))
		{
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
	int bgSizeW = myBackgroundAsset->GetBackgroundTexture(4)->GetSize()->x;
	int bgSizeH = myBackgroundAsset->GetBackgroundTexture(4)->GetSize()->y;
	for (int i = 0; i < 10; i++)
		myDrawer->Draw(myBackgroundAsset->GetBackgroundTexture(4), scrollHorizontal + i * bgSizeW, 0);
	for (int i = 0; i < 10; i++)
		myDrawer->Draw(myBackgroundAsset->GetBackgroundTexture(4), scrollHorizontal + i * bgSizeW, bgSizeH);

	for (auto entity : worldEntities)
		entity->Draw();

	myDrawer->SetScale(5);
	for(int i=0;i<5;i++)
		myDrawer->Draw(myBackgroundAsset->GetBackgroundTexture(4), scrollHorizontal*5 + i*bgSizeW*5, 0);
	myDrawer->SetScale(1);
	DrawUI();

	return true;
}

void World::CheckPlayerStatus()
{
	auto playerShip = dynamic_cast<PlayerShipEntity*>(worldEntities[0]);
	if (!playerShip)
		myStateMachine->Transition(new TransitionState(myStateMachine, myDrawer), "GameLost", new int(0));
	else
	{
		if(playerShip->GetHealth()==0)
			myStateMachine->Transition(new TransitionState(myStateMachine, myDrawer), "GameLost", new int(playerShip->GetScore()));
	}
}

void World::SpawnEnemyEntities()
{
	SDL_FPoint spawnPoint{ 50,50 };
	auto enemy = SpawnEntity<EnemyShipEntity>(spawnPoint, ShipAsset::GetInstance().GetEnemyTexture(0));
	enemy->SetMaxSpeed(30);
	enemy->SetMaxAcceleration(10);
	enemy->SetScale(2.f);
}

void World::SpawnPickupEntities()
{
	SDL_FPoint spawnPoint{ 150,50 };
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
	int winW, winH;
	myDrawer->GetWindowSize(&winW, &winH);
	
	if(PlayerShipEntity* playerShip = dynamic_cast<PlayerShipEntity*>(worldEntities[0]))
	{
		myDrawer->SetTextureColorMod(myMiscAsset->GetIconTexture(2), 255, 0, 0);
		for (int i = 0; i < playerShip->GetHealth(); i++)
			myDrawer->Draw(myMiscAsset->GetIconTexture(2), winW - (i * 8) - (i * 4) - 20, 20);
		myDrawer->SetTextureColorMod(myMiscAsset->GetIconTexture(2), 255, 255, 255);
		std::string scoreText = "Score: " + std::to_string(playerShip->GetScore());

		myDrawer->SetColor(255, 255, 255, 255);
		myDrawer->DrawText(scoreText.c_str(), ".\\data\\fonts\\PublicPixel-z84yD.ttf", 20, 20, 8);
	}
}