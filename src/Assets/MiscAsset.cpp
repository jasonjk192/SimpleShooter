#include "Assets/MiscAsset.h"

MiscAsset::~MiscAsset()
{
    for (int i = myFlameTexture.size() - 1; i >= 0; i--)
        delete myFlameTexture[i];
    for (int i = myExplosionTexture.size() - 1; i >= 0; i--)
        delete myExplosionTexture[i];
    for (int i = myIconTexture.size() - 1; i >= 0; i--)
        delete myIconTexture[i];
    myFlameTexture.clear();
    myExplosionTexture.clear();
    myIconTexture.clear();
}

void MiscAsset::Draw(Drawer* aDrawer, int anIndex, int aCellX, int aCellY)
{
    //aDrawer->Draw(myShipTexture, myBossRegion[anIndex], new SDL_Rect{ aCellX, aCellY , myBossRegion[anIndex]->w, myBossRegion[anIndex]->h });
    //aDrawer->Draw(myPlayerTexture[anIndex], aCellX, aCellY);
    //aDrawer->Draw(myShipTexture, aCellX, aCellY);
}

MiscAsset::MiscAsset()
{}

MiscAsset::MiscAsset(Drawer* aDrawer)
{
    Texture* myMiscTexture = new Texture(aDrawer->GetRenderer(), ".\\data\\SpaceShooterAssetPack_Miscellaneous.png");
    ExtractFlameElements(aDrawer, myMiscTexture);
    ExtractExplosionElements(aDrawer, myMiscTexture);
    ExtractIconElements(aDrawer, myMiscTexture);
    delete myMiscTexture;
}

void MiscAsset::ExtractFlameElements(Drawer* aDrawer, Texture* aShipTexture)
{
    for (int i = 0; i < 4; i++)
    {
        myFlameTexture.push_back(new Texture(aDrawer->GetRenderer(), aShipTexture, new SDL_Rect{ 40, 8 * i, 8, 8 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
        myFlameTexture.push_back(new Texture(aDrawer->GetRenderer(), aShipTexture, new SDL_Rect{ 48, 8 * i, 8, 8 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
        myFlameTexture.push_back(new Texture(aDrawer->GetRenderer(), aShipTexture, new SDL_Rect{ 56, 8 * i, 8, 8 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
        myFlameTexture.push_back(new Texture(aDrawer->GetRenderer(), aShipTexture, new SDL_Rect{ 64, 8 * i, 8, 8 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
    }
    for (int i = 0; i < 4; i++)
    {
        myFlameTexture.push_back(new Texture(aDrawer->GetRenderer(), aShipTexture, new SDL_Rect{ 72, 8 * i, 8, 8 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
        myFlameTexture.push_back(new Texture(aDrawer->GetRenderer(), aShipTexture, new SDL_Rect{ 80, 8 * i, 8, 8 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
        myFlameTexture.push_back(new Texture(aDrawer->GetRenderer(), aShipTexture, new SDL_Rect{ 88, 8 * i, 8, 8 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
        myFlameTexture.push_back(new Texture(aDrawer->GetRenderer(), aShipTexture, new SDL_Rect{ 96, 8 * i, 8, 8 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
    }
}

void MiscAsset::ExtractExplosionElements(Drawer* aDrawer, Texture* aShipTexture)
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            myExplosionTexture.push_back(new Texture(aDrawer->GetRenderer(), aShipTexture, new SDL_Rect{ 40 + j * 8, 48 + 8 * i, 8, 8 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
}

void MiscAsset::ExtractIconElements(Drawer* aDrawer, Texture* aShipTexture)
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 4; j++)
            myIconTexture.push_back(new Texture(aDrawer->GetRenderer(), aShipTexture, new SDL_Rect{ j * 8,  8 * i, 8, 8 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
}