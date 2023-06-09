#ifndef AISHIPENTITY_H
#define AISHIPENTITY_H

#include "Assets/SDLMaths.h"

#include "GameCharacterEntity.h"

#include "BehaviourTree.h"

class AIShipEntity : public GameCharacterEntity
{
public:
	AIShipEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer);
	~AIShipEntity(void);

	bool Update(float aTime);
	void Draw();

	void SetDestination(SDL_FPoint dstPoint) { myDestination = dstPoint; hasReachedDestination = false; }

	void SetBehaviourTree(BehaviourTree* aTree) { myTree = aTree; }
	
	bool HasReachedDestination() { return hasReachedDestination; }
	SDL_FPoint GetDestination() { return myDestination; }

protected:

	SDL_FPoint myDestination;
	BehaviourTree* myTree;

	bool hasReachedDestination;
};

#endif // AISHIPENTITY_H