#ifndef BACKGROUNDASSET_H
#define BACKGROUNDASSET_H

#include "Texture.h"
#include "Drawer.h"

#include <iostream>

class BackgroundAsset
{
private:
    Texture* myBackgroundTexture;
    BackgroundAsset(Drawer* aDrawer)
    {
        myBackgroundTexture = new Texture(aDrawer->GetRenderer(), ".\\data\\SpaceShooterAssetPack_BackGrounds.png");
    }

public:
    BackgroundAsset(const BackgroundAsset& obj) = delete;
    void operator=(BackgroundAsset const& obj) = delete;

    static BackgroundAsset& GetInstance(Drawer* aDrawer = nullptr)
    {
        static BackgroundAsset myInstance(aDrawer);
        return myInstance;
    }

    ~BackgroundAsset()
    {
        delete myBackgroundTexture;
    }

    void GetCroppedRectangle(int anIndex, SDL_Rect* aCroppedRect)
    {
        int inX = anIndex % 3;
        int inY = anIndex / 3;
        aCroppedRect->x = 128 * inX + 1;
        aCroppedRect->y = 256 * inY + 1;
        aCroppedRect->w = 127;
        aCroppedRect->h = 255;
    }

    Texture* GetTexture()
    {
        return myBackgroundTexture;
    }

    void Draw(Drawer* aDrawer, int anIndex = 0, int aCellX = 0, int aCellY = 0)
    {
        SDL_Rect bgRect;
        GetCroppedRectangle(anIndex, &bgRect);
        SDL_Rect dstRect{0,0,127,255};
        aDrawer->Draw(myBackgroundTexture, &bgRect, &dstRect);
    }
};

#endif // BACKGROUNDASSET_H