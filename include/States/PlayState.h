#pragma once

#include "GameState.h"
#include "StateMachine.h"
#include "Pacman.h"
#include "Drawer.h"

class PlayState : public GameState
{
public:
	PlayState(StateMachine* aStateMachine, Drawer* aDrawer);
	~PlayState(void) {};

	bool Enter(void* params);
	bool Update(float aTime);
	bool Draw(Drawer* aDrawer);
private:
	void TransitionIn(float aTime);
	int myCurrentMenuItem;
	Pacman* pacman;
	Drawer* myDrawer;
};