#include "inc/Pipe.h"
#include <random>

Pipe::Pipe()
{
    x = 640;
    y = 80 + (floor( ((double)rand() / RAND_MAX) * 240));
}

Pipe::~Pipe()
{

}

int Pipe::GetX()
{
    return x;
}

int Pipe::GetY()
{
    return y;
}

void Pipe::Update()
{
    x -= 3;

    //handle collision here
}