#include "Entities/AllyShipEntity.h"

AllyShipEntity::AllyShipEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer, World* aWorld):
	AIShipEntity(aPosition, aTexture, aDrawer),
	myWorld(aWorld)
{
	myName = "AllyShip";
	myTree = new BehaviourTree();
	randomMoveSequence.addChild(&PickRandomDestination);
	randomMoveSequence.addChild(&MoveToDestination);
	followAndShootSequence.addChild(&GetNearbyShip);
	followAndShootSequence.addChild(&MoveToDestination);
	followAndShootSequence.addChild(&ShootAtShip);
	followOrRandomSelector.addChild(&followAndShootSequence);
	followOrRandomSelector.addChild(&randomMoveSequence);
	myTree->setRootChild(&followOrRandomSelector);
	hasReachedDestination = true;

	myShootCooldown = 0.5f;
	currentShootCooldown = 0.f;
}

AllyShipEntity::~AllyShipEntity(void)
{
}

bool AllyShipEntity::HandleEvents(SDL_Event* event)
{
	myTree->handleEvents(event);
	return true;
}


bool AllyShipEntity::Update(float aTime)
{
	BaseEntity* nearestEntity = myWorld->GetNearestEntity<EnemyShipEntity*>(this);
	currentShootCooldown -= aTime;
	currentShootCooldown = std::max(currentShootCooldown, 0.f);
	myTree->run(aTime);

	//ParticleSystem::SystemParams* boosterParams = myBooster->GetParams();
	//boosterParams->myPosition = { myPosition.x - myDirection.x * 5, myPosition.y - myDirection.y * 5 };
	//boosterParams->myVelocity = { -myVelocity.x, -myVelocity.y };
	//myBooster->Update(aTime);
	return true;
}

void AllyShipEntity::Draw()
{
	//ParticleSystem::SystemParams* boosterParams = myBooster->GetParams();
	myDrawer->SetScale(myScale);
	myDrawer->Draw(myTexture, myPosition.x - myTexture->GetSize()->x / 2, myPosition.y - myTexture->GetSize()->y / 2, 90 + SDLMaths::rad2deg(SDLMaths::Angle(myDirection)));
	myDrawer->SetScale(1.f);

	// Debug Rectangle
	// myDrawer->DrawRect(boosterParams->myPosition.x - boosterParams->myTexture->GetSize()->x / 2, boosterParams->myPosition.y - boosterParams->myTexture->GetSize()->y / 2, boosterParams->myTexture->GetSize()->x, boosterParams->myTexture->GetSize()->y);
	//myBooster->Draw();
}

void AllyShipEntity::OnCollision(BaseEntity* anEntity)
{
	if (EnemyShipEntity* enemyShip = dynamic_cast<EnemyShipEntity*>(anEntity))
	{
		ChangeHealth(-1);
		enemyShip->ChangeHealth(-1);
	}
}

BehaviourTree::NodeStatus AllyShipEntity::PickRandom(float aTime, void* ship, SDL_Event* event)
{
	AllyShipEntity* myShip = (AllyShipEntity*)ship;
	if(myShip->hasReachedDestination)
	{
		SDL_Point windowSize = myShip->myDrawer->GetWindowSize();
		myShip->SetDestination({ (float)(std::rand() % windowSize.x), (float)(std::rand() % windowSize.y) });
	}
	return BehaviourTree::NodeStatus::SUCCESS;
}

BehaviourTree::NodeStatus AllyShipEntity::Nearby(float aTime, void* ship, SDL_Event* event)
{
	AllyShipEntity* myShip = (AllyShipEntity*)ship;
	BaseEntity* nearestEntity = myShip->myWorld->GetNearestEntity<EnemyShipEntity*>(myShip);
	if (dynamic_cast<EnemyShipEntity*>(nearestEntity))
	{
		float distance = SDLMaths::Distance(myShip->myPosition, nearestEntity->GetPosition());
		if(distance < 250.f)
		{
			myShip->SetDestination(nearestEntity->GetPosition());
			return BehaviourTree::NodeStatus::SUCCESS;
		}
	}
	return BehaviourTree::NodeStatus::FAILED;
}

BehaviourTree::NodeStatus AllyShipEntity::Move(float aTime, void* ship, SDL_Event* event)
{
	AllyShipEntity* myShip = (AllyShipEntity*)ship;

	float distance = SDLMaths::Distance(myShip->myPosition, myShip->myDestination);

	if (distance < 8.f)
		myShip->hasReachedDestination = true;

	if (!myShip->hasReachedDestination)
	{
		SDL_FPoint newDirection = SDLMaths::Normalize(SDLMaths::Direction(myShip->myPosition, myShip->myDestination));
		myShip->myDirection = SDLMaths::Lerp(myShip->myDirection, newDirection, aTime);
		myShip->myVelocity = { myShip->myVelocity.x + myShip->myDirection.x , myShip->myVelocity.y + myShip->myDirection.y };
		myShip->myVelocity = SDLMaths::ClampMagnitude(myShip->myVelocity, myShip->myMaxSpeed);
		myShip->myPosition = { myShip->myPosition.x + aTime * myShip->myVelocity.x * myShip->myMoveSpeedMult , myShip->myPosition.y + aTime * myShip->myVelocity.y * myShip->myMoveSpeedMult };
	}

	return BehaviourTree::NodeStatus::SUCCESS;
}

BehaviourTree::NodeStatus AllyShipEntity::Follow(float aTime, void* ship, SDL_Event* event)
{
	AllyShipEntity* myShip = (AllyShipEntity*)ship;
	BaseEntity* nearestEntity = myShip->myWorld->GetNearestEntity<EnemyShipEntity*>(myShip);
	if(dynamic_cast<EnemyShipEntity*>(nearestEntity))
		myShip->SetDestination(nearestEntity->GetPosition());
	return BehaviourTree::NodeStatus::SUCCESS;
}

BehaviourTree::NodeStatus AllyShipEntity::Shoot(float aTime, void* ship, SDL_Event* event)
{	
	AllyShipEntity* myShip = (AllyShipEntity*)ship;
	float angle = SDLMaths::rad2deg(SDLMaths::Angle(SDLMaths::Direction(myShip->myPosition, myShip->myDestination), myShip->myDirection));
	if(angle <= 15 && angle >= -15)
	{
		if (myShip->currentShootCooldown <= 0.f)
		{
			myShip->currentShootCooldown = myShip->myShootCooldown;
			auto bullet = myShip->myWorld->SpawnEntity<FriendlyBulletEntity>(myShip->myPosition, ProjectileAsset::GetInstance().GetProjectileTexture(7));
			bullet->SetOwner(myShip);
			bullet->SetMoveSpeedMult(1000);
			bullet->SetVelocity(myShip->myDirection);
		}
	}
	return BehaviourTree::NodeStatus::SUCCESS;
}