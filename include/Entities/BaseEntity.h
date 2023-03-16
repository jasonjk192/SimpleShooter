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
	void SetScale(const float aScale) { myScale = aScale; }
	std::string SetName(const std::string& aName) { myName = aName; }

	std::string GetName() const { return myName; }
	SDL_FPoint GetPosition() const { return myPosition; }
	float GetScale() const { return myScale; }

	bool CollidesWith(BaseEntity* anEntity);
	virtual void Draw();

protected:
	std::string myName;
	SDL_FPoint myPosition;
	Texture* myTexture;

	Drawer* myDrawer;

	float myScale;
};

#endif // BASEENTITY_H