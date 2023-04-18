#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <string>
#include <vector>

#include "Drawer.h"
#include "States/BaseState.h"
#include "States/TransitionState.h"

class TransitionState;

class StateMachine
{
public:
	StateMachine();
	~StateMachine(void);

	void Change(BaseState* aState, void* params = nullptr);
	bool Update(float aTime);
	bool HandleEvents(SDL_Event* event);
	bool Draw();

	void Push(BaseState* aState, void* params = nullptr);
	void Pop();

	void AddPushedStates();
	void DeletePoppedStates();

private:

	std::vector<BaseState*> myCurrentStates;
	std::vector<BaseState*> myPoppedStates;
	std::vector<BaseState*> myPushedStates;
	std::vector<void*> myPushedStatesParams;

	bool hasPushed;
	bool hasPopped;
};

#endif // STATEMACHINE_H