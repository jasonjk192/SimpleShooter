#ifndef BASEENTITY_H
#define BASEENTITY_H

#include <string>

#include "Drawer.h"

class BaseEntity
{
public:
	BaseEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer);
	~BaseEntity(void);

	void SetPosition(const SDL_FPoint& aPosition) { myPosition = aPosition; }

	std::string GetName() { return name; }
	SDL_FPoint GetPosition() const { return myPosition; }

	bool CollidesWith(BaseEntity* anEntity);
	virtual void Draw();

protected:


	std::string name;
	SDL_FPoint myPosition;
	Texture* myTexture;

	Drawer* myDrawer;
};

#endif // BASEENTITY_H