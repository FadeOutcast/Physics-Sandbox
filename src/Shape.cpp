#include <Shape.h>
#include <MainLoop.h>

Shape::Shape(){
    Color = { static_cast<Uint8>(SDL_rand(255)), static_cast<Uint8>(SDL_rand(255)),static_cast<Uint8>(SDL_rand(255)), 255 };
    Rect = {static_cast<float>(SDL_rand(800)), static_cast<float>(SDL_rand(700)), 100.f, 100.f};
}

Shape::Shape(float X, float Y, float Width, float Height)
{
    Color = { static_cast<Uint8>(SDL_rand(255)), static_cast<Uint8>(SDL_rand(255)),static_cast<Uint8>(SDL_rand(255)), 255 };
    Rect = {X-Width/2, Y-Height/2, Width, Height};

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
    float PreviousY = Rect.y;

    float NewY = PreviousY * 2 - PreviousY * MainLoop::GravityZ * DeltaTime * DeltaTime;

    Rect.y = NewY;

}

void Shape::CollisionDetection()
{
}
