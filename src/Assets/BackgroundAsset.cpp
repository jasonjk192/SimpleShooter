#include "Assets/BackgroundAsset.h"

BackgroundAsset::BackgroundAsset()
{}

BackgroundAsset::BackgroundAsset(Drawer* aDrawer)
{
	Texture* myBackgroundTexture = new Texture(aDrawer->GetRenderer(), ".\\data\\SpaceShooterAssetPack_BackGrounds.png");
	ExtractBackgroundTextures(aDrawer, myBackgroundTexture);
	delete myBackgroundTexture;
}

BackgroundAsset::~BackgroundAsset()
{
	for (int i = myBGTextures.size() - 1; i >= 0; i--)
		delete myBGTextures[i];
	myBGTextures.clear();
}

void BackgroundAsset::ExtractBackgroundTextures(Drawer* aDrawer, Texture* myBackgroundTexture)
{
	for (int i = 0; i < 6; i++)
		myBGTextures.push_back(new Texture(aDrawer->GetRenderer(), myBackgroundTexture, new SDL_Rect{ 128 * (i % 3) + 1 , 256 * (i / 3) + 1 , 127, 255 }, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET));
}