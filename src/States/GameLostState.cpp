#include "States/GameLostState.h"

GameLostState::GameLostState(StateMachine* aStateMachine, Drawer* aDrawer):
	BaseState(aStateMachine, aDrawer, "GameLost"),
	youLostText(nullptr)
{}

bool GameLostState::Enter(void* params)
{
	myDrawer->SetColor(255, 127, 0, 255);
	youLostText = new Texture(myDrawer->GetRenderer(), "You Lost!", ".\\data\\fonts\\NoContinue-Vogl.ttf");
	return true;
}

bool GameLostState::Update(float aTime)
{
	return true;
}

bool GameLostState::HandleEvents(SDL_Event* event)
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_ESCAPE])
		return false;
	else if (keystate[SDL_SCANCODE_RETURN])
		myStateMachine->Push("Transition", &startStateString);
	return true;
}

bool GameLostState::Draw()
{
	int winW, winH;
	myDrawer->GetWindowSize(&winW, &winH);
	myDrawer->SetColor(255, 255, 0, 255);
	int posX = (winW - youLostText->GetSize()->x) / 2;
	int posY = winH / 2 + youLostText->GetSize()->y;
	myDrawer->Draw(youLostText, posX, posY);
	return true;
}

bool GameLostState::Exit()
{
	delete youLostText;
	youLostText = nullptr;
	return true;
}