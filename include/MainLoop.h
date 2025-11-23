#pragma once

#include <iostream>
#include <SDL3/SDL.h>
#include <vector>
#include "Shape.h"

// class Shape;
class ControlsUI;

class MainLoop{
public:
    MainLoop();
    ~MainLoop();

    static float GravityZ;
    static int RelativeTemperature;
    static int WindowWidth;
    static int WindowHeight;

    void Init(const char* WindowName, int Width, int Height, SDL_WindowFlags Flag);

    void HandleEvents();
    void Update();
    void UpdateRendering();
    void PhysicsUpdate(float DeltaTime);
    void CollisionsUpdate(float DeltaTime);
    void Clean();
    void Reset(int ShapeCount, int NewRelativeTemperature, bool Gravity);
    void PlotDist();

    bool IsRunning(){ return bIsRunning; }

private:
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    bool bIsRunning;

    Shape* Shapes[5000];
    int CurrentShapeCount;
    int MaxShapeCount = 1000;

    // Velocity at Temperature of 1
    ControlsUI* Control;
    


};