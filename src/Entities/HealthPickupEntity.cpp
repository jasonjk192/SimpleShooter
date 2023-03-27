#include "Entities/HealthPickupEntity.h"

HealthPickupEntity::HealthPickupEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer, World* aWorld)
	: BaseEntity(aPosition, aTexture, aDrawer)
{}
HealthPickupEntity::~HealthPickupEntity(void)
{}

void HealthPickupEntity::OnCollision(BaseEntity* anEntity)
{
	if (auto playerShip = dynamic_cast<PlayerShipEntity*>(anEntity))
	{
		playerShip->ChangeHealth(1);
		SetMarkForDelete();
	}
}