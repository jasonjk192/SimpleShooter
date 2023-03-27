#ifndef HEALTHPICKUPENTITY_H
#define HEALTHPICKUPENTITY_H

#include "BaseEntity.h"
#include "PlayerShipEntity.h"

class HealthPickupEntity : public BaseEntity
{
public:
	HealthPickupEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer, World* aWorld);
	~HealthPickupEntity(void);

	void OnCollision(BaseEntity* anEntity);
};

#endif // HEALTHPICKUPENTITY_H