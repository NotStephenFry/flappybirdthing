#include "inc/Game.h"
#include "inc/TextureManager.h"
#include <string>

int SCREEN_WIDTH=640;
int SCREEN_HEIGHT=480;

Game* Game::instance = NULL;

Game::Game()
{
	running = true;

	gWindow = NULL;
	gSurface = NULL;

	bool quit = false;

	SDL_Event e;

	tex = IMG_Load("assets/flappyBird.png");
	downPipe = IMG_Load("assets/downPipe.png");
	upPipe = IMG_Load("assets/upPipe.png");

	

	if (!tex)
	{
		std::cout << "Could not load flappy bird";
	}

	if (SDL_Init( SDL_INIT_VIDEO ) < 0)
	{
		std::cout << "SDL Could not initialise! SDL_Error:";
		std::cout << SDL_GetError();
		std::cout << "\n";
	}
	else
	{
		gWindow = SDL_CreateWindow("Need to figure this shit out", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (!gWindow)
		{
			std::cout << "Window not initialise! SDL_Error:";
        	        std::cout << SDL_GetError();
	                std::cout << "\n";
		}
		else
		{
			renderer = SDL_CreateRenderer(gWindow, -1, 0);
			if (!renderer)
			{
				std::cout << "Renderer not initialise! SDL_Error:";
						std::cout << SDL_GetError();
						std::cout << "\n";
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			}
			

			gSurface = SDL_GetWindowSurface( gWindow );

			SDL_FillRect( gSurface, NULL, SDL_MapRGB( gSurface->format, 0xFF, 0xFF, 0xFF) );

			SDL_BlitSurface( tex, NULL, gSurface, NULL);

			SDL_UpdateWindowSurface( gWindow );
		}
	}

	downPipeTex = TextureManager::LoadTexture("assets/downPipe.png", renderer);
	upPipeTex = TextureManager::LoadTexture("assets/upPipe.png", renderer);
	bgTex = TextureManager::LoadTexture("assets/bg.png", renderer);
	
}

void Game::Reset()
{
	std::list<Bird*>::iterator it = birds.begin();
	while (it != birds.end())
	{
		//delete (*it);
		++it;
	}
	birds.clear();

	std::list<Pipe*>::iterator it2 = pipes.begin();
	while (it2 != pipes.end())
	{
		//delete (*it2);
		++it2;
	}
	pipes.clear();

	bird = new Bird("assets/flappyBird.png", renderer);
	bird->SetPlayerController(true);
	birds.push_back(bird);

	int birdCount = atoi(getenv("NumOfBirds"));

	for (int i = 0; i < birdCount; i++)
	{
		Bird* newBird = new Bird("assets/flappyBird.png", renderer);
		//bird->SetPlayerController(true);
		birds.push_back(newBird);
	}

	pipeTimer = 0;
}

Game::~Game()
{
	SDL_DestroyWindow( gWindow );
	SDL_Quit();
}

Game* Game::Get()
{
	if (!instance)
	{
		instance = new Game();
	}

	return instance;
}

void Game::ProcessEvents()
{
	std::cout << "Process events\n";
	SDL_Event e;
	while (SDL_PollEvent( &e ) != 0)
	{
		if ( e.type == SDL_QUIT )
		{
			running = false;
		}
		else if ( e.type == SDL_KEYDOWN )
		{
			if (e.key.keysym.sym == SDLK_UP)
			{
				if (birds.size())
				{
					std::list<Bird*>::iterator it = birds.begin();
					while (it != birds.end())
					{
						(*it)->Jump();
						++it;
					}
				}
			}
			else if (e.key.keysym.sym = SDLK_ESCAPE)
			{
				running = false;
			}
		}
	}
}

void Game::Draw()
{
	std::cout << "Draw\n";

	SDL_RenderClear(renderer);

	int rx = frame % 144;
	int dx = -rx;

	while (dx < SCREEN_WIDTH)
	{
		SDL_Rect rec;
		rec.x = dx;
		rec.y = 0;
		rec.w = 144;
		rec.h = SCREEN_HEIGHT;
		SDL_RenderCopy(renderer, bgTex, NULL, &rec);

		dx += 144;
	}
	
	for (std::list<Pipe*>::iterator it = pipes.begin(); it != pipes.end(); it++)
	{
		Pipe* pipe = (*it);
		SDL_Rect rec2;
		rec2.x = pipe->GetX();
		rec2.y = pipe->GetY() - 640;
		rec2.w = 16;
		rec2.h = 640;
		SDL_RenderCopy(renderer, downPipeTex, NULL, &rec2);

		SDL_Rect rec3;
		rec3.x = pipe->GetX();
		rec3.y = pipe->GetY() + 80;
		rec3.w = 16;
		rec3.h = 640;
		SDL_RenderCopy(renderer, upPipeTex, NULL, &rec3);
	}

	std::list<Bird*>::iterator it = birds.begin();
	while (it != birds.end())
	{
		(*it)->Render();
		++it;
	}

	SDL_RenderPresent(renderer);
	//SDL_UpdateWindowSurface( gWindow );
}

SDL_Window* Game::GetWindow()
{
	return gWindow;
}

SDL_Surface* Game::GetSurface()
{
	return gSurface;
}

bool Game::Running()
{
	return running;
}

std::list<Pipe*> Game::GetPipes()
{
	return pipes;
}

void Game::Update()
{
	frame++;

	bool reset = false;

	bool anyBirdIsAlive = false;

	// no birds
	if (!birds.size())
	{
		reset = true;
	}

	std::list<Bird*>::iterator it3 = birds.begin();
	while (it3 != birds.end())
	{
		if ((*it3)->Alive())
		{
			anyBirdIsAlive = true;
		}
		++it3;
	}
	if (!anyBirdIsAlive)
	{
		reset = true;
	}

	if (reset)
	{
		Reset();
	}

	currentPipe = NULL;
	nextPipe = NULL;

	std::list<Pipe*>::iterator it = pipes.begin();
	while (it != pipes.end())
	{
		Pipe* pipe = (*it);
		if (pipe->GetX() > 48)
		{
			if (!currentPipe)
				currentPipe = pipe;

			if (!nextPipe && pipe != currentPipe)
				nextPipe = pipe;
		}
		++it;
	}


	std::cout << "Update\n";
	std::list<Bird*>::iterator it2 = birds.begin();
	while (it2 != birds.end())
	{
		(*it2)->Update();
		++it2;
	}

	if (pipeTimer == 0)
	{
		pipeTimer = 90;
		Pipe* pipe = new Pipe();
		pipes.push_back(pipe);
	}
	else
	{
		pipeTimer--;
	}
	

	std::list<Pipe*> pipesToRemove;
	it = pipes.begin();
	
	while (it != pipes.end())
	{
		Pipe* pipe = (*it);
		pipe->Update();

		std::cout << pipe->GetX();
		std::cout << "\n";

		if (pipe->GetX() < -16)
		{
			delete (*it);
			pipes.erase(it++);
		}

		++it;
	}

	std::cout << "\n";
		std::cout << "\n";
}

Pipe* Game::GetCurrentPipe()
{
	return currentPipe;
}

Pipe* Game::GetNextPipe()
{
	return nextPipe;
}