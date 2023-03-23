#include "StateMachine.h"
#include "Drawer.h"

#include "States/StartState.h"
#include "States/PlayState.h"
#include "States/GameLostState.h"
#include "States/GameWonState.h"
#include "States/TransitionState.h"

#include "SDL_image.h"
#include "SDL_ttf.h"

#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600

int main(int argc, char* argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized!" << std::endl << "SDL_Error: " << SDL_GetError() << std::endl;
        return 0;
    }

    SDL_Window* window = SDL_CreateWindow("Simple Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!window)
    {
        std::cout << "Window could not be created!" << std::endl << "SDL_Error: " << SDL_GetError() << std::endl;
        return 0;
    }

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	if (TTF_Init() == -1)
	{
		std::cout << "TTF could not be initialized!" << std::endl << "SDL_Error: " << SDL_GetError() << std::endl;
		return 0;
	}

	Drawer* drawer = new Drawer(window, renderer);
	UIAsset* uiAsset = &UIAsset::GetInstance(drawer);
	BackgroundAsset* bgAsset = &BackgroundAsset::GetInstance(drawer);
	ShipAsset* shipAsset = &ShipAsset::GetInstance(drawer);
	MiscAsset* miscAsset = &MiscAsset::GetInstance(drawer);

	StateMachine* stateMachine = new StateMachine();
	stateMachine->Add(new StartState(stateMachine, drawer));
	stateMachine->Add(new PlayState(stateMachine, drawer));
	stateMachine->Add(new GameLostState(stateMachine, drawer));
	stateMachine->Add(new GameWonState(stateMachine, drawer));
	stateMachine->Add(new TransitionState(stateMachine, drawer));
	stateMachine->Change("Start");

	float lastFrame = (float)SDL_GetTicks() * 0.001f;

	SDL_Event event;
	
	while (SDL_PollEvent(&event) >= 0)
	{
		float currentFrame = (float)SDL_GetTicks() * 0.001f;
		float elapsedTime = currentFrame - lastFrame;

		if (!stateMachine->HandleEvents(&event))
			break;
		if (!stateMachine->Update(elapsedTime))
			break;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		stateMachine->Draw();

		lastFrame = currentFrame;

		SDL_RenderPresent(renderer);
		SDL_Delay(1);
	}

    SDL_Quit();
	delete drawer;
	delete stateMachine;

    return EXIT_SUCCESS;
}
