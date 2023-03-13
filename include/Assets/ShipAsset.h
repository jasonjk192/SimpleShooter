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

    Texture* GetTexture() { return myShipTexture; }
    SDL_Rect* GetPlayerRegion(int anIndex = 0) { return myPlayerRegion[anIndex * 3]; }
    SDL_Rect* GetEnemyRegion(int anIndex = 0) { return myEnemyRegion[anIndex]; }
    SDL_Rect* GetBossRegion(int anIndex = 0) { return myBossRegion[anIndex]; }

private:
    ShipAsset();
    ShipAsset(Drawer* aDrawer);

    std::vector<SDL_Rect*> myPlayerRegion;
    std::vector<SDL_Rect*> myEnemyRegion;
    std::vector<SDL_Rect*> myBossRegion;

    void ExtractPlayerElements(Drawer* aDrawer, Texture* aShipTexture);
    void ExtractEnemyElements(Drawer* aDrawer, Texture* aShipTexture);
    void ExtractBossElements(Drawer* aDrawer, Texture* aShipTexture);

    Texture* myShipTexture;
};

#endif // SHIPASSET_H