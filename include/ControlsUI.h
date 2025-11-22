#pragma once
#include <MainLoop.h>

class ControlsUI{

    void Init(SDL_Window* Window, SDL_Renderer* Renderer);
public:
    void Render();
    MainLoop* Loop;

private:
    float ShapeCount;
    bool Gravity;
};