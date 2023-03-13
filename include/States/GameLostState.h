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
	bool UpdateInput();
	bool Draw();
	bool Exit();


private:
	void UpdateTransitionOut(float aTime);
	void DrawTransitionOut();

	bool isInTransition;
	int transitionAlpha;

	Texture* youLostText;
};

#endif // GAMELOSTSTATE_H