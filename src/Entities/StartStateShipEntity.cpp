#include "Entities/StartStateShipEntity.h"

StartStateShipEntity::StartStateShipEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer):
	AIShipEntity(aPosition, aTexture, aDrawer)
{
	myTree = new BehaviourTree();
	followCursorSequence.addChild(&PickMouseDestination);
	followCursorSequence.addChild(&MoveToDestination);
	randomMoveSequence.addChild(&PickRandomDestination);
	randomMoveSequence.addChild(&MoveToDestination);
	conditionalMoveSequence.addChild(&followCursorSequence);
	conditionalMoveSequence.addChild(&randomMoveSequence);
	myTree->setRootChild(&conditionalMoveSequence);
	myName = "AIShipEntity";

	ParticleSystem::SystemParams params;
	params.myLifetime = 2;
	params.myMaxParticleCount = 100;
	params.myFrequency = 0.05f;
	params.myPosition = { 0,0 };
	params.myTexture = MiscAsset::GetInstance().GetFlameTexture(0);
	myBooster = new ParticleSystem(aDrawer, params);
}

StartStateShipEntity::~StartStateShipEntity(void)
{
}

bool StartStateShipEntity::HandleEvents(SDL_Event* event)
{
	return myTree->handleEvents(event);
}

bool StartStateShipEntity::Update(float aTime)
{
	myTree->run(aTime);

	ParticleSystem::SystemParams* boosterParams = myBooster->GetParams();
	boosterParams->myPosition = { myPosition.x - myDirection.x * 5, myPosition.y - myDirection.y * 5};
	boosterParams->myVelocity = { -myVelocity.x, -myVelocity.y };
	myBooster->Update(aTime);
	return true;
}

void StartStateShipEntity::Draw()
{
	ParticleSystem::SystemParams* boosterParams = myBooster->GetParams();
	myDrawer->SetScale(myScale);
	myDrawer->Draw(myTexture, myPosition.x - myTexture->GetSize()->x / 2, myPosition.y - myTexture->GetSize()->y / 2, 90 + SDLMaths::rad2deg(SDLMaths::Angle(myDirection)));
	myDrawer->SetScale(1.f);

	// Debug Rectangle
	// myDrawer->DrawRect(boosterParams->myPosition.x - boosterParams->myTexture->GetSize()->x / 2, boosterParams->myPosition.y - boosterParams->myTexture->GetSize()->y / 2, boosterParams->myTexture->GetSize()->x, boosterParams->myTexture->GetSize()->y);
	myBooster->Draw();
}

// ---------------- //
// Static functions //
// ---------------- //

BehaviourTree::NodeStatus StartStateShipEntity::PickMouse(float aTime, void* ship, SDL_Event* event)
{
	StartStateShipEntity* myShip = (StartStateShipEntity*)ship;
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (SDLMaths::Distance(((StartStateShipEntity*)ship)->myPosition, SDL_FPoint { (float)x, (float)y }) > 150.f)
		return BehaviourTree::NodeStatus::FAILED;
	myShip->SetDestination({ (float)x,(float)y });
	return BehaviourTree::NodeStatus::SUCCESS;
}

BehaviourTree::NodeStatus StartStateShipEntity::PickRandom(float aTime, void* ship, SDL_Event* event)
{
	StartStateShipEntity* myShip = (StartStateShipEntity*)ship;
	int winW, winH;
	myShip->myDrawer->GetWindowSize(&winW, &winH);
	myShip->SetDestination({ (float)(std::rand() % winW), (float)(std::rand() % winH) });
	return BehaviourTree::NodeStatus::SUCCESS;
}

BehaviourTree::NodeStatus StartStateShipEntity::MoveForce(float aTime, void* ship, SDL_Event* event)
{
	StartStateShipEntity* myShip = (StartStateShipEntity*)ship;
	
	if (SDLMaths::Distance(myShip->myPosition, myShip->myDestination) < 8.f)
	{
		myShip->hasReachedDestination = true;
		return BehaviourTree::NodeStatus::SUCCESS;
	}

	if (!myShip->hasReachedDestination)
	{
		myShip->myDirection = SDLMaths::Normalize(SDLMaths::Direction(myShip->myPosition, myShip->myDestination));
		myShip->AddForce(myShip->myDirection);
		myShip->myAcceleration = SDLMaths::ClampMagnitude(myShip->myAcceleration, myShip->myMaxAcceleration);
	}
	myShip->myVelocity = { myShip->myVelocity.x + aTime * myShip->myAcceleration.x, myShip->myVelocity.y + aTime * myShip->myAcceleration.y };
	myShip->myVelocity = SDLMaths::ClampMagnitude(myShip->myVelocity, myShip->myMaxSpeed);
	myShip->myPosition = { myShip->myPosition.x + aTime * myShip->myVelocity.x * myShip->myMoveSpeedMult , myShip->myPosition.y + aTime * myShip->myVelocity.y * myShip->myMoveSpeedMult };

	return BehaviourTree::NodeStatus::RUNNING;
}

BehaviourTree::NodeStatus StartStateShipEntity::MoveVel(float aTime, void* ship, SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_MOUSEMOTION: int x, y; SDL_GetMouseState(&x, &y);
		if (SDLMaths::Distance(((StartStateShipEntity*)ship)->myPosition, SDL_FPoint { (float)x, (float)y }) <= 150.f)  return BehaviourTree::NodeStatus::FAILED;
	}

	StartStateShipEntity* myShip = (StartStateShipEntity*)ship;

	float distance = SDLMaths::Distance(myShip->myPosition, myShip->myDestination);

	if (distance < 8.f)
	{
		myShip->hasReachedDestination = true;
		return BehaviourTree::NodeStatus::SUCCESS;
	}

	if (!myShip->hasReachedDestination)
	{
		myShip->myDirection = SDLMaths::Normalize(SDLMaths::Direction(myShip->myPosition, myShip->myDestination));
		myShip->myVelocity = { myShip->myVelocity.x + myShip->myDirection.x , myShip->myVelocity.y + myShip->myDirection.y };
		myShip->myVelocity = SDLMaths::ClampMagnitude(myShip->myVelocity, myShip->myMaxSpeed);
		myShip->myPosition = { myShip->myPosition.x + aTime * myShip->myVelocity.x * myShip->myMoveSpeedMult , myShip->myPosition.y + aTime * myShip->myVelocity.y * myShip->myMoveSpeedMult };
	}

	return BehaviourTree::NodeStatus::RUNNING;
}