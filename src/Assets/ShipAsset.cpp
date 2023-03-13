#include "Assets/ShipAsset.h"

ShipAsset::~ShipAsset()
{
    delete myShipTexture;
    for (int i = myPlayerRegion.size() - 1; i >= 0; i--)
        delete myPlayerRegion[i];
    for (int i = myEnemyRegion.size() - 1; i >= 0; i--)
        delete myEnemyRegion[i];
    myPlayerRegion.clear();
    myEnemyRegion.clear();
    myBossRegion.clear();
}

void ShipAsset::Draw(Drawer* aDrawer, int anIndex, int aCellX, int aCellY)
{
    aDrawer->Draw(myShipTexture, myBossRegion[anIndex], new SDL_Rect{ aCellX, aCellY , myBossRegion[anIndex]->w, myBossRegion[anIndex]->h });
}

ShipAsset::ShipAsset()
{}

ShipAsset::ShipAsset(Drawer* aDrawer)
{
    myShipTexture = new Texture(aDrawer->GetRenderer(), ".\\data\\SpaceShooterAssetPack_Ships.png");
    ExtractPlayerElements(aDrawer, myShipTexture);
    ExtractEnemyElements(aDrawer, myShipTexture);
    ExtractBossElements(aDrawer, myShipTexture);
}

void ShipAsset::ExtractPlayerElements(Drawer* aDrawer, Texture* aShipTexture)
{
    for (int i = 0; i < 5; i++)
    {
        myPlayerRegion.push_back(new SDL_Rect{ 0, 8 * i, 8, 8 });
        myPlayerRegion.push_back(new SDL_Rect{ 8, 8 * i, 8, 8 });
        myPlayerRegion.push_back(new SDL_Rect{ 16, 8 * i, 8, 8 });
    }
}

void ShipAsset::ExtractEnemyElements(Drawer* aDrawer, Texture* aShipTexture)
{
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            myEnemyRegion.push_back(new SDL_Rect{ 32 + j * 8, 8 * i, 8, 8 });
}

void ShipAsset::ExtractBossElements(Drawer* aDrawer, Texture* aShipTexture)
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            myBossRegion.push_back(new SDL_Rect{ 32 + j * 16, 48 + 16 * i, 16, 16 });
}