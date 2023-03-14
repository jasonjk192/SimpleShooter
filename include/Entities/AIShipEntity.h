#ifndef AISHIPENTITY_H
#define AISHIPENTITY_H

#include "Assets/SDLMaths.h"

#include "DynamicEntity.h"

#include "BehaviourTree.h"

class AIShipEntity : public DynamicEntity
{
public:
	AIShipEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer);
	~AIShipEntity(void);

	bool Update(float aTime);
	void Draw();

	void SetDestination(SDL_FPoint dstPoint) { myDestination = dstPoint; hasReachedDestination = false; }
	
	bool HasReachedDestination() { return hasReachedDestination; }

protected:

	SDL_FPoint myDestination;

	bool hasReachedDestination;

	BehaviourTree myTree;

private:
	
	// Can specify different functions and multiple behaviour trees

	static void Move(float aTime, void* ship);
	static void Pick(float aTime, void* ship);

	BehaviourTree::Sequence followCursorSequence;
	Action MoveToDestination = Action(*Move, this);
	Action PickDestination = Action(*Pick, this);
};

#endif // AISHIPENTITY_H