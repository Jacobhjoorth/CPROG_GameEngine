#include "Constants.h"
#include "GameEngine.h"
#include "System.h"
#include "EnemyShip.h"
#include <SDL2/SDL_image.h>

using namespace GameEngine;

// Constructor: Set position, dimensions, and load texture for the enemy ship
EnemyShip::EnemyShip(int x, int y, int w, int h) : Sprite(x, y, w, h)
{
    shipTexture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + "images/Enemy.png").c_str());
}

// Static factory method to create an EnemyShip
EnemyShip *EnemyShip::getInstance(int x, int y, int w, int h)
{
    return new EnemyShip(x, y, w, h);
}

// Destructor: Clean up texture memory
EnemyShip::~EnemyShip()
{
    SDL_DestroyTexture(shipTexture);
}

// Renders the enemy ship on screen
void EnemyShip::draw() const
{
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.get_ren(), shipTexture, NULL, &rect);
}

// Called every frame: moves ship and checks if it escapes the screen
void EnemyShip::tick()
{
    moveY(); // Move downward

    // If ship moves past bottom of screen, penalize player and remove ship
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

// Returns string for identifying the type
std::string EnemyShip::getType() const
{
    return "EnemyShip";
}

// Marks object for deletion during a game restart
bool EnemyShip::deleteAtRestart() const
{
    return true;
}
