#include "Entities/DynamicEntity.h"

DynamicEntity::DynamicEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer):
	BaseEntity(aPosition, aTexture, aDrawer),
	myDirection({ 0,0 }),
	myVelocity({0,0}),
	myAcceleration({0,0}),
	myMoveSpeedMult(1.f),
	myMass(1.f),
	myMaxSpeed(0.f),
	myMaxAcceleration(0.f)
{
	myName = "DynamicEntity";
}

DynamicEntity::~DynamicEntity(void)
{
}

