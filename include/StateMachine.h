#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <string>
#include <vector>

#include "Drawer.h"
#include "States/BaseState.h"

class StateMachine
{
public:
	StateMachine();
	~StateMachine(void);

	void Change(std::string stateName, void* params = nullptr);
	bool Update(float aTime);
	bool HandleEvents(SDL_Event* event);
	bool Draw();
	void Add(BaseState* aBaseState);

	void Push(std::string stateName, void* params = nullptr);
	void Pop();

private:
	BaseState* GetState(std::string stateName);

	std::vector<BaseState*> myStates;
	std::vector<BaseState*> myCurrentStates;
};

#endif // STATEMACHINE_H