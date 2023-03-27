#ifndef PROJECTILEASSET_H
#define PROJECTILEASSET_H

#include "Texture.h"
#include "Drawer.h"

#include <iostream>
#include <vector>

class ProjectileAsset
{
public:
    ~ProjectileAsset();

    ProjectileAsset(const ProjectileAsset& obj) = delete;
    void operator=(ProjectileAsset const& obj) = delete;

    static ProjectileAsset& GetInstance(Drawer* aDrawer = nullptr)
    {
        static ProjectileAsset myInstance(aDrawer);
        return myInstance;
    }

    void Draw(Drawer* aDrawer, int anIndex = 0, int aCellX = 0, int aCellY = 0);

    Texture* GetProjectileTexture(int anIndex = 0) { return myProjectileTexture[anIndex]; }
    Texture* GetIconTexture(int anIndex = 0) { return myIconTexture[anIndex]; }
    Texture* GetBeamTexture(int anIndex = 0) { return myBeamTexture[anIndex]; }

private:
    ProjectileAsset();
    ProjectileAsset(Drawer* aDrawer);

    std::vector<Texture*> myProjectileTexture;
    std::vector<Texture*> myIconTexture;
    std::vector<Texture*> myBeamTexture;

    void ExtractProjectileElements(Drawer* aDrawer, Texture* aShipTexture);
    void ExtractIconElements(Drawer* aDrawer, Texture* aShipTexture);
    void ExtractBeamElements(Drawer* aDrawer, Texture* aShipTexture);
};

#endif // PROJECTILEASSET_H