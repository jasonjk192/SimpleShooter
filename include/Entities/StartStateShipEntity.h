#ifndef STARTSTATESHIPENTITY_H
#define STARTSTATESHIPENTITY_H

#include "AIShipEntity.h"

class StartStateShipEntity : public AIShipEntity
{
public:
	StartStateShipEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer);
	~StartStateShipEntity(void);

private:

	// Can specify different functions and multiple behaviour trees

	static void MoveForce(float aTime, void* ship);
	static void MoveVel(float aTime, void* ship);
	static void Pick(float aTime, void* ship);

	BehaviourTree::Sequence followCursorSequence;
	Action MoveToDestination = Action(*MoveVel, this);
	Action PickDestination = Action(*Pick, this);
};

#endif // STARTSTATESHIPENTITY_H