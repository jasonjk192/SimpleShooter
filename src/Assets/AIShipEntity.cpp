#include "Entities/AIShipEntity.h"

#include <iostream>

AIShipEntity::AIShipEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer):
	DynamicEntity(aPosition, aTexture, aDrawer),
	myDestination({0,0}),
	hasReachedDestination(true)
{
	followCursorSequence.addChild(&PickDestination);
	followCursorSequence.addChild(&MoveToDestination);
	myTree.setRootChild(&followCursorSequence);
	myName = "AIShipEntity";
}

AIShipEntity::~AIShipEntity(void)
{
}

bool AIShipEntity::Update(float aTime)
{
	myTree.run(aTime);
	return true;
}

void AIShipEntity::Draw()
{
	myDrawer->Draw(myTexture, myPosition.x - myTexture->GetSize()->x / 2, myPosition.y - myTexture->GetSize()->y / 2, 90 + SDLMaths::rad2deg(SDLMaths::Angle(myDirection)));
}

// ---------------- //
// Static functions //
// ---------------- //

void AIShipEntity::Pick(float aTime, void* ship)
{
	AIShipEntity* myShip = (AIShipEntity*)ship;
	int x, y;
	SDL_GetMouseState(&x, &y);
	myShip->SetDestination({ (float)x,(float)y });
}

void AIShipEntity::Move(float aTime, void* ship)
{
	AIShipEntity* myShip = (AIShipEntity*)ship;
	if (SDLMaths::Distance(myShip->myPosition, myShip->myDestination) < 8.f)
		myShip->hasReachedDestination = true;

	if (!myShip->hasReachedDestination)
	{
		myShip->myDirection = SDLMaths::Direction(myShip->myPosition, myShip->myDestination);
		myShip->AddForce(SDLMaths::Normalize(myShip->myDirection));
		myShip->myAcceleration = SDLMaths::ClampMagnitude(myShip->myAcceleration, myShip->myMaxAcceleration);
	}

	myShip->myPosition = { myShip->myPosition.x + aTime * myShip->myVelocity.x * myShip->myMoveSpeedMult , myShip->myPosition.y + aTime * myShip->myVelocity.y * myShip->myMoveSpeedMult };
	myShip->myVelocity = { myShip->myVelocity.x + aTime * myShip->myAcceleration.x, myShip->myVelocity.y + aTime * myShip->myAcceleration.y };
	myShip->myVelocity = SDLMaths::ClampMagnitude(myShip->myVelocity, myShip->myMaxSpeed);
}