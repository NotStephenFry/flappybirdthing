#include "inc/Bird.h"
#include "inc/TextureManager.h"
#include "inc/Pipe.h"

Bird::Bird(const char* textureSheet, SDL_Renderer *ren)
{
    x = 64;
    y = 240;
    vspeed = 0.0f;
    hspeed = 0.0f;

    timeAlive = 0;
    alive = true;

    renderer = ren;
    objTexture = TextureManager::LoadTexture(textureSheet, ren);

    isPlayerControlled = false;
}

Bird::~Bird()
{
    if (objTexture)
        SDL_DestroyTexture(objTexture);
}

int Bird::GetX()
{
    return x;
}

int Bird::GetY()
{
    return y;
}

float Bird::GetHSpeed()
{
    return hspeed;
}

float Bird::GetVSpeed()
{
    return vspeed;
}

void Bird::Update()
{
    Pipe* currentPipe = NULL;
    Pipe* nextPipe = NULL;

    int chance = floor( ((double)rand() / RAND_MAX) * 100);
    if ((chance < 2) && (!isPlayerControlled))
    {
        vspeed = -6;
    }

    if (alive)
    {
        timeAlive++;
        vspeed += 0.2;

        x += hspeed;
        y += vspeed;

        currentPipe = Game::Get()->GetCurrentPipe();
        nextPipe = Game::Get()->GetNextPipe();

        

        std::list<Pipe*> pipes = Game::Get()->GetPipes();
        std::list<Pipe*>::iterator it = pipes.begin();
        while (it != pipes.end())
        {
            Pipe* pipe = (*it);

            SDL_Rect birdRect;
            SDL_Rect topPipeRect;
            SDL_Rect bottomPipeRect;

            birdRect.x = x;
            birdRect.y = y;
            birdRect.w = 16;
            birdRect.h = 16;

            topPipeRect.x = pipe->GetX();
            topPipeRect.y = pipe->GetY() - 640;
            topPipeRect.w = 16;
            topPipeRect.h = 640;

            bottomPipeRect.x = pipe->GetX();
            bottomPipeRect.y = pipe->GetY() + 80;
            bottomPipeRect.w = 16;
            bottomPipeRect.h = 640;

            SDL_Rect res;

            if (SDL_IntersectRect(&birdRect, &topPipeRect, &res))
            {
                x = -60;
                alive = false;
            }

            if (SDL_IntersectRect(&birdRect, &bottomPipeRect, &res))
            {
                x = -60;
                alive = false;
            }

            if (y < 0)
            {
                x = -60;
                alive = false;
            }

            if (y > 480)
            {
                x = -60;
                alive = false;
            }

            ++it;
        }
    }



    //handle collision here
    if (isPlayerControlled)
    {
        std::cout << "== BIRD INFO ==\n";
        std::cout << "HEIGHT: " << y << "\n";
        std::cout << "VSPEED: " << vspeed << "\n";
        std::cout << "FITNESS: " << timeAlive << "\n";
        if (currentPipe)
        {
            std::cout << "CURRENT PIPE X: " << currentPipe->GetX() << "\n";
            std::cout << "CURRENT PIPE TOP LIMIT: " << currentPipe->GetY() << "\n";
            std::cout << "CURRENT PIPE BOTTOM LIMIT: " << (currentPipe->GetY() + 80) << "\n";
        }
        if (nextPipe)
        {
            std::cout << "NEXT PIPE X: " << nextPipe->GetX() << "\n";
            std::cout << "NEXT PIPE TOP LIMIT: " << nextPipe->GetY() << "\n";
            std::cout << "NEXT PIPE BOTTOM LIMIT: " << (nextPipe->GetY() + 80) << "\n";
        }
    }
    
}

void Bird::Jump()
{
    if (isPlayerControlled)
        vspeed = -6;
}

void Bird::Render()
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = 16;
    rect.h = 16;
    if (!isPlayerControlled)
        SDL_SetTextureAlphaMod(objTexture, 100);
    SDL_RenderCopy(renderer, objTexture, NULL, &rect);
}

bool Bird::Alive()
{
    return alive;
}

bool Bird::IsPlayerControlled()
{
    return isPlayerControlled;
}

void Bird::SetPlayerController(bool val)
{
    isPlayerControlled = val;
}