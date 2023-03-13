#include "States/BaseState.h"

BaseState::BaseState():
	myDrawer(nullptr),
	myStateMachine(nullptr)
{ }

BaseState::~BaseState(void)
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
