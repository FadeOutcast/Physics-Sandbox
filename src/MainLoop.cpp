#include <MainLoop.h>

float MainLoop::GravityZ = -0.1f;

MainLoop::MainLoop()
{
    ShapeCount = 0;
    // float MainLoop::GravityZ = -9.8f;
}

MainLoop::~MainLoop()
{
}

void MainLoop::Init(const char* WindowName, int Width, int Height, SDL_WindowFlags Flag)
{
    if (SDL_Init(SDL_INIT_VIDEO) == true )
    {
        printf("STARTING WINDOW");        
        Window = SDL_CreateWindow(WindowName, Width, Height, Flag);
        Renderer = SDL_CreateRenderer(Window, NULL);
        bIsRunning = true;
    }
    else{
        printf("FAILED TO START WINDOW");        
        bIsRunning = false;
    }
}

void MainLoop::HandleEvents()
{
    SDL_Event Event;
    SDL_PollEvent(&Event);
    switch (Event.type)
    {
    case SDL_EVENT_QUIT:
        bIsRunning = false;
        break;
        
    case SDL_EVENT_KEY_DOWN:
        if (Event.key.key == SDLK_T)
        {
            if (ShapeCount < 100) {
                Shape* NewShape = new Shape();
                Shapes[ShapeCount] = NewShape;
                ShapeCount++;
            }
        }
        break;

    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        if (Event.button.button == SDL_BUTTON_LEFT){
            if (ShapeCount < 100) {
                float X;
                float Y;
                SDL_GetMouseState(&X, &Y);
                Shape* NewShape = new Shape(X, Y, 50.f, 50.f);
                Shapes[ShapeCount] = NewShape;
                ShapeCount++;
            }
        }

    default:
        break;
    }
}

void MainLoop::Update()
{
}

void MainLoop::PhysicsUpdate(float DeltaTime)
{
    for (int i = 0; i < ShapeCount; i++)
    {
        Shapes[i]->PhysicsUpdate(DeltaTime);
    }
    
}

void MainLoop::UpdateRendering()
{
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderClear(Renderer);
    for (int i = 0; i < ShapeCount; i++)
    {
        SDL_SetRenderDrawColor( Renderer, Shapes[i]->Color.r, Shapes[i]->Color.g, Shapes[i]->Color.b, Shapes[i]->Color.a );
        SDL_RenderFillRect(Renderer, &Shapes[i]->Rect);
    }
    
    SDL_RenderPresent(Renderer);
}

void MainLoop::Clean()
{
    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
    SDL_Quit();
}