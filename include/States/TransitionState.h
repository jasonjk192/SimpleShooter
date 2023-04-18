#ifndef TRANSITIONSTATE_H
#define TRANSITIONSTATE_H

#include "StateMachine.h"
#include "BaseState.h"

class TransitionState : public BaseState
{
public:
	TransitionState(StateMachine* aStateMachine, Drawer* aDrawer, BaseState* aNextState);
	~TransitionState(void) {};

	bool Enter(void* params);
	bool Update(float aTime);
	bool Draw();

	void SetNextStateParams(void* aStateParams) { nextStateParams = aStateParams; }

private:
	float transitionAlpha;
	void* nextStateParams;
	BaseState* nextState;
};

#endif // TRANSITIONSTATE_H