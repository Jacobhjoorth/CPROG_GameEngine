#include "Constants.h"
#include "GameEngine.h"
#include "System.h"
#include "Bullet.h"
#include "Pistol.h"
#include "EnemyShip.h"
#include <SDL2/SDL_image.h>

using namespace GameEngine;

// Constructor: Initializes position and loads pistol texture
Pistol::Pistol() : Sprite(500, 570, 200, 200)
{
    pistolTexture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + "images/Player.png").c_str());
}

// Factory method to create a new pistol instance
Pistol *Pistol::getInstance()
{
    return new Pistol();
}

// Destructor: free the texture memory
Pistol::~Pistol()
{
    SDL_DestroyTexture(pistolTexture);
}

// Called every frame
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

// Renders the pistol to the screen
void Pistol::draw() const
{
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.get_ren(), pistolTexture, NULL, &rect);
}

// Updates pistol position based on mouse
void Pistol::followMouse()
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    rect.x = mouseX - rect.w / 2;
}

// Indicates pistol should persist after restart
bool Pistol::deleteAtRestart() const
{
    return false;
}

// Checks if pistol overlaps an enemy and removes it
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
