#include "Constants.h"
#include "GameEngine.h"
#include "System.h"
#include "Bullet.h"
#include "Pistol.h"
#include "EnemyShip.h"
#include <SDL2/SDL_image.h>

using namespace GameEngine;

Pistol::Pistol() : Sprite(500, 570, 200, 200)
{
    pistolTexture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + "images/Player.png").c_str());
}

Pistol *Pistol::getInstance()
{
    return new Pistol();
}

Pistol::~Pistol()
{
    SDL_DestroyTexture(pistolTexture);
}

void Pistol::tick()
{
    followMouse();     // Make pistol follow cursor
    killOnCollision(); // Check for collisions with enemies
}

// Called on mouse click: fires a bullet and plays sound
void Pistol::mouseDown(int x, int y)
{
    Bullet *b = Bullet::getInstance(getRect().x + 90); // Spawn bullet near center of pistol
    ge.addSprite(b);
    sys.playSound("sounds/GunshotSound.wav");
}

void Pistol::draw() const
{
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.get_ren(), pistolTexture, NULL, &rect);
}

void Pistol::followMouse()
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    rect.x = mouseX - rect.w / 2;
}

bool Pistol::deleteAtRestart() const
{
    return false;
}

void Pistol::killOnCollision()
{
    std::vector<Sprite *> spritesToRemove;
    for (Sprite *c : ge.getComps())
    {
        if (dynamic_cast<EnemyShip *>(c) != nullptr)
        {
            if (checkCollision(c))
            {
                spritesToRemove.push_back(c);
                ge.addEnemyKilled();
            }
        }
    }

    for (Sprite *c : spritesToRemove)
    {
        ge.removeSprite(c);
    }
}
