#ifndef AISHIPENTITY_H
#define AISHIPENTITY_H

#include "Assets/SDLMaths.h"

#include "DynamicEntity.h"

class AIShipEntity : public DynamicEntity
{
public:
	AIShipEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer);
	~AIShipEntity(void);

	bool Update(float aTime);
	void SetDestination(SDL_FPoint dstPoint) { myDestination = dstPoint; hasReachedDestination = false; }
	
	bool HasReachedDestination() { return hasReachedDestination; }

protected:

	SDL_FPoint myDestination;

	bool hasReachedDestination;

};

#endif // AISHIPENTITY_H