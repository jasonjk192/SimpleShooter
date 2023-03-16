#ifndef SHIPASSET_H
#define SHIPASSET_H

#include "Texture.h"
#include "Drawer.h"

#include <iostream>
#include <vector>

class ShipAsset
{
public:
    ~ShipAsset();

    ShipAsset(const ShipAsset& obj) = delete;
    void operator=(ShipAsset const& obj) = delete;

    static ShipAsset& GetInstance(Drawer* aDrawer = nullptr)
    {
        static ShipAsset myInstance(aDrawer);
        return myInstance;
    }

    void Draw(Drawer* aDrawer, int anIndex = 0, int aCellX = 0, int aCellY = 0);

    Texture* GetPlayerTexture(int anIndex = 0) { return myPlayerTexture[anIndex]; }
    Texture* GetEnemyTexture(int anIndex = 0) { return myEnemyTexture[anIndex]; }
    Texture* GetBossTexture(int anIndex = 0) { return myBossTexture[anIndex]; }

private:
    ShipAsset();
    ShipAsset(Drawer* aDrawer);

    std::vector<Texture*> myPlayerTexture;
    std::vector<Texture*> myEnemyTexture;
    std::vector<Texture*> myBossTexture;

    void ExtractPlayerElements(Drawer* aDrawer, Texture* aShipTexture);
    void ExtractEnemyElements(Drawer* aDrawer, Texture* aShipTexture);
    void ExtractBossElements(Drawer* aDrawer, Texture* aShipTexture);
};

#endif // SHIPASSET_H