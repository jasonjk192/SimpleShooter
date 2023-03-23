#include "Entities/BulletEntity.h"

BulletEntity::BulletEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer, World* aWorld) :
	DynamicEntity(aPosition, aTexture, aDrawer),
	myWorld(aWorld),
	myLifetime(1),
	myOwner(nullptr)
{
}

BulletEntity::~BulletEntity(void)
{
}

bool BulletEntity::Update(float aTime)
{
	myDirection = myVelocity;
	myPosition = { myPosition.x + aTime * myVelocity.x * myMoveSpeedMult , myPosition.y + aTime * myVelocity.y * myMoveSpeedMult };

	myLifetime -= aTime;
	if (myLifetime <= 0)
		markForDelete = true;

	return true;
}

void BulletEntity::OnCollision(BaseEntity* anEntity)
{
	if (anEntity == myOwner) return;
	else
	{
		anEntity->SetMarkForDelete();
		SetMarkForDelete();
	}
}
