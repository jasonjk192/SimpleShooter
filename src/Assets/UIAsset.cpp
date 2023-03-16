#include "Assets/UIAsset.h"

UIAsset::UIAsset()
{}

UIAsset::UIAsset(Drawer* aDrawer)
{
    Texture* myUITexture = new Texture(aDrawer->GetRenderer(), ".\\data\\SpaceShooterAssetPack_IU.png");
    ExtractBorderElements(aDrawer, myUITexture);
    ExtractButtonElements(aDrawer, myUITexture);
    delete myUITexture;
}

UIAsset::~UIAsset()
{
    for (int i = myBorderTexture.size() - 1; i >= 0; i--)
        delete myBorderTexture[i];
    for (int i = myButtonTexture.size() - 1; i >= 0; i--)
        delete myButtonTexture[i];
    myBorderTexture.clear();
    myButtonTexture.clear();
}

void UIAsset::Draw(Drawer* aDrawer, int anIndex, int aCellX, int aCellY)
{
    //aDrawer->Draw(myUITexture, myBorderTexture[anIndex], new SDL_Rect{ aCellX, aCellY , myWindowTexture[anIndex]->w, myWindowTexture[anIndex]->h });
    //aDrawer->Draw(myButtonTexture[anIndex], aCellX, aCellY);
}

void UIAsset::DrawWindow(Drawer* aDrawer, int anIndex, int aCellX, int aCellY, int aSizeX, int aSizeY)
{
    aSizeX = aSizeX < 0 ? 0 : aSizeX;
    aSizeY = aSizeY < 0 ? 0 : aSizeY;

    SDL_Rect croppedRect{ 0, 0, 3, 3 };
    SDL_Rect dstRect{ aCellX, aCellY, 3, 3 };
    aDrawer->Draw(myBorderTexture[anIndex], &croppedRect, &dstRect);
    croppedRect = { 13, 0, 3, 3 };
    dstRect = { aSizeX + aCellX, aCellY, 3, 3 };
    aDrawer->Draw(myBorderTexture[anIndex], &croppedRect, &dstRect);
    croppedRect = { 0, 13, 3, 3 };
    dstRect = { aCellX, aCellY + aSizeY, 3, 3 };
    aDrawer->Draw(myBorderTexture[anIndex], &croppedRect, &dstRect);
    croppedRect = { 13, 13, 3, 3 };
    dstRect = { aSizeX + aCellX, aCellY + aSizeY, 3, 3 };
    aDrawer->Draw(myBorderTexture[anIndex], &croppedRect, &dstRect);

    if (aSizeX > 0)
    {
        croppedRect = { 3, 0, 1, 3 };
        dstRect = { aCellX + 3, aCellY, aSizeX - 3 , 3 };
        aDrawer->Draw(myBorderTexture[anIndex], &croppedRect, &dstRect);
        croppedRect = { 3, 13, 1, 3 };
        dstRect = { aCellX + 3, aCellY + aSizeY , aSizeX - 3, 3 };
        aDrawer->Draw(myBorderTexture[anIndex], &croppedRect, &dstRect);
    }
    if (aSizeY > 0)
    {
        croppedRect = { 0, 3, 3, 1 };
        dstRect = { aCellX, aCellY + 3 , 3, aSizeY - 3 };
        aDrawer->Draw(myBorderTexture[anIndex], &croppedRect, &dstRect);
        croppedRect = { 13, 3, 3, 1 };
        dstRect = { aCellX + aSizeX, aCellY + 3, 3, aSizeY - 3 };
        aDrawer->Draw(myBorderTexture[anIndex], &croppedRect, &dstRect);
    }
    croppedRect = { 3, 3, 1, 1 };
    dstRect = { aCellX + 3, aCellY + 3, aSizeX - 3, aSizeY - 3 };
    aDrawer->Draw(myBorderTexture[anIndex], &croppedRect, &dstRect);
    
}

void UIAsset::ExtractBorderElements(Drawer* aDrawer, Texture* aUITexture)
{
    for (int i = 0; i < 5; i++)
    {
        myBorderTexture.push_back(new Texture(aDrawer->GetRenderer(), aUITexture, new SDL_Rect{ 0, 16 * i, 16, 16 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
        myBorderTexture.push_back(new Texture(aDrawer->GetRenderer(), aUITexture, new SDL_Rect{ 16, 16 * i, 16, 16 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
    }
}

void UIAsset::ExtractButtonElements(Drawer* aDrawer, Texture* aUITexture)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            myButtonTexture.push_back(new Texture(aDrawer->GetRenderer(), aUITexture, new SDL_Rect{ 88 + j * 37, i * 14, 12, 13 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
            myButtonTexture.push_back(new Texture(aDrawer->GetRenderer(), aUITexture, new SDL_Rect{ 100 + j * 37, i * 14, 12, 13 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
            myButtonTexture.push_back(new Texture(aDrawer->GetRenderer(), aUITexture, new SDL_Rect{ 112 + j * 37, i * 14, 12, 13 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
        }
    }
}