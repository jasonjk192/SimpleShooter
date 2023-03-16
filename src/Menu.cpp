#include "Menu.h"

Menu::Menu(Drawer* aDrawer):
	myAlignment(Align::CENTRE),
    myOffsetX(0),
    myOffsetY(0),
    myCurrentSelection(-1),
    myItemSpacing(0),
    maxSizeX(0),
    maxSizeY(0),
    myDrawer(aDrawer),
    isItemSelected(false),
    isActive(true),
    callback(nullptr),
    myContext(nullptr)
{
    myUIAsset = &UIAsset::GetInstance();
}

Menu::~Menu(void)
{
	myItems.clear();
}

void Menu::AddItem(const char* anItem)
{
    Texture* texture = new Texture(myDrawer->GetRenderer(), anItem, ".\\data\\fonts\\NoContinue-Vogl.ttf");
    myItems.emplace_back(texture);
    SDL_Point* itemSize = texture->GetSize();
    if (itemSize->x > maxSizeX)
        maxSizeX = itemSize->x;
    if (itemSize->y > maxSizeY)
        maxSizeY = itemSize->y;
}

void Menu::RemoveItem(int anIndex)
{

}

void Menu::Clear()
{
    myCurrentSelection = 0;
    for (int i = myItems.size() - 1; i >= 0; i--)
        delete myItems[i];
    myItems.clear();
}

bool Menu::HandleEvents(SDL_Event* event)
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    switch (event->type)
    {
    case SDL_MOUSEMOTION:
        if (x > myOffsetX && x < (myOffsetX + maxSizeX) && y > myOffsetY && y < (myOffsetY + maxSizeY*myItems.size()))
        {
            if(!isItemSelected)
                myCurrentSelection = (y - myOffsetY) / maxSizeY;
        }
        break;

    case SDL_MOUSEBUTTONDOWN:
        if (x > myOffsetX && x < (myOffsetX + maxSizeX) && y > myOffsetY && y < (myOffsetY + maxSizeY * myItems.size()))
        {
            myCurrentSelection = (y - myOffsetY) / maxSizeY;
            isItemSelected = true;
        }
        break;

    case SDL_MOUSEBUTTONUP:
        if (isItemSelected)
            OnItemSelected(myCurrentSelection);
        isItemSelected = false;
        break;
    }
    return true;
}

void Menu::OnItemSelected(int index)
{
    if (callback != nullptr)
        callback(index, myContext);
}

void Menu::Draw(int anIndex)
{
    if (isActive)
    {
        int winW, winH;
        myDrawer->GetWindowSize(&winW, &winH);

        myUIAsset->DrawWindow(myDrawer, anIndex, myOffsetX - 2, myOffsetY - 2, maxSizeX + 2, (maxSizeY + 4) * myItems.size());

        int itemSize = myItems.size();
        for (int i = 0; i < itemSize; i++)
        {
            SDL_Point* menuItemSize = myItems[i]->GetSize();
            myDrawer->Draw(myItems[i], CalculatePositionX(i), CalculatePositionY(i));
        }
    }
}

void Menu::DrawSelectionBox(int anIndex)
{
    int itemSize = myItems.size();
    SDL_Point* menuItemSize = myItems[myCurrentSelection]->GetSize();
    myDrawer->SetBlendMode(1);
    myUIAsset->DrawWindow(myDrawer, anIndex, myOffsetX , CalculatePositionY(myCurrentSelection), maxSizeX , menuItemSize->y);
    myDrawer->SetBlendMode(0);
}

int Menu::CalculatePositionX(int anIndex)
{
    if (myAlignment == Align::CENTRE)
        return (maxSizeX - myItems[anIndex]->GetSize()->x) / 2 + myOffsetX;
    else if (myAlignment == Align::RIGHT)
        return maxSizeX - myItems[anIndex]->GetSize()->x + myOffsetX;
    return myOffsetX;
}

int Menu::CalculatePositionY(int anIndex)
{
    return anIndex * (maxSizeY + myItemSpacing) + myOffsetY;
}
