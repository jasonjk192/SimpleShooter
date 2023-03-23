#ifndef STARTSTATE_H
#define STARTSTATE_H

#include "Assets/BackgroundAsset.h"
#include "Assets/ShipAsset.h"
#include "Assets/Button.h"

#include "Menu.h"
#include "StateMachine.h"

#include "BaseState.h"

#include "Entities/StartStateShipEntity.h"

class StartState: public BaseState
{
public:
	StartState(StateMachine* aStateMachine, Drawer* aDrawer);
	~StartState(void) {};

	bool Enter(void* params);
	bool Update(float aTime);
	bool HandleEvents(SDL_Event* event);
	bool Draw();
	bool Exit();

private:

	Menu* myStartMenu;
	BackgroundAsset* myBackgroundAsset;
	UIAsset* myUIAsset;
	SDL_Cursor* myCursor;

	StartStateShipEntity* ship;

	std::string playStateString = "Play";

	static bool onPressCallback(int index, void* context) {
		StartState* state = ((StartState*)context);
		if (state->myStartMenu->myCurrentSelection == 0)
			state->myStateMachine->Push("Transition", &state->playStateString);
		else
			return false;
	}
};

#endif // STARTSTATE_H