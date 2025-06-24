#pragma once

#include <iostream>
#include <SDL3/SDL.h>

class Shape{
public:
    Shape();
    Shape(float X, float Y, float Width, float Height);
    ~Shape();
    SDL_Color Color;
    SDL_FRect Rect;
    void PhysicsUpdate(float DeltaTime);
    void ApplyGravity(float DeltaTime);
    void CollisionDetection();

private:
    float PreviousY;
};