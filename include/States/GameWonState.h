#include "BaseState.h"
#include "StateMachine.h"

#pragma once
class GameWonState : public BaseState
{
public:
	GameWonState(StateMachine* aStateMachine, Drawer* aDrawer);
	~GameWonState(void) {};

	bool Enter(void* params);
	bool Update(float aTime);
	bool HandleEvents(SDL_Event* event);
	bool Draw();
	bool Exit();

private:
	int myScore;

	Texture* youWonText;
	Texture* scoreText;

	std::string startStateString = "Start";
};

