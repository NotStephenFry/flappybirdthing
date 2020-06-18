#pragma once


#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "inc/Bird.h"
#include "inc/Pipe.h"
#include <list>

class Bird;

class Game
{
private:
	Game();
	~Game();

	SDL_Window* gWindow = NULL;
	SDL_Surface* gSurface = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* tex = NULL;
	SDL_Surface* downPipe = NULL;
	SDL_Surface* upPipe = NULL;

	SDL_Texture* downPipeTex = NULL;
	SDL_Texture* upPipeTex = NULL;
	SDL_Texture* bgTex = NULL;

	static Game* instance;
	bool running;

	Bird* bird = NULL;

	std::list<Pipe*> pipes;
	std::list<Bird*> birds;

	int frame = 0;
int birdX = 0;
	int birdY = 0;

	int pipeTimer = 0;

	Pipe* currentPipe;
	Pipe* nextPipe;
	

public:
	SDL_Window* GetWindow();
	SDL_Surface* GetSurface();
	static Game* Get();

	std::list<Pipe*> GetPipes();
	std::list<Bird*> GetBirds();

	bool Running();

	void ProcessEvents();
	void Update();
	void Draw();

	void Reset();

	Pipe* GetCurrentPipe();
	Pipe* GetNextPipe();

};
