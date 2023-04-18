#include "States/GamePausedState.h"

GamePausedState::GamePausedState(StateMachine* aStateMachine, Drawer* aDrawer):
	BaseState(aStateMachine, aDrawer, "GamePaused"),
    myCursor(nullptr),
    myPauseMenu(nullptr)
{
    myUIAsset = &UIAsset::GetInstance();
}

GamePausedState::~GamePausedState(void)
{
}

bool GamePausedState::Enter(void* params)
{
    myPauseMenu = new Menu(myDrawer);
    myDrawer->SetColor(255, 255, 0, 255);
    myPauseMenu->AddItem("Continue Game");
    myPauseMenu->AddItem("Exit");
    myPauseMenu->myCurrentSelection = 0;
    myPauseMenu->SetCallback(&onPressCallback, this);

    SDL_Point windowSize = myDrawer->GetWindowSize();
    myPauseMenu->SetOffset((windowSize.x - myPauseMenu->GetMenuWidth()) / 2, (windowSize.y - myPauseMenu->GetMenuHeight()) / 2);
    myPauseMenu->SetSpacing(5);

    SDL_ShowCursor(SDL_ENABLE);

    SDL_Surface* surface = IMG_Load(".\\data\\simpleCursor.png");
    myCursor = SDL_CreateColorCursor(surface, 0, 0);
    SDL_SetCursor(myCursor);

	return true;
}

bool GamePausedState::Update(float aTime)
{
	return true;
}

bool GamePausedState::HandleEvents(SDL_Event* event)
{
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_UP])
        myPauseMenu->SelectPrevious();
    else if (keystate[SDL_SCANCODE_DOWN])
        myPauseMenu->SelectNext();
    else if (keystate[SDL_SCANCODE_RETURN])
    {
        if (myPauseMenu->myCurrentSelection == 0)
        {
            myStateMachine->Pop();
            return true;
        }
        else
        {
            myStateMachine->Push(new TransitionState(myStateMachine, myDrawer, new StartState(myStateMachine, myDrawer)));
            return true;
        }
    }

    if (!myPauseMenu->HandleEvents(event))
        return false;
	return true;
}

bool GamePausedState::Draw()
{
    SDL_Point windowSize = myDrawer->GetWindowSize();

    myDrawer->SetBlendMode(1);
    myDrawer->SetColor(0, 0, 0, 128);
    myDrawer->DrawRect(0, 0, windowSize.x, windowSize.y, true);
    myDrawer->SetColor(255, 255, 255, 255);
    myDrawer->SetBlendMode(0);

    myPauseMenu->Draw(0);
    myPauseMenu->DrawSelectionBox(2);
	return true;
}

bool GamePausedState::Exit()
{
    myPauseMenu->Clear();
    SDL_FreeCursor(myCursor);

    delete myPauseMenu;
	return true;
}

bool GamePausedState::onPressCallback(int index, void* context)
{
    GamePausedState* state = ((GamePausedState*)context);
    if (state->myPauseMenu->myCurrentSelection == 0)
        state->myStateMachine->Pop();
    else
        state->myStateMachine->Push(new TransitionState(state->myStateMachine, state->myDrawer, new StartState(state->myStateMachine, state->myDrawer)));
    return true;
}