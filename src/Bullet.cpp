#include "Constants.h"
#include "GameEngine.h"
#include "System.h"
#include "Bullet.h"
#include "EnemyShip.h"
#include <SDL2/SDL_image.h>

using namespace GameEngine;

Bullet *Bullet::getInstance(int x)
{
    return new Bullet(x);
}

Bullet::Bullet(int x) : Sprite(x, 550, 20, 20)
{
    texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + "images/Bullet.png").c_str());
}

Bullet::~Bullet()
{
    SDL_DestroyTexture(texture);
}

void Bullet::draw() const
{
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.get_ren(), texture, NULL, &rect);
}

void Bullet::tick()
{
    killOnCollision();

    counter++;
    if (getRect().y <= 0) // If bullet goes off-screen (top)
    {
        ge.removeSprite(this);
    }
    else if (counter % 1 == 0)
    {
        rect.y -= 6; // Move bullet upward
    }
}

void Bullet::killOnCollision()
{
    std::vector<Sprite *> spritesToRemove;

    for (Sprite *c : ge.getComps()) // Loop through all game sprites
    {
        // Check if sprite is an EnemyShip and collides with bullet
        if (dynamic_cast<EnemyShip *>(c) != nullptr && checkCollision(c))
        {
            spritesToRemove.push_back(c);    // Mark enemy for deletion
            spritesToRemove.push_back(this); // Mark bullet for deletion
            ge.addEnemyKilled();         
        }
    }

    // Remove marked sprites from game engine
    for (Sprite *c : spritesToRemove)
    {
        ge.removeSprite(c);
    }
}

bool Bullet::deleteAtRestart() const
{
    return true;
}
