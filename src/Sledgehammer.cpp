#include "Constants.h"
#include "GameEngine.h"
#include "System.h"
#include "EnemyRabbit.h"
#include "Sledgehammer.h"
#include <SDL2/SDL_image.h>

using namespace GameEngine;

// Constructor: Initializes sledgehammer and loads texture
Sledgehammer::Sledgehammer() : Sprite(200, 200, 20, 20)
{
    sledgehammerTexture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + "images/Sledgehammer.png").c_str());
}

// Factory method to create sledgehammer
Sledgehammer *Sledgehammer::getInstance()
{
    return new Sledgehammer();
}

// Destructor: Clean up texture
Sledgehammer::~Sledgehammer()
{
    SDL_DestroyTexture(sledgehammerTexture);
}

// Called every frame: follows mouse position
void Sledgehammer::tick()
{
    followMouse();
}

// Called on mouse click: hits rabbits in range
void Sledgehammer::mouseDown(int x, int y)
{
    std::vector<Sprite *> spritesToRemove;
    for (Sprite *c : ge.getComps())
    {
        if (dynamic_cast<EnemyRabbit *>(c) != nullptr)
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

// Render sledgehammer on screen
void Sledgehammer::draw() const
{
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.get_ren(), sledgehammerTexture, NULL, &rect);
}

// Updates hammer position to cursor
void Sledgehammer::followMouse()
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    rect.x = mouseX;
    rect.y = mouseY;
}

// Sledgehammer persists between restarts
bool Sledgehammer::deleteAtRestart() const
{
    return false;
}
