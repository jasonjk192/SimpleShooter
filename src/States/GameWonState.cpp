#include "States/GameWonState.h"

GameWonState::GameWonState(StateMachine* aStateMachine, Drawer* aDrawer) :
	BaseState(aStateMachine, aDrawer, "GameWon"),
	youWonText(nullptr),
	myScore(0),
	scoreText(nullptr)
{}

bool GameWonState::Enter(void* params)
{
	myScore = *((int*)params);
	std::string scoreString = "Score : " + std::to_string(myScore);

	myDrawer->SetColor(255, 127, 0, 255);
	youWonText = new Texture(myDrawer->GetRenderer(), "You Won!", ".\\data\\fonts\\NoContinue-Vogl.ttf");
	scoreText = new Texture(myDrawer->GetRenderer(), scoreString.c_str(), ".\\data\\fonts\\NoContinue-Vogl.ttf");
	return true;
}

bool GameWonState::Update(float aTime)
{
	return true;
}

bool GameWonState::HandleEvents(SDL_Event* event)
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_ESCAPE])
		return false;
	else if (keystate[SDL_SCANCODE_RETURN])
		myStateMachine->Push(new TransitionState(myStateMachine, myDrawer, new StartState(myStateMachine, myDrawer)));
	return true;
}

bool GameWonState::Draw()
{
	SDL_Point windowSize = myDrawer->GetWindowSize();
	myDrawer->SetColor(255, 255, 0, 255);
	int posX = (windowSize.x - youWonText->GetSize()->x) / 2;
	int posY = windowSize.y / 2 + youWonText->GetSize()->y;
	myDrawer->Draw(youWonText, posX, posY);
	myDrawer->Draw(scoreText, posX, posY + 30);
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