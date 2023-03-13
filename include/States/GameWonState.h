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
	bool UpdateInput();
	bool Draw();
	bool Exit();

private:
	void UpdateTransitionOut(float aTime);
	void DrawTransitionOut();

	bool isInTransition;
	int transitionAlpha;
	int myScore;

	Texture* youWonText;
	Texture* scoreText;
};

