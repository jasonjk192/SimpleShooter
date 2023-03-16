#include "Assets/ShipAsset.h"

ShipAsset::~ShipAsset()
{
    
    for (int i = myPlayerTexture.size() - 1; i >= 0; i--)
        delete myPlayerTexture[i];
    for (int i = myEnemyTexture.size() - 1; i >= 0; i--)
        delete myEnemyTexture[i];
    for (int i = myBossTexture.size() - 1; i >= 0; i--)
        delete myBossTexture[i];
    myPlayerTexture.clear();
    myEnemyTexture.clear();
    myBossTexture.clear();
}

void ShipAsset::Draw(Drawer* aDrawer, int anIndex, int aCellX, int aCellY)
{
    //aDrawer->Draw(myShipTexture, myBossRegion[anIndex], new SDL_Rect{ aCellX, aCellY , myBossRegion[anIndex]->w, myBossRegion[anIndex]->h });
    aDrawer->Draw(myPlayerTexture[anIndex], aCellX, aCellY);
    //aDrawer->Draw(myShipTexture, aCellX, aCellY);
}

ShipAsset::ShipAsset()
{}

ShipAsset::ShipAsset(Drawer* aDrawer)
{
    Texture* myShipTexture = new Texture(aDrawer->GetRenderer(), ".\\data\\SpaceShooterAssetPack_Ships.png");
    ExtractPlayerElements(aDrawer, myShipTexture);
    ExtractEnemyElements(aDrawer, myShipTexture);
    ExtractBossElements(aDrawer, myShipTexture);
    delete myShipTexture;
}

void ShipAsset::ExtractPlayerElements(Drawer* aDrawer, Texture* aShipTexture)
{
    for (int i = 0; i < 5; i++)
    {
        myPlayerTexture.push_back(new Texture(aDrawer->GetRenderer(), aShipTexture, new SDL_Rect{ 0, 8 * i, 8, 8 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
        myPlayerTexture.push_back(new Texture(aDrawer->GetRenderer(), aShipTexture, new SDL_Rect{ 8, 8 * i, 8, 8 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
        myPlayerTexture.push_back(new Texture(aDrawer->GetRenderer(), aShipTexture, new SDL_Rect{ 16, 8 * i, 8, 8 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
    }
}

void ShipAsset::ExtractEnemyElements(Drawer* aDrawer, Texture* aShipTexture)
{
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            myEnemyTexture.push_back(new Texture(aDrawer->GetRenderer(), aShipTexture, new SDL_Rect{ 32 + j * 8, 8 * i, 8, 8 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
}

void ShipAsset::ExtractBossElements(Drawer* aDrawer, Texture* aShipTexture)
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            myBossTexture.push_back(new Texture(aDrawer->GetRenderer(), aShipTexture, new SDL_Rect{ 32 + j * 16, 48 + 16 * i, 16, 16 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
}