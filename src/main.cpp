#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>
#include "inc/Game.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main()
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	Game* game = Game::Get();

	while (game->Running())
	{
		frameStart = SDL_GetTicks();

		game->ProcessEvents();
		game->Update();
		game->Draw();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}

		std::cout << "FPS: " << (float)(1000.0f / (float)std::max((float)frameTime, (float) 1000/60)) << "\n";
	}
	return 0;
}
