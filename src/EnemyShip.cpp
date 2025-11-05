#include "Constants.h"
#include "GameEngine.h"
#include "System.h"
#include "EnemyShip.h"
#include <SDL2/SDL_image.h>

using namespace GameEngine;

EnemyShip::EnemyShip(int x, int y, int w, int h) : Sprite(x, y, w, h)
{
    shipTexture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + "images/Enemy.png").c_str());
}

EnemyShip *EnemyShip::getInstance(int x, int y, int w, int h)
{
    return new EnemyShip(x, y, w, h);
}

EnemyShip::~EnemyShip()
{
    SDL_DestroyTexture(shipTexture);
}

void EnemyShip::draw() const
{
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.get_ren(), shipTexture, NULL, &rect);
}

void EnemyShip::tick()
{
    moveY(); 

    // If ship moves past bottom of screen, reduce player health and remove ship
    if (getRect().y >= sys.SCREEN_HEIGHT)
    {
        ge.reducePlayerHealth();
        ge.removeSprite(this);
    }
}

// Moves the enemy ship downward by a fixed amount
void EnemyShip::moveY()
{
    rect.y += 2;
}

std::string EnemyShip::getType() const
{
    return "EnemyShip";
}

bool EnemyShip::deleteAtRestart() const
{
    return true;
}
