#include "inc/Actor.h"
#include "inc/TextureManager.h"

Actor::Actor(const char* textureSheet, SDL_Renderer* ren)
{
    renderer = ren;
    objTexture = TextureManager::LoadTexture(textureSheet, ren);
}