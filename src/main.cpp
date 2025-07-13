#include <iostream>
#include <MainLoop.h>
#include <matplotlib-cpp-master/matplotlibcpp.h>

namespace plt = matplotlibcpp;


int main(){


    const int FPS = 60;
    const int TargetDeltaTime = 1000/FPS;
    const int TargetPhysicsDeltaTime = 1000/50;

    int FrameTime;
    float PhysicsTime;
    Uint32 CurrentTime;

    // Used to track for frametime
    Uint32 PreviousTime = 0;
    // Used to track for physics deltatime
    Uint32 PreviousPhysicsTime = 0;
    

    MainLoop* Loop = new MainLoop();

    Loop->Init("Physics Sandbox", 1920, 1080, SDL_WINDOW_RESIZABLE);
    
    while (Loop->IsRunning())
    {
        CurrentTime = SDL_GetTicks();
        FrameTime = CurrentTime - PreviousTime;
        PhysicsTime = CurrentTime - PreviousPhysicsTime;

        if (FrameTime >= TargetDeltaTime)
        {
            Loop->HandleEvents();
            Loop->Update();
            Loop->UpdateRendering();
            PreviousTime = CurrentTime;
        }

        if ( PhysicsTime >= TargetPhysicsDeltaTime ){
            // Do Something
            std::cout << PhysicsTime << std::endl;
            Loop->PhysicsUpdate(PhysicsTime/1000);
            PreviousPhysicsTime = CurrentTime;
        }        
    }

    const int NumberOfBars = 20;


    std::vector<float> Velocities;
    Loop->Clean(Velocities);


    plt::hist(Velocities, NumberOfBars);
    plt::xlim(0.f, 2500.f);
    plt::show();

    return 0;
}