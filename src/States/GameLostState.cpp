#include "States/GameLostState.h"

GameLostState::GameLostState(StateMachine* aStateMachine, Drawer* aDrawer)
{
	name = "GameLost";
	myStateMachine = aStateMachine;
	myDrawer = aDrawer;
}

bool GameLostState::Enter(void* params)
{
	myDrawer->SetColor(255, 127, 0, 255);
	transitionAlpha = 0;
	isInTransition = false;
	youLostText = new Texture(myDrawer->GetRenderer(), "You Lost!", ".\\data\\fonts\\NoContinue-Vogl.ttf");
	return true;
}

bool GameLostState::Update(float aTime)
{
	if (isInTransition)
	{
		UpdateTransitionOut(aTime);
		return true;
	}
	if (!UpdateInput())
		return false;
	return true;
}

bool GameLostState::UpdateInput()
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_ESCAPE])
		return false;
	else if (keystate[SDL_SCANCODE_RETURN])
		isInTransition = true;
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

	if (isInTransition)
		DrawTransitionOut();
	return true;
}

bool GameLostState::Exit()
{
	delete youLostText;
	youLostText = nullptr;
	return true;
}

void GameLostState::UpdateTransitionOut(float aTime)
{
	transitionAlpha += 2;
	if (transitionAlpha >= 255)
		myStateMachine->Change("Start");
}

void GameLostState::DrawTransitionOut()
{
	int winW, winH;
	myDrawer->GetWindowSize(&winW, &winH);
	myDrawer->SetColor(255, 255, 0, 255);
	myDrawer->SetColor(0, 0, 0, transitionAlpha);
	myDrawer->SetBlendMode(1);
	myDrawer->DrawRect(0, 0, winW, winH, true);
	myDrawer->SetBlendMode(0);
	myDrawer->SetColor(0, 0, 0, 255);
}