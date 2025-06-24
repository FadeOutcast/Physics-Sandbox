#pragma once

#include <iostream>
#include <SDL3/SDL.h>

enum EShapeType{
    Circle = 0,
    Rectangle = 1
};

class Shape{
public:
    Shape(SDL_Renderer* Renderer, float X, float Y, float Width, float Height);
    Shape(SDL_Renderer* Renderer, float X, float Y, float Radius);
    ~Shape();
    SDL_Color Color;
    SDL_FRect Rect;
    EShapeType ShapeType;
    void PhysicsUpdate(float DeltaTime);
    void ApplyGravity(float DeltaTime);
    void CollisionDetection();
    void Render(SDL_Renderer* Renderer);

private:
    float PreviousY;
    SDL_Texture* CirlceTex;
};