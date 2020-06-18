#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>

class Game
{
private:
	Game();
	~Game();

	SDL_Window* gWindow = NULL;
	SDL_Surface* gSurface = NULL;
	SDL_Surface* tex = NULL;

	static Game* instance;

public:
	SDL_Window* GetWindow();
	SDL_Surface* GetSurface();
	static Game* Get();

	void Draw();

	int birdX = 0;
	int birdY = 0;

};
