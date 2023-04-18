#ifndef GAMELOSTSTATE_H
#define GAMELOSTSTATE_H

#include "StateMachine.h"

#include "States/StartState.h"

class GameLostState : public BaseState
{
public:
	GameLostState(StateMachine* aStateMachine, Drawer* aDrawer);
	~GameLostState(void) {};

	bool Enter(void* params);
	bool Update(float aTime);
	bool HandleEvents(SDL_Event* event);
	bool Draw();
	bool Exit();


private:
	Texture* youLostText;

	int myScore;
	Texture* scoreText;
};

#endif // GAMELOSTSTATE_H