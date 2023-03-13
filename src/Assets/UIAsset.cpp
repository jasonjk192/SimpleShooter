#include "Assets/UIAsset.h"

UIAsset::UIAsset()
{}

UIAsset::UIAsset(Drawer* aDrawer)
{
    myUITexture = new Texture(aDrawer->GetRenderer(), ".\\data\\SpaceShooterAssetPack_IU.png");
    ExtractWindowElements(aDrawer, myUITexture);
    ExtractButtonElements(aDrawer, myUITexture);
}

UIAsset::~UIAsset()
{
    delete myUITexture;
    for (int i = myWindowTexture.size() - 1; i >= 0; i--)
        delete myWindowTexture[i];
    for (int i = myButtonTexture.size() - 1; i >= 0; i--)
        delete myButtonTexture[i];
    myWindowTexture.clear();
    myButtonTexture.clear();
}

void UIAsset::Draw(Drawer* aDrawer, int anIndex, int aCellX, int aCellY)
{
    aDrawer->Draw(myUITexture, myWindowTexture[anIndex], new SDL_Rect{ aCellX, aCellY , myWindowTexture[anIndex]->w, myWindowTexture[anIndex]->h });
    //aDrawer->Draw(myButtonTexture[anIndex], aCellX, aCellY);
}

void UIAsset::DrawWindow(Drawer* aDrawer, int anIndex, int aCellX, int aCellY, int aSizeX, int aSizeY)
{
    aSizeX = aSizeX < 0 ? 0 : aSizeX;
    aSizeY = aSizeY < 0 ? 0 : aSizeY;

    SDL_Rect croppedRect{ myWindowTexture[anIndex]->x, myWindowTexture[anIndex]->y, 3, 3 };
    SDL_Rect dstRect{ aCellX, aCellY, 3, 3 };
    aDrawer->Draw(myUITexture, &croppedRect, &dstRect);
    croppedRect = { myWindowTexture[anIndex]->x + 13, myWindowTexture[anIndex]->y, 3, 3 };
    dstRect = { aSizeX + aCellX, aCellY, 3, 3 };
    aDrawer->Draw(myUITexture, &croppedRect, &dstRect);
    croppedRect = { myWindowTexture[anIndex]->x, myWindowTexture[anIndex]->y + 13, 3, 3 };
    dstRect = { aCellX, aCellY + aSizeY, 3, 3 };
    aDrawer->Draw(myUITexture, &croppedRect, &dstRect);
    croppedRect = { myWindowTexture[anIndex]->x + 13, myWindowTexture[anIndex]->y + 13, 3, 3 };
    dstRect = { aSizeX + aCellX, aCellY + aSizeY, 3, 3 };
    aDrawer->Draw(myUITexture, &croppedRect, &dstRect);

    if (aSizeX > 0)
    {
        croppedRect = { myWindowTexture[anIndex]->x + 3, myWindowTexture[anIndex]->y, 1, 3 };
        dstRect = { aCellX + 3, aCellY, aSizeX - 3 , 3 };
        aDrawer->Draw(myUITexture, &croppedRect, &dstRect);
        croppedRect = { myWindowTexture[anIndex]->x + 3, myWindowTexture[anIndex]->y + 13, 1, 3 };
        dstRect = { aCellX + 3, aCellY + aSizeY , aSizeX - 3, 3 };
        aDrawer->Draw(myUITexture, &croppedRect, &dstRect);
    }
    if (aSizeY > 0)
    {
        croppedRect = { myWindowTexture[anIndex]->x, myWindowTexture[anIndex]->y + 3, 3, 1 };
        dstRect = { aCellX, aCellY + 3 , 3, aSizeY - 3 };
        aDrawer->Draw(myUITexture, &croppedRect, &dstRect);
        croppedRect = { myWindowTexture[anIndex]->x + 13, myWindowTexture[anIndex]->y+ 3, 3, 1 };
        dstRect = { aCellX + aSizeX, aCellY + 3, 3, aSizeY - 3 };
        aDrawer->Draw(myUITexture, &croppedRect, &dstRect);
    }
    croppedRect = { myWindowTexture[anIndex]->x + 3, myWindowTexture[anIndex]->y+ 3, 1, 1 };
    dstRect = { aCellX + 3, aCellY + 3, aSizeX - 3, aSizeY - 3 };
    aDrawer->Draw(myUITexture, &croppedRect, &dstRect);
    
}

void UIAsset::ExtractWindowElements(Drawer* aDrawer, Texture* UITexture)
{
    for (int i = 0; i < 5; i++)
    {
        myWindowTexture.push_back(new SDL_Rect{ 0, 16 * i, 16, 16 });
        myWindowTexture.push_back(new SDL_Rect{ 16, 16 * i, 16, 16 });
    }
}

void UIAsset::ExtractButtonElements(Drawer* aDrawer, Texture* UITexture)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            myButtonTexture.push_back(new SDL_Rect{ 88 + j * 37, i * 14, 12, 13 });
            myButtonTexture.push_back(new SDL_Rect{ 100 + j * 37, i * 14, 12, 13 });
            myButtonTexture.push_back(new SDL_Rect{ 112 + j * 37, i * 14, 12, 13 });
        }
    }
}