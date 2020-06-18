#pragma once
#include "Game.h"
#include "inc/TextureManager.h"

class Actor
{
    public:
    Actor(const char* textureSheet, SDL_Renderer* ren);
    ~Actor();

    void Update();
    void Render();

    private:
    int x;
    int y;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;

};
