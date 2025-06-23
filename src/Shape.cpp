#include <Shape.h>

Shape::Shape(){
    Color = { static_cast<Uint8>(SDL_rand(255)), static_cast<Uint8>(SDL_rand(255)),static_cast<Uint8>(SDL_rand(255)), 255 };
    Rect = {static_cast<float>(SDL_rand(800)), static_cast<float>(SDL_rand(700)), 100.f, 100.f};
}

Shape::~Shape(){

}

