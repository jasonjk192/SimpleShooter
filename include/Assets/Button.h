#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <string>

#include "Texture.h"
#include "Drawer.h"

class Button
{
public:
    Button():
        callback(nullptr),
        myButtonTexture(nullptr),
        defaultRegion(nullptr),
        hoverRegion(nullptr),
        pressedRegion(nullptr),
        isPressed(false),
        isHovered(false),
        isActive(true),
        offsetX(0),
        offsetY(0),
        myContext(nullptr)
    { }

    Button(Texture* aButtonTex, int anOFfsetX = 0, int anOFfsetY = 0) :
        callback(nullptr),
        myButtonTexture(aButtonTex),
        defaultRegion(nullptr),
        hoverRegion(nullptr),
        pressedRegion(nullptr),
        isPressed(false),
        isHovered(false),
        isActive(true),
        offsetX(anOFfsetX),
        offsetY(anOFfsetY),
        myContext(nullptr)
    { }

    ~Button()
    {
        if(myButtonTexture != nullptr)
            delete myButtonTexture;
    }

    void SetCallback(void(*aCallback)(void* context), void* aContext) { callback = aCallback; myContext = aContext; }
    void SetButtonTexture(Texture* aTexture) { myButtonTexture = aTexture; }
    void SetDefaultRegion(SDL_Rect* aRect) { defaultRegion = aRect; }
    void SetHoverRegion(SDL_Rect* aRect) { hoverRegion = aRect; }
    void SetPressedRegion(SDL_Rect* aRect) { pressedRegion = aRect; }
    void SetActive(bool anIsActive) { isActive = anIsActive; }
    void SetOffset(int anOFfsetX = 0, int anOFfsetY = 0) { offsetX = anOFfsetX; offsetY = anOFfsetY; }

    void Press()
    {
        if (callback != nullptr)
            callback(myContext);
    }

    void Draw(Drawer* aDrawer)
    {
        if (isActive)
        {
            SDL_Rect offset{offsetX, offsetY, defaultRegion->w, defaultRegion->h};
            if (isPressed)
                aDrawer->Draw(myButtonTexture, pressedRegion, &offset);
            else if (isHovered)
                aDrawer->Draw(myButtonTexture, hoverRegion, &offset);
            else
                aDrawer->Draw(myButtonTexture, defaultRegion, &offset);
        }
    }

    bool HandleEvents(SDL_Event* event)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        switch (event->type)
        {
        case SDL_MOUSEMOTION:
            if (x > offsetX && x < (offsetX + defaultRegion->w) && y > offsetY && y < (offsetY + defaultRegion->h))
            {
                isHovered = true;
            }
            else
            {
                isHovered = false;
                isPressed = false;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (x > offsetX && x < (offsetX + defaultRegion->w) && y > offsetY && y < (offsetY + defaultRegion->h))
                isPressed = true;
            break;

        case SDL_MOUSEBUTTONUP:
            if(isPressed)
                Press();
            isPressed = false;
            break;
        }
        return true;
    }
    
private:
    void (*callback)(void* aContext);
    void* myContext;

    bool isPressed, isHovered, isActive;
    int offsetX, offsetY;
    int sizeX, sizeY;

    Texture* myButtonTexture;
    SDL_Rect* defaultRegion;
    SDL_Rect* hoverRegion;
    SDL_Rect* pressedRegion;
};

#endif // BUTTON_H