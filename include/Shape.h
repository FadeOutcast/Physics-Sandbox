#include <iostream>
#include <SDL3/SDL.h>

class Shape{
public:
    Shape();
    ~Shape();
    SDL_Color Color;
    SDL_FRect Rect;
};