#include "PlayState.h"

PlayState::PlayState(StateMachine* aStateMachine, Drawer *aDrawer)
{
	name = "Play";
	myStateMachine = aStateMachine;
	myDrawer = aDrawer;
}

bool PlayState::Enter(void* params)
{
	myStateMachine->Push("Pause");
	pacman = Pacman::Create(myStateMachine, myDrawer);
	return true;
}

bool PlayState::Update(float aTime)
{
	return pacman->Update(aTime);
}

bool PlayState::Draw(Drawer* aDrawer)
{
	return pacman->Draw();
}

void PlayState::TransitionIn(float aTime)
{
	/*transitionAlpha -= 2;
	if (transitionAlpha <= 0)
		myStateMachine->Change("Play");*/
}
