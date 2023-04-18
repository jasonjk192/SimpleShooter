#ifndef GAMEPAUSEDSTATE_H
#define GAMEPAUSEDSTATE_H

#include "StateMachine.h"
#include "Menu.h"

#include "States/StartState.h"

class GamePausedState : public BaseState
{
public:
	GamePausedState(StateMachine* aStateMachine, Drawer* aDrawer);
	~GamePausedState(void);

	bool Enter(void* params);
	bool Update(float aTime);
	bool HandleEvents(SDL_Event* event);
	bool Draw();
	bool Exit();

private:

	Menu* myPauseMenu;
	UIAsset* myUIAsset;
	SDL_Cursor* myCursor;

	static bool onPressCallback(int index, void* context);
};

#endif // GAMEPAUSEDSTATE_H