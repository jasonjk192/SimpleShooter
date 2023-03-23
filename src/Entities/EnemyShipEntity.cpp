#include "Entities/EnemyShipEntity.h"

EnemyShipEntity::EnemyShipEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer, World* aWorld):
	AIShipEntity(aPosition, aTexture, aDrawer),
	myWorld(aWorld)
{
	myTree = new BehaviourTree();
	randomMoveSequence.addChild(&PickRandomDestination);
	randomMoveSequence.addChild(&MoveToDestination);
	myTree->setRootChild(&randomMoveSequence);
}

EnemyShipEntity::~EnemyShipEntity(void)
{
}

bool EnemyShipEntity::HandleEvents(SDL_Event* event)
{
	myTree->handleEvents(event);
	return true;
}


bool EnemyShipEntity::Update(float aTime)
{
	myTree->run(aTime);

	//ParticleSystem::SystemParams* boosterParams = myBooster->GetParams();
	//boosterParams->myPosition = { myPosition.x - myDirection.x * 5, myPosition.y - myDirection.y * 5 };
	//boosterParams->myVelocity = { -myVelocity.x, -myVelocity.y };
	//myBooster->Update(aTime);
	return true;
}

void EnemyShipEntity::Draw()
{
	//ParticleSystem::SystemParams* boosterParams = myBooster->GetParams();
	myDrawer->SetScale(myScale);
	myDrawer->Draw(myTexture, myPosition.x - myTexture->GetSize()->x / 2, myPosition.y - myTexture->GetSize()->y / 2, 90 + SDLMaths::rad2deg(SDLMaths::Angle(myDirection)));
	myDrawer->SetScale(1.f);

	// Debug Rectangle
	// myDrawer->DrawRect(boosterParams->myPosition.x - boosterParams->myTexture->GetSize()->x / 2, boosterParams->myPosition.y - boosterParams->myTexture->GetSize()->y / 2, boosterParams->myTexture->GetSize()->x, boosterParams->myTexture->GetSize()->y);
	//myBooster->Draw();
}

void EnemyShipEntity::Shoot()
{
}


BehaviourTree::NodeStatus EnemyShipEntity::PickRandom(float aTime, void* ship, SDL_Event* event)
{
	EnemyShipEntity* myShip = (EnemyShipEntity*)ship;
	int winW, winH;
	myShip->myDrawer->GetWindowSize(&winW, &winH);
	myShip->SetDestination({ (float)(std::rand() % winW), (float)(std::rand() % winH) });
	return BehaviourTree::NodeStatus::SUCCESS;
}

BehaviourTree::NodeStatus EnemyShipEntity::Move(float aTime, void* ship, SDL_Event* event)
{
	EnemyShipEntity* myShip = (EnemyShipEntity*)ship;

	float distance = SDLMaths::Distance(myShip->myPosition, myShip->myDestination);

	if (distance < 8.f)
	{
		myShip->hasReachedDestination = true;
		return BehaviourTree::NodeStatus::SUCCESS;
	}

	if (!myShip->hasReachedDestination)
	{
		SDL_FPoint newDirection = SDLMaths::Normalize(SDLMaths::Direction(myShip->myPosition, myShip->myDestination));
		myShip->myDirection = SDLMaths::Lerp(myShip->myDirection, newDirection, aTime);
		myShip->myVelocity = { myShip->myVelocity.x + myShip->myDirection.x , myShip->myVelocity.y + myShip->myDirection.y };
		myShip->myVelocity = SDLMaths::ClampMagnitude(myShip->myVelocity, myShip->myMaxSpeed);
		myShip->myPosition = { myShip->myPosition.x + aTime * myShip->myVelocity.x * myShip->myMoveSpeedMult , myShip->myPosition.y + aTime * myShip->myVelocity.y * myShip->myMoveSpeedMult };
	}

	return BehaviourTree::NodeStatus::RUNNING;
}