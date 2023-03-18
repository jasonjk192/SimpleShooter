#ifndef STARTSTATESHIPENTITY_H
#define STARTSTATESHIPENTITY_H

#include "AIShipEntity.h"
#include "ParticleSystem.h"

#include "Assets/MiscAsset.h"

class StartStateShipEntity : public AIShipEntity
{
public:
	StartStateShipEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer);
	~StartStateShipEntity(void);

	bool HandleEvents(SDL_Event* event);
	bool Update(float aTime);
	void Draw();	

private:

	ParticleSystem* myBooster;
	
	// Can specify different functions and multiple behaviour trees

	static BehaviourTree::NodeStatus MoveForce(float aTime, void* ship, SDL_Event* event);
	static BehaviourTree::NodeStatus MoveVel(float aTime, void* ship, SDL_Event* event);
	static BehaviourTree::NodeStatus PickMouse(float aTime, void* ship, SDL_Event* event);
	static BehaviourTree::NodeStatus PickRandom(float aTime, void* ship, SDL_Event* event);

	BehaviourTree::Selector conditionalMoveSequence;

	BehaviourTree::Sequence followCursorSequence;
	Action MoveToDestination = Action(*MoveVel, this);
	Action PickMouseDestination = Action(*PickMouse, this);

	BehaviourTree::Sequence randomMoveSequence;
	Action PickRandomDestination = Action(*PickRandom, this);
};

#endif // STARTSTATESHIPENTITY_H