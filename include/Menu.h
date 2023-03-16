#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>

#include "Texture.h"
#include "Drawer.h"

#include "Assets/UIAsset.h"

class Menu
{
public:
	static enum class Align { LEFT, CENTRE, RIGHT };

	Menu(Drawer* aDrawer);
	~Menu(void);

	void AddItem(const char* anItem);
	void RemoveItem(int anIndex);
	void Clear();

	bool HandleEvents(SDL_Event* event);
	void OnItemSelected(int index);

	void Draw(int anIndex = 0);
	void DrawSelectionBox(int anIndex = 0);

	void SetAlignment(Align anAlignment) { myAlignment = anAlignment; }
	void SetOffset(int anOffsetX = 0, int anOffsetY = 0) { myOffsetX = anOffsetX; myOffsetY = anOffsetY; }
	void SetSpacing(int anItemSpacing = 0) { myItemSpacing = anItemSpacing; }
	void SetActive(bool anIsActive) { isActive = anIsActive; }

	void SetCallback(void(*aCallback)(int anIndex, void* context), void* aContext) { callback = aCallback; myContext = aContext; }

	int GetMenuWidth() { return maxSizeX; }
	int GetMenuHeight() { return myItems.size() * maxSizeY; }

	int myCurrentSelection;
	
private:

	Drawer* myDrawer;
	std::vector<Texture*> myItems;
	Align myAlignment;

	int myOffsetX, myOffsetY;
	int maxSizeX, maxSizeY;
	int myItemSpacing;

	void (*callback)(int anIndex, void* aContext);
	void* myContext;
	bool isItemSelected, isActive;

	int CalculatePositionX(int anIndex);
	int CalculatePositionY(int anIndex);

	UIAsset* myUIAsset;
	
};

#endif // MENU_H