#ifndef UIASSET_H
#define UIASSET_H

#include "Texture.h"
#include "Drawer.h"

#include <iostream>
#include <vector>

class UIAsset
{
public:
    ~UIAsset();

    UIAsset(const UIAsset& obj) = delete;
    void operator=(UIAsset const& obj) = delete;

    static UIAsset& GetInstance(Drawer* aDrawer = nullptr)
    {
        static UIAsset myInstance(aDrawer);
        return myInstance;
    }

    void Draw(Drawer* aDrawer, int anIndex = 0, int aCellX = 0, int aCellY = 0);
    void DrawWindow(Drawer* aDrawer, int anIndex = 0, int aCellX = 0, int aCellY = 0, int aSizeX = 8, int aSizeY = 8);

    Texture* GetTexture() { return myUITexture; }
    SDL_Rect* GetButtonDefaultRegion(int anIndex = 0) { return myButtonTexture[anIndex * 3]; }
    SDL_Rect* GetButtonHoverRegion(int anIndex = 0) { return myButtonTexture[anIndex * 3 + 1]; }
    SDL_Rect* GetButtonPressedRegion(int anIndex = 0) { return myButtonTexture[anIndex * 3 + 2]; }

private:
    UIAsset();
    UIAsset(Drawer* aDrawer);

    std::vector<SDL_Rect*> myWindowTexture;
    std::vector<SDL_Rect*> myButtonTexture;

    void ExtractWindowElements(Drawer* aDrawer, Texture* UITexture);
    void ExtractButtonElements(Drawer* aDrawer, Texture* UITexture);
    void ExtractIconElements(Drawer* aDrawer, Texture* UITexture);

    Texture* myUITexture;
};

#endif // UIASSET_H