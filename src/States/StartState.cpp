#include "States/StartState.h"

StartState::StartState(StateMachine* aStateMachine, Drawer* aDrawer):
    isInTransition(false),
    transitionAlpha(0)
{
    ui = &UIAsset::GetInstance();
    myStartMenu = new Menu(aDrawer);
    name = "Start";
    myStateMachine = aStateMachine;
    myDrawer = aDrawer;
    myBackgroundAsset = &BackgroundAsset::GetInstance();
}  

bool StartState::Enter(void* params)
{
    myDrawer->SetColor(255, 255, 0, 255);
    myStartMenu->AddItem("Start Game");
    myStartMenu->AddItem("Quit");
    myStartMenu->myCurrentSelection = 0;
    myStartMenu->SetCallback(&onPressCallback, this);

    int winW, winH;
    myDrawer->GetWindowSize(&winW, &winH);
    myStartMenu->SetOffset((winW - myStartMenu->GetMenuWidth()) / 2, (winH - myStartMenu->GetMenuHeight()) / 2);
    myStartMenu->SetSpacing(5);

    SDL_ShowCursor(SDL_ENABLE);

    SDL_Surface* surface = IMG_Load(".\\data\\simpleCursor.png");
    myCursor = SDL_CreateColorCursor(surface, 0 , 0);
    SDL_SetCursor(myCursor);

    ship = new AIShipEntity({220,220}, ShipAsset::GetInstance().GetPlayerTexture(4), myDrawer);

    ship->SetDestination({ 300,312 });
    ship->SetMaxSpeed(30);
    ship->SetMaxAcceleration(10);

    return true;
}

bool StartState::Update(float aTime)
{
    if (isInTransition)
        return UpdateTransitionOut(aTime);
    if (!UpdateInput())
        return false;

    ship->Update(aTime);

    int x, y;
    SDL_GetMouseState(&x, &y);
    ship->SetDestination({(float)x,(float)y});

    return true;
}

bool StartState::UpdateInput()
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_ESCAPE])
		return false;
    else if (keystate[SDL_SCANCODE_UP])
        myStartMenu->myCurrentSelection = myStartMenu->myCurrentSelection == 0 ? 0 : --myStartMenu->myCurrentSelection;
    else if(keystate[SDL_SCANCODE_DOWN])
        myStartMenu->myCurrentSelection = myStartMenu->myCurrentSelection == 1 ? 1 : ++myStartMenu->myCurrentSelection;
    else if (keystate[SDL_SCANCODE_RETURN])
        isInTransition = true;
	return true;
}

bool StartState::HandleEvents(SDL_Event* event)
{
    if (!isInTransition)
    {
        myStartMenu->HandleEvents(event);
    }
    return true;
}

bool StartState::Draw()
{
    myDrawer->SetScale(5);
    myBackgroundAsset->Draw(myDrawer, 0, 0, 0);
    myDrawer->SetScale(1);

    myDrawer->SetColor(255, 255, 0, 255);
    myStartMenu->Draw(0);
    myStartMenu->DrawSelectionBox(2);

    //ShipAsset::GetInstance().Draw(myDrawer, 0);

    ship->Draw();

    if (isInTransition)
        DrawTransitionOut();

    return true;
}

bool StartState::Exit()
{
    myStartMenu->Clear();
    isInTransition = false;
    transitionAlpha = 0;
    SDL_FreeCursor(myCursor);

    return true;
}

bool StartState::UpdateTransitionOut(float aTime)
{
    transitionAlpha += 2;
    if (transitionAlpha >= 255)
        if (myStartMenu->myCurrentSelection == 0)
            myStateMachine->Change("GameLost");
        else
            return false;
    return true;
}

void StartState::DrawTransitionOut()
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