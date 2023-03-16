#ifndef STARTSTATESHIPENTITY_H
#define STARTSTATESHIPENTITY_H

#include "AIShipEntity.h"
#include "ParticleSystem.h"

class StartStateShipEntity : public AIShipEntity
{
public:
	StartStateShipEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer);
	~StartStateShipEntity(void);

	bool Update(float aTime);
	void Draw();

private:

	ParticleSystem* myBooster;
	
	// Can specify different functions and multiple behaviour trees

	static void MoveForce(float aTime, void* ship);
	static void MoveVel(float aTime, void* ship);
	static void Pick(float aTime, void* ship);

	BehaviourTree::Sequence followCursorSequence;
	Action MoveToDestination = Action(*MoveVel, this);
	Action PickDestination = Action(*Pick, this);
};

#endif // STARTSTATESHIPENTITY_H