#ifndef BASESTATE_H
#define BASESTATE_H

#include <string>

#include "Drawer.h"

class StateMachine;

class BaseState
{
public:
	BaseState();
	~BaseState(void);

	virtual bool Enter(void* params);
	virtual bool Update(float aTime);
	virtual bool HandleEvents(SDL_Event* event);
	virtual bool Draw();
	virtual bool Exit();

	std::string GetName() { return name; }

protected:
	std::string name;
	StateMachine* myStateMachine;
	Drawer* myDrawer;
};

#endif // BASESTATE_H