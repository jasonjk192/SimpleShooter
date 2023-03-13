#ifndef STARTSTATE_H
#define STARTSTATE_H

#include "Assets/BackgroundAsset.h"
#include "Assets/ShipAsset.h"
#include "Assets/Button.h"

#include "Menu.h"
#include "StateMachine.h"

#include "BaseState.h"

#include "Entities/AIShipEntity.h"

class StartState: public BaseState
{
public:
	StartState(StateMachine* aStateMachine, Drawer* aDrawer);
	~StartState(void) {};

	bool Enter(void* params);
	bool Update(float aTime);
	bool UpdateInput();
	bool HandleEvents(SDL_Event* event);
	bool Draw();
	bool Exit();

private:
	bool UpdateTransitionOut(float aTime);
	void DrawTransitionOut();

	bool isInTransition;
	int transitionAlpha;

	Menu* myStartMenu;
	BackgroundAsset* myBackgroundAsset;
	UIAsset* ui;

	AIShipEntity* ship;

	SDL_Cursor* myCursor;

	std::vector<SDL_FPoint> destinations;
	int dest;

	static void onPressCallback(int index, void* context)
	{ 
		((StartState*)context)->isInTransition = true;
	}
};

#endif // STARTSTATE_H