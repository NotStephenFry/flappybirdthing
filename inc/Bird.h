#pragma once

#include "Game.h"

class Bird
{
public:
    Bird(const char* textureSheet, SDL_Renderer* ren);
    ~Bird();
    int GetX();
    int GetY();
    float GetHSpeed();
    float GetVSpeed();
    void Jump();

    void Update();
    void Render();
    bool Alive();

    bool IsPlayerControlled();
    void SetPlayerController(bool val);

private:
    int x;
    int y;
    float hspeed;
    float vspeed;

    int timeAlive;
    bool alive;

    SDL_Texture* objTexture = NULL;
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer = NULL;

    bool isPlayerControlled;
};