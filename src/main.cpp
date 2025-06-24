#include <iostream>
#include <MainLoop.h>

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

    Loop->Init("Physics Sandbox", 800, 700, SDL_WINDOW_RESIZABLE);
    
    // SDL_Delay(1000);

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
            Loop->PhysicsUpdate(PhysicsTime/1000);
            PreviousPhysicsTime = CurrentTime;
        }        
    }

    Loop->Clean();
    


    return 0;
}