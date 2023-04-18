#include "StateMachine.h"

#include <iostream>

StateMachine::StateMachine():
	hasPushed(false),
	hasPopped(false)
{}

StateMachine::~StateMachine(void)
{
	hasPopped = true;
	DeletePoppedStates();
	for (int i = myCurrentStates.size() - 1; i >= 0; i -= 1)
		delete myCurrentStates[i];
	for (int i = myPushedStates.size() - 1; i >= 0; i -= 1)
		delete myCurrentStates[i];
	myCurrentStates.clear();
	myPushedStates.clear();
}

void StateMachine::Change(BaseState* aState, void* params)
{
	hasPushed = true;
	if (myCurrentStates.size() > 0)
	{
		hasPopped = true;
		for (int i = myCurrentStates.size() - 1; i >= 0; i -= 1)
		{
			myPoppedStates.push_back(myCurrentStates[i]);
		}
		myCurrentStates.clear();
	}
	myPushedStates.push_back(aState);
	myPushedStatesParams.push_back(params);
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

void StateMachine::Push(BaseState* aState, void* params)
{
	hasPushed = true;
	myPushedStates.push_back(aState);
	myPushedStatesParams.push_back(params);
}

void StateMachine::Pop()
{
	hasPopped = true;
	myPoppedStates.push_back(myCurrentStates[myCurrentStates.size() - 1]);
	myCurrentStates.pop_back();
}

void StateMachine::AddPushedStates()
{
	if (hasPushed)
	{
		for (int i = 0; i < myPushedStates.size(); i++)
		{
			myCurrentStates.push_back(myPushedStates[i]);
			myPushedStates[i]->Enter(myPushedStatesParams[i]);
		}
		myPushedStates.clear();
		myPushedStatesParams.clear();
	}
}

void StateMachine::DeletePoppedStates()
{
	if (hasPopped)
	{
		for (int i = myPoppedStates.size() - 1; i >= 0; i -= 1)
		{
			myPoppedStates[i]->Exit();
			delete myPoppedStates[i];
		}
		myPoppedStates.clear();
	}
}