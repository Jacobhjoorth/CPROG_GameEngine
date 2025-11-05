#include "Constants.h"
#include "GameEngine.h"
#include "System.h"
#include "EnemyRabbit.h"
#include <SDL2/SDL_image.h>

using namespace GameEngine;

EnemyRabbit::EnemyRabbit(int x, int y, int w, int h) : Sprite(x, y, w, h)
{
    rabbitTexture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + "images/EnemyRabbit.png").c_str());
    setCreationTime(SDL_GetTicks()); // Store current time to track lifetime
}

EnemyRabbit *EnemyRabbit::getInstance(int x, int y, int w, int h)
{
    return new EnemyRabbit(x, y, w, h);
}

EnemyRabbit::~EnemyRabbit()
{
    SDL_DestroyTexture(rabbitTexture);
}

void EnemyRabbit::draw() const
{
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.get_ren(), rabbitTexture, NULL, &rect);
}

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
        spritesToRemove.push_back(this);    
        ge.reducePlayerHealth();             
    }

    for (Sprite *c : spritesToRemove)
    {
        ge.removeSprite(c);
    }
}

void EnemyRabbit::setCreationTime(Uint32 time)
{
    creationTime = time;
}

Uint32 EnemyRabbit::getCreationTime() const
{
    return creationTime;
}

std::string EnemyRabbit::getType() const
{
    return "EnemyRabbit";
}

bool EnemyRabbit::deleteAtRestart() const
{
    return true;
}
