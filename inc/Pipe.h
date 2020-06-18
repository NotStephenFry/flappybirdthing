#pragma once

class Pipe
{
public:
    Pipe();
    ~Pipe();
    int GetX();
    int GetY();

    void Update();

private:
    int x;
    int y;
};