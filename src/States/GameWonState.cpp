#include "States/GameWonState.h"

GameWonState::GameWonState(StateMachine* aStateMachine, Drawer* aDrawer):
	BaseState(aStateMachine, aDrawer, "GameWon")
{}

bool GameWonState::Enter(void* params)
{
	myScore = *((int*)params);
	std::string scoreString = "Score : " + std::to_string(myScore);

	myDrawer->SetColor(255, 255, 0, 255);
	youWonText = new Texture(myDrawer->GetRenderer(), "You Won!", "freefont-ttf\\sfd\\FreeMono.ttf");
	scoreText = new Texture(myDrawer->GetRenderer(), scoreString.c_str(), "freefont-ttf\\sfd\\FreeMono.ttf");

	transitionAlpha = 0;
	isInTransition = false;

	return true;
}

bool GameWonState::Update(float aTime)
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

bool GameWonState::UpdateInput()
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_ESCAPE])
		return false;
	else if (keystate[SDL_SCANCODE_RETURN])
		isInTransition = true;

	return true;
}

bool GameWonState::Draw()
{
	int winW, winH;
	myDrawer->GetWindowSize(&winW, &winH);
	myDrawer->SetColor(255, 255, 0, 255);
	SDL_Point* textSize = youWonText->GetSize();
	int posX = (winW - textSize->x) / 2;
	int posY = winH / 2 + textSize->y;
	
	myDrawer->Draw(youWonText, posX, posY);
	myDrawer->Draw(scoreText, posX, posY + 30);

	if (isInTransition)
		DrawTransitionOut();
	return true;
}

bool GameWonState::Exit()
{
	delete youWonText;
	delete scoreText;
	youWonText = nullptr;
	scoreText = nullptr;

	return true;
}

void GameWonState::UpdateTransitionOut(float aTime)
{
	transitionAlpha += 2;
	if (transitionAlpha >= 255)
		myStateMachine->Change("Start");
}

void GameWonState::DrawTransitionOut()
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