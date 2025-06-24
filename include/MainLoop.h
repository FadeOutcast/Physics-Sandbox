#include <iostream>
#include <SDL3/SDL.h>
#include "Shape.h"

// class Shape;

class MainLoop{
public:
    MainLoop();
    ~MainLoop();

    static float GravityZ;

    void Init(const char* WindowName, int Width, int Height, SDL_WindowFlags Flag);

    void HandleEvents();
    void Update();
    void UpdateRendering();
    void PhysicsUpdate(float DeltaTime);
    void Clean();

    bool IsRunning(){ return bIsRunning; }

private:
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    bool bIsRunning;

    Shape* Shapes[100];
    int ShapeCount;
    
    


};