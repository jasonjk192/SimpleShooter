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
	void SetDrawRegion(SDL_Rect* aRegion) { myDrawRegion = aRegion; }

	std::string GetName() { return name; }
	SDL_FPoint GetPosition() const { return myPosition; }

	bool CollidesWith(BaseEntity* anEntity);
	virtual void Draw();

protected:


	std::string name;
	SDL_FPoint myPosition;
	Texture* myTexture;

	SDL_Rect* myDrawRegion;

	Drawer* myDrawer;
};

#endif // BASEENTITY_H