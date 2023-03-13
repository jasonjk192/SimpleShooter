#include "StateMachine.h"

StateMachine::StateMachine()
{}

StateMachine::~StateMachine(void)
{}

void StateMachine::Change(std::string stateName, void* params)
{
	if (myCurrentStates.size() > 0)
	{
		for (int i = myCurrentStates.size() - 1; i>=0; i-=1)
			myCurrentStates[i]->Exit();
		myCurrentStates.clear();
	}
	auto state = GetState(stateName);
	if (state == nullptr)
		return;
	myCurrentStates.push_back(state);
	myCurrentStates[0]->Enter(params);
}

bool StateMachine::Update(float aTime)
{
	return myCurrentStates[myCurrentStates.size()-1]->Update(aTime);
}

bool StateMachine::HandleEvents(SDL_Event* event)
{
	return myCurrentStates[myCurrentStates.size() - 1]->HandleEvents(event);
}

bool StateMachine::Draw()
{
	for (auto state : myCurrentStates)
		if(!state->Draw())
			return false;
	return true;
}

void StateMachine::Add(BaseState* aBaseState)
{
	myStates.push_back(aBaseState);
}

void StateMachine::Push(std::string stateName)
{
	auto state = GetState(stateName);
	if (state == nullptr)
		return;
	myCurrentStates.push_back(state);
}

void StateMachine::Pop()
{
	myCurrentStates[myCurrentStates.size() - 1]->Exit();
	myCurrentStates.pop_back();
}

BaseState* StateMachine::GetState(std::string stateName)
{
	for (int i = 0; i < myStates.size(); i++)
		if (myStates[i]->GetName() == stateName)
			return myStates[i];
	return nullptr;
}
