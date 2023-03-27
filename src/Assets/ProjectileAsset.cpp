#include "Assets/ProjectileAsset.h"

ProjectileAsset::~ProjectileAsset()
{
    for (int i = myProjectileTexture.size() - 1; i >= 0; i--)
        delete myProjectileTexture[i];
    for (int i = myIconTexture.size() - 1; i >= 0; i--)
        delete myIconTexture[i];
    for (int i = myBeamTexture.size() - 1; i >= 0; i--)
        delete myBeamTexture[i];
    myProjectileTexture.clear();
    myIconTexture.clear();
    myBeamTexture.clear();
}

void ProjectileAsset::Draw(Drawer* aDrawer, int anIndex, int aCellX, int aCellY)
{
    //aDrawer->Draw(myShipTexture, myBossRegion[anIndex], new SDL_Rect{ aCellX, aCellY , myBossRegion[anIndex]->w, myBossRegion[anIndex]->h });
    aDrawer->Draw(myProjectileTexture[anIndex], aCellX, aCellY);
    //aDrawer->Draw(myShipTexture, aCellX, aCellY);
}

ProjectileAsset::ProjectileAsset()
{}

ProjectileAsset::ProjectileAsset(Drawer* aDrawer)
{
    Texture* myProjTexture = new Texture(aDrawer->GetRenderer(), ".\\data\\SpaceShooterAssetPack_Projectiles.png");
    ExtractProjectileElements(aDrawer, myProjTexture);
    ExtractIconElements(aDrawer, myProjTexture);
    ExtractBeamElements(aDrawer, myProjTexture);
    delete myProjTexture;
}

void ProjectileAsset::ExtractProjectileElements(Drawer* aDrawer, Texture* aProjTexture)
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 6; j++)
            myProjectileTexture.push_back(new Texture(aDrawer->GetRenderer(), aProjTexture, new SDL_Rect{ j * 8, 8 * i, 8, 8 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
}

void ProjectileAsset::ExtractIconElements(Drawer* aDrawer, Texture* aProjTexture)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 6; j++)
            myIconTexture.push_back(new Texture(aDrawer->GetRenderer(), aProjTexture, new SDL_Rect{ j * 8, 40 + 8 * i, 8, 8 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
}

void ProjectileAsset::ExtractBeamElements(Drawer* aDrawer, Texture* aProjTexture)
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 6; j++)
            myBeamTexture.push_back(new Texture(aDrawer->GetRenderer(), aProjTexture, new SDL_Rect{ j * 8, 64 + 8 * i, 8, 8 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
}