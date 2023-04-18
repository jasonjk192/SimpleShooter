#include "States/BaseState.h"

BaseState::BaseState():
	myDrawer(nullptr),
	myStateMachine(nullptr),
	name("")
{ }

BaseState::BaseState(StateMachine* aStateMachine, Drawer* aDrawer, std::string aName):
	myDrawer(aDrawer),
	myStateMachine(aStateMachine),
	name(aName)
{}

BaseState::~BaseState()
{ }

bool BaseState::Enter(void* params)
{
	return true;
}

bool BaseState::Update(float aTime)
{
	return true;
}

bool BaseState::HandleEvents(SDL_Event* event)
{
	return true;
}

bool BaseState::Draw()
{
	return true;
}

bool BaseState::Exit()
{
	return true;
}
