#include "Constants.h"
#include "GameEngine.h"
#include "System.h"
#include "EnemyRabbit.h"
#include <SDL2/SDL_image.h>

using namespace GameEngine;

// Constructor: Initializes the rabbit's position, size, texture, and creation time
EnemyRabbit::EnemyRabbit(int x, int y, int w, int h) : Sprite(x, y, w, h)
{
    rabbitTexture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + "images/EnemyRabbit.png").c_str());
    setCreationTime(SDL_GetTicks()); // Store current time to track lifetime
}

// Static factory method to create a rabbit instance
EnemyRabbit *EnemyRabbit::getInstance(int x, int y, int w, int h)
{
    return new EnemyRabbit(x, y, w, h);
}

// Destructor: Release texture memory
EnemyRabbit::~EnemyRabbit()
{
    SDL_DestroyTexture(rabbitTexture);
}

// Renders the rabbit to the screen
void EnemyRabbit::draw() const
{
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.get_ren(), rabbitTexture, NULL, &rect);
}

// Called every game tick to handle logic
void EnemyRabbit::tick()
{
    autoDelete(); // Check if the rabbit should despawn
}

// Automatically removes the rabbit after 3 seconds and reduces player health
void EnemyRabbit::autoDelete()
{
    std::vector<Sprite *> spritesToRemove;

    // If rabbit has existed for 3 seconds
    if (SDL_GetTicks() - getCreationTime() >= 3000)
    {
        spritesToRemove.push_back(this);     // Mark self for removal
        ge.reducePlayerHealth();             // Penalize player health
    }

    for (Sprite *c : spritesToRemove)
    {
        ge.removeSprite(c);
    }
}

// Records the rabbit's creation time
void EnemyRabbit::setCreationTime(Uint32 time)
{
    creationTime = time;
}

// Retrieves how long the rabbit has existed
Uint32 EnemyRabbit::getCreationTime() const
{
    return creationTime;
}

// Returns a string representing the type
std::string EnemyRabbit::getType() const
{
    return "EnemyRabbit";
}

// Mark this object for deletion on game restart
bool EnemyRabbit::deleteAtRestart() const
{
    return true;
}
