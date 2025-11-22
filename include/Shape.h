#pragma once

#include <iostream>
#include <SDL3/SDL.h>

enum EShapeType{
    Circle = 0,
    Rectangle = 1
};

class Shape{
public:
    [[deprecated]]
    Shape(float X, float Y, float Width, float Height, SDL_Renderer* Renderer);
    
    Shape(SDL_Renderer* Renderer, float X, float Y, float Radius, float SpawnVelocity);
    ~Shape();
    void PhysicsUpdate(float DeltaTime);
    void ApplyGravity(float DeltaTime);
    void WallCollision();
    void Render(SDL_Renderer* Renderer);

    SDL_Color Color;
    SDL_FRect Rect;
    EShapeType ShapeType;
    std::pair<float, float> Velocity;

private:
    float PreviousY;
    SDL_Texture* CirlceTex;
};