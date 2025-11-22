#include <Shape.h>
#include <MainLoop.h>

// Shape::Shape(){
//     Color = { static_cast<Uint8>(SDL_rand(255)), static_cast<Uint8>(SDL_rand(255)),static_cast<Uint8>(SDL_rand(255)), 255 };
//     Rect = {static_cast<float>(SDL_rand(800)), static_cast<float>(SDL_rand(700)), 100.f, 100.f};
//     ShapeType = Circle;
//     PreviousY = 0.f;
//     CirlceTex = nullptr;

// }
// Rectangle Spawn, deprecated
Shape::Shape(float X, float Y, float Width, float Height, SDL_Renderer* Renderer)
{
    SDL_Color Colors[4] = { {255, 99, 71, 255},    // Red
                            {135, 206, 250, 255},  // Blue
                            {255, 215, 0, 255},    // Yellow
                            {124, 252, 0, 255},    // Green
    };
    int RandInt = SDL_rand(4);
    RandInt = std::max(RandInt, 0);
    RandInt = std::min(RandInt, 4);
    Color = Colors[RandInt];
    Rect = {X-Width/2, Y-Height/2, Width, Height};
    ShapeType = EShapeType::Rectangle;
    PreviousY = 0.f;
    Velocity = std::make_pair(0.f, 0.f);
    CirlceTex = nullptr;
}

Shape::Shape(SDL_Renderer* Renderer, float X, float Y, float Radius, float SpawnVelocity)
{
    SDL_Color Colors[4] = { {255, 99, 71, 255},    // Red
                            {135, 206, 250, 255},  // Blue
                            {255, 215, 0, 255},    // Yellow
                            {124, 252, 0, 255},    // Green
    };
    int RandInt = SDL_rand(4);
    RandInt = std::max(RandInt, 0);
    RandInt = std::min(RandInt, 4);
    Color = Colors[RandInt];
    Rect = {X-Radius, Y-Radius, Radius*2, Radius*2};
    ShapeType = EShapeType::Circle;
    PreviousY = 0.f;
    float SpeedX = SDL_rand(SpawnVelocity);
    float SpeedY = SDL_rand(SpawnVelocity);//SDL_sqrtf(SpawnVelocity*SpawnVelocity - SpeedX*SpeedX);
    std::cout << SpawnVelocity << std::endl;
    Velocity = std::make_pair(SpeedX, SpeedY);

    // Randomly negate x or y velocities
    Velocity.first *= -1.f + 2.f * (SDL_rand(3) > 1.f);
    Velocity.second *= -1.f + 2.f* (SDL_rand(3) > 1.f);
    CirlceTex = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Radius*2, Radius*2);
}




Shape::~Shape(){

}

void Shape::PhysicsUpdate(float DeltaTime)
{
    WallCollision();
    ApplyGravity(DeltaTime);
    Rect.x += Velocity.first * DeltaTime;
    // Rect.y += Velocity.second * DeltaTime;
}

void Shape::ApplyGravity(float DeltaTime)
{
    // Verlet Integration, which doesn't work if we are doing elastic collision since we need the velocity
    // if( PreviousY ==  0.f ) PreviousY = Rect.y;
    // float NewY = Rect.y * 2 - PreviousY + MainLoop::GravityZ * DeltaTime * DeltaTime;
    // PreviousY = Rect.y;
    // Rect.y = NewY;

    Rect.y += Velocity.second * DeltaTime + 0.5 * MainLoop::GravityZ * DeltaTime * DeltaTime;
    Velocity.second = Velocity.second + MainLoop::GravityZ * DeltaTime;

}

void Shape::WallCollision()
{
    
    if( Rect.x + Rect.w >= MainLoop::WindowWidth) Velocity.first = -std::abs(Velocity.first);
    if( Rect.x <= 0) Velocity.first = std::abs(Velocity.first);
    if( Rect.y + Rect.h >= MainLoop::WindowHeight) Velocity.second = -std::abs(Velocity.second);
    if( Rect.y <= 0) Velocity.second = std::abs(Velocity.second);

}

void Shape::Render(SDL_Renderer* Renderer)
{
    SDL_SetRenderDrawColor( Renderer, Color.r, Color.g, Color.b, Color.a );

    if( ShapeType == EShapeType::Rectangle ){
        SDL_RenderFillRect(Renderer, &Rect);
    } else {

        SDL_FPoint Points[ static_cast<int>(Rect.w * Rect.w) ];
        int count = 0;

        for (int i = 0; i < Rect.w; i++) {
            for (int j = 0; j < Rect.h; j++) {
                float X = Rect.w/2 - i;
                float Y = Rect.w/2 - j;
                if ((X * X + Y * Y) <= (Rect.w/2 * Rect.w/2)) {
                    Points[count] = SDL_FPoint{Rect.x + i, Rect.y + j};
                    count++;
                }
            }
        }

        SDL_RenderPoints(Renderer, Points, count);        
    }
    
    
}
