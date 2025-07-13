#include <MainLoop.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl3.h>
#include <imgui/imgui_impl_sdlrenderer3.h>
#include <ControlsUI.h>
#include <cmath>


float MainLoop::GravityZ = 9.8f;
int MainLoop::WindowHeight = 0.f;
int MainLoop::WindowWidth = 0.f;


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
    if (SDL_Init(SDL_INIT_VIDEO) == 1 )
    {
        printf("STARTING WINDOW");        
        Window = SDL_CreateWindow(WindowName, Width, Height, Flag);
        if( !Window ){
            SDL_Quit();
            return;
        }
        Renderer = SDL_CreateRenderer(Window, NULL);
        if( !Renderer ){
            SDL_Quit();
            return;
        }

        bIsRunning = true;
        MainLoop::WindowHeight = Height;
        MainLoop::WindowWidth = Width;

        // init IMGUI
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &IO = ImGui::GetIO(); (void)IO;

        ImGui_ImplSDL3_InitForSDLRenderer(Window, Renderer);
        ImGui_ImplSDLRenderer3_Init(Renderer);

        Control = new ControlsUI();

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
        if (Event.key.key == SDLK_R)
        {
            if (ShapeCount < 1000) {
                Shape* NewShape = new Shape(Renderer, SDL_rand(MainLoop::WindowWidth), SDL_rand(MainLoop::WindowHeight), 5.f);
                Shapes[ShapeCount] = NewShape;
                ShapeCount++;
            }
        }
        break;

    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        if (Event.button.button == SDL_BUTTON_LEFT){
            if (ShapeCount < 1000) {
                float X;
                float Y;
                SDL_GetMouseState(&X, &Y);
                Shape* NewShape = new Shape(Renderer, X, Y, 5.f);
                Shapes[ShapeCount] = NewShape;
                ShapeCount++;
            }
        }
        break;

    default:
        break;
    }
    ImGui_ImplSDL3_ProcessEvent(&Event);
}

void MainLoop::Update()
{
    int SpawnRate = 3;
    
    for(int i = 0; i < SpawnRate; i++){
        
        if (ShapeCount < 1000) {
            Shape* NewShape = new Shape(Renderer, SDL_rand(MainLoop::WindowWidth), SDL_rand(MainLoop::WindowHeight), 5.f);
            Shapes[ShapeCount] = NewShape;
            ShapeCount++;
        }

    }
        
}

void MainLoop::PhysicsUpdate(float DeltaTime)
{
    CollisionsUpdate(DeltaTime);

    for (int i = 0; i < ShapeCount; i++)
    {
        Shapes[i]->PhysicsUpdate(DeltaTime);
    }


}

void MainLoop::CollisionsUpdate(float DeltaTime)
{
    for( int i = 0; i < ShapeCount; i++){

        for( int j = i+1; j < ShapeCount; j++ ){
            if( i == j || !Shapes[i] || !Shapes[j]) continue;
            
            if (Shapes[i]->ShapeType == EShapeType::Circle && Shapes[j]->ShapeType == EShapeType::Circle)
            {

                // Circle centres position
                float Shape1X = Shapes[i]->Rect.x + Shapes[i]->Rect.w/2;
                float Shape2X = Shapes[j]->Rect.x + Shapes[j]->Rect.w/2;
                float Shape1Y = Shapes[i]->Rect.y + Shapes[i]->Rect.w/2;
                float Shape2Y = Shapes[j]->Rect.y + Shapes[j]->Rect.w/2;

                float DistanceSquared = (Shape2X-Shape1X)*(Shape2X-Shape1X) + (Shape2Y-Shape1Y)*(Shape2Y-Shape1Y);

                bool Colliding = DistanceSquared <= (Shapes[i]->Rect.w/2+Shapes[j]->Rect.w/2)*(Shapes[i]->Rect.w/2+Shapes[j]->Rect.w/2);
                
                if (Colliding)
                {
                    
                    float Distance = SDL_sqrtf( DistanceSquared );
                    
                    float NormalX = 0.f;
                    float NormalY = 0.f;

                    if (Distance != 0.f) {
                        // Normalized Vectors
                        NormalX = ( Shape2X - Shape1X) / Distance;
                        NormalY = ( Shape2Y - Shape1Y) / Distance;
                    }
                    else{
                        NormalX = 0.1f;
                        NormalY = 0.1f;
                    }

                    // Push both out to ensure not colliding
                    float RadiusSum = Shapes[i]->Rect.w/2 + Shapes[j]->Rect.w/2;
                    Shapes[i]->Rect.x -= NormalX * ( (RadiusSum - Distance) / 2.0f);
                    Shapes[i]->Rect.y -= NormalY * ( (RadiusSum - Distance) / 2.0f);
                    Shapes[j]->Rect.x += NormalX * ( (RadiusSum - Distance) / 2.0f);
                    Shapes[j]->Rect.y += NormalY * ( (RadiusSum - Distance) / 2.0f);



                    float XVelocityDiff = Shapes[i]->Velocity.first - Shapes[j]->Velocity.first;
                    float YVelocityDiff = Shapes[i]->Velocity.second - Shapes[j]->Velocity.second;
                    // Dot product of velocity difference and collision normal
                    float Dot = (XVelocityDiff * NormalX + YVelocityDiff * NormalY);

                    // Elastic collision
                    Shapes[i]->Velocity.first -= Dot * NormalX;
                    Shapes[j]->Velocity.first += Dot * NormalX;
                    Shapes[i]->Velocity.second -= Dot * NormalY;
                    Shapes[j]->Velocity.second += Dot * NormalY;

                }                

            }
            

        }

    }

}

void MainLoop::UpdateRendering()
{
    Control->Render();
    ImGui::End();
    ImGui::Render();
    SDL_SetRenderDrawColor(Renderer, 5, 5, 5, 255);
    SDL_RenderClear(Renderer);
    for (int i = 0; i < ShapeCount; i++)
    {
        Shapes[i]->Render(Renderer);
    }
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), Renderer);
    SDL_RenderPresent(Renderer);
}

void MainLoop::Clean(std::vector<float> &Velocities)
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
    SDL_Quit();
    Velocities.reserve(ShapeCount);

    for( int i = 0; i < ShapeCount; i++){
        float Velocity = sqrt( (Shapes[i]->Velocity.first * Shapes[i]->Velocity.first) + (Shapes[i]->Velocity.second * Shapes[i]->Velocity.second));
        Velocities.push_back(Velocity);
    }
}

