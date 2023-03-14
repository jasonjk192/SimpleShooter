#include "Entities/StartStateShipEntity.h"

StartStateShipEntity::StartStateShipEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer):
	AIShipEntity(aPosition, aTexture, aDrawer)
{
	myTree = new BehaviourTree();
	followCursorSequence.addChild(&PickDestination);
	followCursorSequence.addChild(&MoveToDestination);
	myTree->setRootChild(&followCursorSequence);
	myName = "AIShipEntity";
}

StartStateShipEntity::~StartStateShipEntity(void)
{
}

// ---------------- //
// Static functions //
// ---------------- //

void StartStateShipEntity::Pick(float aTime, void* ship)
{
	StartStateShipEntity* myShip = (StartStateShipEntity*)ship;
	int x, y;
	SDL_GetMouseState(&x, &y);
	myShip->SetDestination({ (float)x,(float)y });
}

void StartStateShipEntity::MoveForce(float aTime, void* ship)
{
	StartStateShipEntity* myShip = (StartStateShipEntity*)ship;
	if (SDLMaths::Distance(myShip->myPosition, myShip->myDestination) < 8.f)
		myShip->hasReachedDestination = true;

	if (!myShip->hasReachedDestination)
	{
		myShip->myDirection = SDLMaths::Normalize(SDLMaths::Direction(myShip->myPosition, myShip->myDestination));
		myShip->AddForce(myShip->myDirection);
		myShip->myAcceleration = SDLMaths::ClampMagnitude(myShip->myAcceleration, myShip->myMaxAcceleration);
	}
	myShip->myVelocity = { myShip->myVelocity.x + aTime * myShip->myAcceleration.x, myShip->myVelocity.y + aTime * myShip->myAcceleration.y };
	myShip->myVelocity = SDLMaths::ClampMagnitude(myShip->myVelocity, myShip->myMaxSpeed);
	myShip->myPosition = { myShip->myPosition.x + aTime * myShip->myVelocity.x * myShip->myMoveSpeedMult , myShip->myPosition.y + aTime * myShip->myVelocity.y * myShip->myMoveSpeedMult };
}

void StartStateShipEntity::MoveVel(float aTime, void* ship)
{
	StartStateShipEntity* myShip = (StartStateShipEntity*)ship;
	if (SDLMaths::Distance(myShip->myPosition, myShip->myDestination) < 8.f)
		myShip->hasReachedDestination = true;

	if (!myShip->hasReachedDestination)
	{
		myShip->myDirection = SDLMaths::Normalize(SDLMaths::Direction(myShip->myPosition, myShip->myDestination));
		myShip->myVelocity = { myShip->myVelocity.x + myShip->myDirection.x, myShip->myVelocity.y + myShip->myDirection.y };
		myShip->myVelocity = SDLMaths::ClampMagnitude(myShip->myVelocity, myShip->myMaxSpeed);
		myShip->myPosition = { myShip->myPosition.x + aTime * myShip->myVelocity.x * myShip->myMoveSpeedMult , myShip->myPosition.y + aTime * myShip->myVelocity.y * myShip->myMoveSpeedMult };
	}
}