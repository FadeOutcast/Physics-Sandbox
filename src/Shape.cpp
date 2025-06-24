#include <Shape.h>
#include <MainLoop.h>

// Shape::Shape(){
//     Color = { static_cast<Uint8>(SDL_rand(255)), static_cast<Uint8>(SDL_rand(255)),static_cast<Uint8>(SDL_rand(255)), 255 };
//     Rect = {static_cast<float>(SDL_rand(800)), static_cast<float>(SDL_rand(700)), 100.f, 100.f};
//     ShapeType = Circle;
//     PreviousY = 0.f;
//     CirlceTex = nullptr;

// }

Shape::Shape(SDL_Renderer* Renderer, float X, float Y, float Width, float Height)
{
    Color = { static_cast<Uint8>(SDL_rand(255)), static_cast<Uint8>(SDL_rand(255)),static_cast<Uint8>(SDL_rand(255)), 255 };
    Rect = {X-Width/2, Y-Height/2, Width, Height};
    ShapeType = EShapeType::Rectangle;
    PreviousY = 0.f;
    CirlceTex = nullptr;
}

Shape::Shape(SDL_Renderer* Renderer, float X, float Y, float Radius)
{
    Color = { static_cast<Uint8>(SDL_rand(255)), static_cast<Uint8>(SDL_rand(255)),static_cast<Uint8>(SDL_rand(255)), 255 };
    Rect = {X-Radius, Y-Radius, Radius*2, Radius*2};
    ShapeType = EShapeType::Circle;
    PreviousY = 0.f;
    CirlceTex = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Radius*2, Radius*2);
}




Shape::~Shape(){

}

void Shape::PhysicsUpdate(float DeltaTime)
{
    ApplyGravity(DeltaTime);
    CollisionDetection();
}

void Shape::ApplyGravity(float DeltaTime)
{
    if( PreviousY ==  0.f ) PreviousY = Rect.y;

    float NewY = Rect.y * 2 - PreviousY + MainLoop::GravityZ * DeltaTime * DeltaTime;

    PreviousY = Rect.y;
    Rect.y = NewY;

}

void Shape::CollisionDetection()
{
}

void Shape::Render(SDL_Renderer* Renderer)
{
    SDL_SetRenderDrawColor( Renderer, Color.r, Color.g, Color.b, Color.a );

    if( ShapeType == EShapeType::Rectangle ){
        SDL_RenderFillRect(Renderer, &Rect);
    } else {

        for (int i = 0; i < Rect.w; i++) {
            for (int j = 0; j < Rect.h; j++) {
                float X = Rect.w/2 - i;
                float Y = Rect.w/2 - j;
                if ((X * X + Y * Y) <= (Rect.w/2 * Rect.w/2)) {
                    SDL_RenderPoint(Renderer, static_cast<int>(Rect.x + i), static_cast<int>(Rect.y + j));
                }
            }
        }
        
    }
    
    
}
