#ifndef MISCASSET_H
#define MISCASSET_H

#include "Texture.h"
#include "Drawer.h"

#include <iostream>
#include <vector>

class MiscAsset
{
public:
    ~MiscAsset();

    MiscAsset(const MiscAsset& obj) = delete;
    void operator=(MiscAsset const& obj) = delete;

    static MiscAsset& GetInstance(Drawer* aDrawer = nullptr)
    {
        static MiscAsset myInstance(aDrawer);
        return myInstance;
    }

    void Draw(Drawer* aDrawer, int anIndex = 0, int aCellX = 0, int aCellY = 0);

    Texture* GetFlameTexture(int anIndex = 0) { return myFlameTexture[anIndex]; }
    Texture* GetExplosionTexture(int anIndex = 0) { return myExplosionTexture[anIndex]; }
    Texture* GetIconTexture(int anIndex = 0) { return myIconTexture[anIndex]; }

private:
    MiscAsset();
    MiscAsset(Drawer* aDrawer);

    std::vector<Texture*> myFlameTexture;
    std::vector<Texture*> myExplosionTexture;
    std::vector<Texture*> myIconTexture;

    void ExtractFlameElements(Drawer* aDrawer, Texture* aShipTexture);
    void ExtractExplosionElements(Drawer* aDrawer, Texture* aShipTexture);
    void ExtractIconElements(Drawer* aDrawer, Texture* aShipTexture);
};

#endif // MISCASSET_H