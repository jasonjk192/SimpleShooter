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

    Texture* GetButtonTexture(int anIndex) { return myButtonTexture[anIndex]; }
    Texture* GetIconTexture(int anIndex) { return myIconTexture[anIndex]; }
    Texture* GetBorderTexture(int anIndex) { return myBorderTexture[anIndex]; }

private:
    UIAsset();
    UIAsset(Drawer* aDrawer);

    std::vector<Texture*> myBorderTexture;
    std::vector<Texture*> myButtonTexture;
    std::vector<Texture*> myIconTexture;

    void ExtractBorderElements(Drawer* aDrawer, Texture* aUITexture);
    void ExtractButtonElements(Drawer* aDrawer, Texture* aUITexture);
    void ExtractIconElements(Drawer* aDrawer, Texture* aUITexture);
};

#endif // UIASSET_H