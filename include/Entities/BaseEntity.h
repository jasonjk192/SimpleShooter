#ifndef BASEENTITY_H
#define BASEENTITY_H

#include <string>

#include "Assets/SDLMaths.h"
#include "Drawer.h"

class BaseEntity
{
public:
	BaseEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer);
	~BaseEntity(void);

	void SetPosition(const SDL_FPoint& aPosition) { myPosition = aPosition; }
	void SetScale(const float aScale) { myScale = aScale; }
	void SetName(const std::string& aName) { myName = aName; }
	void SetMarkForDelete() { markForDelete = true; }

	std::string GetName() const { return myName; }
	SDL_FPoint GetPosition() const { return myPosition; }
	float GetScale() const { return myScale; }
	bool IsMarkedForDelete() { return markForDelete; }

	virtual bool HandleEvents(SDL_Event* event) { return true; }
	virtual bool Update(float aTime) { return true; }
	virtual void Draw();
	virtual void OnCollision(BaseEntity* anEntity) {}
	virtual bool CollidesWith(BaseEntity* anEntity) { return (SDLMaths::Distance(myPosition, anEntity->GetPosition()) < 8.f); }

protected:
	std::string myName;
	SDL_FPoint myPosition;
	Texture* myTexture;

	Drawer* myDrawer;

	float myScale;

	bool markForDelete;
};

#endif // BASEENTITY_H