#ifndef BACKGROUNDASSET_H
#define BACKGROUNDASSET_H

#include "Texture.h"
#include "Drawer.h"

#include <vector>
#include <iostream>

class BackgroundAsset
{
public:
    BackgroundAsset(const BackgroundAsset& obj) = delete;
    void operator=(BackgroundAsset const& obj) = delete;

    static BackgroundAsset& GetInstance(Drawer* aDrawer = nullptr)
    {
        static BackgroundAsset myInstance(aDrawer);
        return myInstance;
    }

    ~BackgroundAsset();

    Texture* GetBackgroundTexture(int anIndex) { return myBGTextures[anIndex]; }

    void Draw(Drawer* aDrawer, int anIndex = 0, int aCellX = 0, int aCellY = 0);

private:
    BackgroundAsset();
    BackgroundAsset(Drawer* aDrawer);

    void ExtractBackgroundTextures(Drawer* aDrawer, Texture* myBackgroundTexture);

    std::vector<Texture*> myBGTextures;
};

#endif // BACKGROUNDASSET_H