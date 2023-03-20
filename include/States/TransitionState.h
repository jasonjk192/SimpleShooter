#ifndef TRANSITIONSTATE_H
#define TRANSITIONSTATE_H

#include "StateMachine.h"
#include "BaseState.h"

class TransitionState : public BaseState
{
public:
	TransitionState(StateMachine* aStateMachine, Drawer* aDrawer);
	~TransitionState(void) {};

	bool Enter(void* params);
	bool Update(float aTime);
	bool Draw();

private:
	float transitionAlpha;
	std::string nextState;
};

#endif // TRANSITIONSTATE_H