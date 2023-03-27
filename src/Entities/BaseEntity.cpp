#include "Entities/BaseEntity.h"

BaseEntity::BaseEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer):
	myPosition(aPosition),
	myDrawer(aDrawer),
	myTexture(aTexture),
	myName("BaseEntity"),
	myScale(1.f),
	markForDelete(false)
{}

BaseEntity::~BaseEntity(void)
{
}

void BaseEntity::Draw()
{
	myDrawer->SetScale(myScale);
	myDrawer->Draw(myTexture, myPosition.x - myTexture->GetSize()->x/2, myPosition.y - myTexture->GetSize()->y / 2);
	myDrawer->SetScale(1.f);
}