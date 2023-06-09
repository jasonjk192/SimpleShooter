#include "States/GameLostState.h"

GameLostState::GameLostState(StateMachine* aStateMachine, Drawer* aDrawer):
	BaseState(aStateMachine, aDrawer, "GameLost"),
	youLostText(nullptr),
	myScore(0),
	scoreText(nullptr)
{}

bool GameLostState::Enter(void* params)
{
	myScore = *((int*)params);
	std::string scoreString = "Score : " + std::to_string(myScore);

	myDrawer->SetColor(255, 127, 0, 255);
	youLostText = new Texture(myDrawer->GetRenderer(), "You Lost!", ".\\data\\fonts\\NoContinue-Vogl.ttf");
	scoreText = new Texture(myDrawer->GetRenderer(), scoreString.c_str(), ".\\data\\fonts\\NoContinue-Vogl.ttf");
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
		myStateMachine->Push(new TransitionState(myStateMachine, myDrawer, new StartState(myStateMachine, myDrawer)));
	return true;
}

bool GameLostState::Draw()
{
	SDL_Point windowSize = myDrawer->GetWindowSize();
	myDrawer->SetColor(255, 255, 0, 255);
	int posX = (windowSize.x - youLostText->GetSize()->x) / 2;
	int posY = windowSize.y / 2 + youLostText->GetSize()->y;
	myDrawer->Draw(youLostText, posX, posY);
	myDrawer->Draw(scoreText, posX, posY + 30);
	return true;
}

bool GameLostState::Exit()
{
	delete youLostText;
	delete scoreText;
	youLostText = nullptr;
	scoreText = nullptr;
	return true;
}