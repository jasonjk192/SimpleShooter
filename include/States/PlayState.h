#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "StateMachine.h"
#include "World.h"

#include "BaseState.h"

class PlayState : public BaseState
{
public:
	PlayState(StateMachine* aStateMachine, Drawer* aDrawer);
	~PlayState(void);

	bool Enter(void* params);
	bool Update(float aTime);
	bool HandleEvents(SDL_Event* event);
	bool Draw();
	bool Exit();

private:
	World* myWorld;

};

#endif // PLAYSTATE_H