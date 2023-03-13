#include "Entities/BaseEntity.h"

BaseEntity::BaseEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer):
	myPosition(aPosition),
	myDrawer(aDrawer),
	myTexture(aTexture),
	myDrawRegion(nullptr)
{}

BaseEntity::~BaseEntity(void)
{
}

void BaseEntity::Draw()
{
	if (myDrawRegion == nullptr)
		myDrawer->Draw(myTexture, myPosition.x, myPosition.y);
	else
		myDrawer->Draw(myTexture, myDrawRegion, new SDL_Rect{ (int)myPosition.x, (int)myPosition.y,myDrawRegion->w,myDrawRegion->h});
}