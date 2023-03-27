#include "Entities/AIShipEntity.h"

#include <iostream>

AIShipEntity::AIShipEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer) :
	GameCharacterEntity(aPosition, aTexture, aDrawer),
	myDestination({ 0,0 }),
	hasReachedDestination(true),
	myTree(nullptr)
{
}

AIShipEntity::~AIShipEntity(void)
{
}

bool AIShipEntity::Update(float aTime)
{
	myTree->run(aTime);
	return true;
}

void AIShipEntity::Draw()
{
	myDrawer->SetScale(myScale);
	myDrawer->Draw(myTexture, myPosition.x - myTexture->GetSize()->x / 2, myPosition.y - myTexture->GetSize()->y / 2, 90 + SDLMaths::rad2deg(SDLMaths::Angle(myDirection)));
	myDrawer->SetScale(1.f);
}