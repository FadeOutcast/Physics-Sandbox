#include <iostream>
#include <MainLoop.h>

int main(){
    printf("HELOO?");


    MainLoop* Loop = new MainLoop();

    Loop->Init("Empty Window", 800, 700, SDL_WINDOW_RESIZABLE);
    
    while (Loop->IsRunning())
    {
        Loop->HandleEvents();
        Loop->Update();
        Loop->UpdateRendering();
        /* code */
    }
    


    return 0;
}