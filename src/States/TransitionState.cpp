#include "States/TransitionState.h"

TransitionState::TransitionState(StateMachine* aStateMachine, Drawer* aDrawer):
	BaseState(aStateMachine, aDrawer, "Transition"),
	transitionAlpha(0)
{}

bool TransitionState::Enter(void* params)
{
	transitionAlpha = 0;
	nextState = *(std::string*)params;
	return true;
}

bool TransitionState::Update(float aTime)
{
	transitionAlpha += aTime * 500;
	if (transitionAlpha >= 255)
	{
		myStateMachine->Pop();
		myStateMachine->Pop();
		myStateMachine->Push(nextState);
	}
	return true;
}

bool TransitionState::Draw()
{
	int winW, winH;
	myDrawer->GetWindowSize(&winW, &winH);
	myDrawer->SetColor(255, 255, 0, 255);
	myDrawer->SetColor(0, 0, 0, (int)transitionAlpha);
	myDrawer->SetBlendMode(1);
	myDrawer->DrawRect(0, 0, winW, winH, true);
	myDrawer->SetBlendMode(0);
	myDrawer->SetColor(0, 0, 0, 255);
	return true;
}