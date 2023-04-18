#include "States/StartState.h"

StartState::StartState(StateMachine* aStateMachine, Drawer* aDrawer):
    BaseState(aStateMachine, aDrawer, "Start"),
    myCursor(nullptr),
    myStartMenu(nullptr),
    ship(nullptr)
{
    myBackgroundAsset = &BackgroundAsset::GetInstance();
    myUIAsset = &UIAsset::GetInstance();
}  

StartState::~StartState()
{
}

bool StartState::Enter(void* params)
{
    myStartMenu = new Menu(myDrawer);
    myDrawer->SetColor(255, 255, 0, 255);
    myStartMenu->AddItem("Start Game");
    myStartMenu->AddItem("Quit");
    myStartMenu->myCurrentSelection = 0;
    myStartMenu->SetCallback(&onPressCallback, this);

    SDL_Point windowSize = myDrawer->GetWindowSize();
    myStartMenu->SetOffset((windowSize.x - myStartMenu->GetMenuWidth()) / 2, (windowSize.y - myStartMenu->GetMenuHeight()) / 2);
    myStartMenu->SetSpacing(5);

    SDL_ShowCursor(SDL_ENABLE);

    SDL_Surface* surface = IMG_Load(".\\data\\simpleCursor.png");
    myCursor = SDL_CreateColorCursor(surface, 0 , 0);
    SDL_SetCursor(myCursor);

    ship = new StartStateShipEntity({ (float)(std::rand() % windowSize.x), (float)(std::rand() % windowSize.y) }, ShipAsset::GetInstance().GetPlayerTexture(4), myDrawer);
    ship->SetMaxSpeed(30);
    ship->SetMaxAcceleration(10);
    ship->SetScale(2.f);

    return true;
}

bool StartState::Update(float aTime)
{
    ship->Update(aTime);
    return true;
}

bool StartState::HandleEvents(SDL_Event* event)
{
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_ESCAPE])
        return false;
    else if (keystate[SDL_SCANCODE_UP])
        myStartMenu->SelectPrevious();
    else if (keystate[SDL_SCANCODE_DOWN])
        myStartMenu->SelectNext();
    else if (keystate[SDL_SCANCODE_RETURN])
    {
        if (myStartMenu->myCurrentSelection == 0)
        {
            myStateMachine->Push(new TransitionState(myStateMachine, myDrawer, new PlayState(myStateMachine, myDrawer)));
            return true;
        }
        else
            return false;
    }

    ship->HandleEvents(event);

    if(!myStartMenu->HandleEvents(event))
        return false;

    return true;
}

bool StartState::Draw()
{
    myDrawer->SetScale(5);
    myDrawer->Draw(myBackgroundAsset->GetBackgroundTexture(0), myBackgroundAsset->GetBackgroundTexture(0)->GetSize()->x * 2, myBackgroundAsset->GetBackgroundTexture(0)->GetSize()->y * 2);
    myDrawer->SetScale(1);

    myDrawer->SetColor(255, 255, 0, 255);
    myStartMenu->Draw(0);
    myStartMenu->DrawSelectionBox(2);

    ship->Draw();

    return true;
}

bool StartState::Exit()
{
    myStartMenu->Clear();
    SDL_FreeCursor(myCursor);

    delete myStartMenu;
    delete ship;

    return true;
}

bool StartState::onPressCallback(int index, void* context)
{
    StartState* state = ((StartState*)context);
    if (state->myStartMenu->myCurrentSelection == 0)
        state->myStateMachine->Push(new TransitionState(state->myStateMachine, state->myDrawer, new PlayState(state->myStateMachine, state->myDrawer)));
    else
        return false;
}