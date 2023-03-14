#include "Entities/BaseEntity.h"

BaseEntity::BaseEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer):
	myPosition(aPosition),
	myDrawer(aDrawer),
	myTexture(aTexture),
	myName("BaseEntity")
{}

BaseEntity::~BaseEntity(void)
{
}

void BaseEntity::Draw()
{
	myDrawer->Draw(myTexture, myPosition.x - myTexture->GetSize()->x/2, myPosition.y - myTexture->GetSize()->y / 2);
}