#include "States/TransitionState.h"

TransitionState::TransitionState(StateMachine* aStateMachine, Drawer* aDrawer, BaseState* aNextState):
	BaseState(aStateMachine, aDrawer, "Transition"),
	transitionAlpha(0),
	nextState(aNextState),
	nextStateParams(nullptr)
{}

bool TransitionState::Enter(void* params)
{
	transitionAlpha = 0;
	nextStateParams = params;
	return true;
}

bool TransitionState::Update(float aTime)
{
	transitionAlpha += aTime * 500;
	if (transitionAlpha >= 255)
	{
		myStateMachine->Pop();
		myStateMachine->Pop();
		myStateMachine->Push(nextState, nextStateParams);
	}
	return true;
}

bool TransitionState::Draw()
{
	SDL_Point windowSize = myDrawer->GetWindowSize();
	myDrawer->SetColor(255, 255, 0, 255);
	myDrawer->SetColor(0, 0, 0, (int)transitionAlpha);
	myDrawer->SetBlendMode(1);
	myDrawer->DrawRect(0, 0, windowSize.x, windowSize.y, true);
	myDrawer->SetBlendMode(0);
	myDrawer->SetColor(0, 0, 0, 255);
	return true;
}