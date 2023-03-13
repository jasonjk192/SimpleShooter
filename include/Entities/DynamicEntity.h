#ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H

#include "Assets/SDLMaths.h"

#include "BaseEntity.h"

class DynamicEntity : public BaseEntity
{
public:
	DynamicEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer);
	~DynamicEntity(void);

	SDL_FPoint GetDirection() const { return myDirection; }

	void SetMoveSpeedMult(float aMoveSpeedMult) { myMoveSpeedMult = aMoveSpeedMult; }
	void SetMaxSpeed(float aMaxSpeed) { myMaxSpeed = aMaxSpeed; }
	void SetMass(float aMass) { myMass = aMass; }
	void AddForce(SDL_FPoint& aForce) { myAcceleration = { myAcceleration.x + aForce.x / myMass, myAcceleration.y + aForce.y / myMass }; }

	bool Update(float aTime);

protected:

	SDL_FPoint myDirection, myVelocity, myAcceleration;

	float myMoveSpeedMult, myMaxSpeed, myMass;
};

#endif // DYNAMICENTITY_H