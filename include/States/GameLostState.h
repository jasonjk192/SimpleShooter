#ifndef GAMELOSTSTATE_H
#define GAMELOSTSTATE_H

#include "BaseState.h"
#include "StateMachine.h"

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

	std::string startStateString = "Start";
};

#endif // GAMELOSTSTATE_H