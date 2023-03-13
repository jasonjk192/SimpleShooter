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
		SDL_FPoint direction = SDLMaths::Direction(myDestination, myPosition);
		if (SDLMaths::Magnitude(myVelocity) < myMaxSpeed)
			AddForce(SDLMaths::Normalize(direction));
	}

	myPosition = { myPosition.x + aTime * myVelocity.x * myMoveSpeedMult , myPosition.y + aTime * myVelocity.y * myMoveSpeedMult };

	if (SDLMaths::Magnitude(myVelocity) < myMaxSpeed)
		myVelocity = { myVelocity.x + aTime * myAcceleration.x, myVelocity.y + aTime * myAcceleration.y };

	std::string s = hasReachedDestination ? "Yes" : "No";
	std::cout << SDLMaths::Magnitude(myVelocity) << ", " << s.c_str()<< ", (" << myPosition.x << ", " << myPosition.y << ")" << std::endl;

	return true;
}