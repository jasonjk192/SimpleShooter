#include "Entities/AIShipEntity.h"

#include <iostream>

AIShipEntity::AIShipEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer):
	DynamicEntity(aPosition, aTexture, aDrawer),
	myDestination({0,0}),
	hasReachedDestination(true)
{
}

AIShipEntity::~AIShipEntity(void)
{
}

bool AIShipEntity::Update(float aTime)
{
	if (SDLMaths::Distance(myPosition, myDestination) < 1.f)
		hasReachedDestination = true;

	if (!hasReachedDestination)
	{
		myDirection = SDLMaths::Direction(myDestination, myPosition);
		AddForce(SDLMaths::Normalize(myDirection));
		myAcceleration = SDLMaths::ClampMagnitude(myAcceleration, myMaxAcceleration);
	}

	myPosition = { myPosition.x + aTime * myVelocity.x * myMoveSpeedMult , myPosition.y + aTime * myVelocity.y * myMoveSpeedMult };
	myVelocity = { myVelocity.x + aTime * myAcceleration.x, myVelocity.y + aTime * myAcceleration.y };
	myVelocity = SDLMaths::ClampMagnitude(myVelocity, myMaxSpeed);

	return true;
}

void AIShipEntity::Draw()
{
	myDrawer->Draw(myTexture, myPosition.x - myTexture->GetSize()->x / 2, myPosition.y - myTexture->GetSize()->y / 2, 90 + SDLMaths::rad2deg(SDLMaths::Angle(myDirection)));
}