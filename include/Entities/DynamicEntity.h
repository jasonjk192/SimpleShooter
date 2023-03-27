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
	SDL_FPoint GetVelocity() const { return myVelocity; }
	SDL_FPoint GetAcceleration() const { return myAcceleration; }

	void SetMoveSpeedMult(float aMoveSpeedMult) { myMoveSpeedMult = aMoveSpeedMult; }
	void SetMaxSpeed(float aMaxSpeed) { myMaxSpeed = aMaxSpeed; }
	void SetMaxAcceleration(float aMaxAcceleration) { myMaxAcceleration = aMaxAcceleration; }
	void SetMass(float aMass) { myMass = aMass; }
	void SetVelocity(SDL_FPoint aVelocity) { myVelocity = aVelocity; }
	void SetAcceleration(SDL_FPoint anAcceleration) { myAcceleration = anAcceleration; }
	void AddForce(SDL_FPoint& aForce) { myAcceleration = { myAcceleration.x + aForce.x / myMass, myAcceleration.y + aForce.y / myMass }; }

	bool Update(float aTime) { return true; }

protected:

	SDL_FPoint myDirection, myVelocity, myAcceleration;

	float myMoveSpeedMult, myMaxSpeed, myMass, myMaxAcceleration;
};

#endif // DYNAMICENTITY_H