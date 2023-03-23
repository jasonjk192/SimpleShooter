#include "States/PlayState.h"

PlayState::PlayState(StateMachine* aStateMachine, Drawer *aDrawer):
	BaseState(aStateMachine, aDrawer, "Play"),
	myWorld(nullptr)
{
}

PlayState::~PlayState(void)
{}

bool PlayState::Enter(void* params)
{
	myWorld = new World(myStateMachine, myDrawer);
	return true;
}

bool PlayState::Update(float aTime)
{
	myWorld->Update(aTime);
	return true;
}

bool PlayState::HandleEvents(SDL_Event* event)
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_ESCAPE])
		return false;
	myWorld->HandleEvents(event);
	return true;
}

bool PlayState::Draw()
{
	myWorld->Draw();
	return true;
}

bool PlayState::Exit()
{
	delete myWorld;
	return true;
}