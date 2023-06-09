#ifndef GAMECHARACTERENTITY_H
#define GAMECHARACTERENTITY_H

#include "DynamicEntity.h"

class GameCharacterEntity : public DynamicEntity
{
public:
	GameCharacterEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer): DynamicEntity(aPosition,aTexture,aDrawer) {}
	~GameCharacterEntity(void) {}

	virtual void ChangeHealth(int aValue) { currentHealth += aValue; currentHealth = std::min(std::max(0, currentHealth), myMaxHealth); if (currentHealth == 0) markForDelete = true; else markForDelete = false; }
	int GetHealth() const { return currentHealth; }
	bool IsDead() const { return isDead; }

protected:
	float myShootCooldown = 1.f;
	float currentShootCooldown = 0.f;

	int myMaxHealth = 1;
	int currentHealth = 1;

	bool isDead = false;
};

#endif // GAMECHARACTERENTITY_H