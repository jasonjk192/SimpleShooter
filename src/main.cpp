#include "StateMachine.h"
#include "Drawer.h"

#include "States/StartState.h"

#include "SDL_image.h"
#include "SDL_ttf.h"

#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_mixer.h>

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600

int main(int argc, char* argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << "Mixer could not be initialized!" << std::endl << "SDL_Error: " << SDL_GetError() << std::endl;
		return 0;
	}

	Drawer* drawer = new Drawer(window, renderer);
	UIAsset* uiAsset = &UIAsset::GetInstance(drawer);
	BackgroundAsset* bgAsset = &BackgroundAsset::GetInstance(drawer);
	ShipAsset* shipAsset = &ShipAsset::GetInstance(drawer);
	MiscAsset* miscAsset = &MiscAsset::GetInstance(drawer);
	ProjectileAsset* projectileAsset = &ProjectileAsset::GetInstance(drawer);

	StateMachine* stateMachine = new StateMachine();
	stateMachine->Change(new StartState(stateMachine, drawer));

	float lastFrame = (float)SDL_GetTicks() * 0.001f;

	SDL_Event event;
	
	while (SDL_PollEvent(&event) >= 0)
	{
		stateMachine->AddPushedStates();

		float currentFrame = (float)SDL_GetTicks() * 0.001f;
		float elapsedTime = currentFrame - lastFrame;

		if (!stateMachine->HandleEvents(&event))
			break;
		if (!stateMachine->Update(elapsedTime))
			break;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		stateMachine->Draw();
		stateMachine->DeletePoppedStates();

		lastFrame = currentFrame;

		SDL_RenderPresent(renderer);
		SDL_Delay(1);
	}

	Mix_Quit();
    SDL_Quit();
	delete drawer;
	delete stateMachine;

    return EXIT_SUCCESS;
}
