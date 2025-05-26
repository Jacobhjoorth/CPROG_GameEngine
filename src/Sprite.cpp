#include "Sprite.h"

namespace GameEngine
{
    // Constructor: stores sprite position and dimensions
    Sprite::Sprite(int x, int y, int width, int height) : rect({x, y, width, height}) {}

    Sprite::~Sprite() {}

    // Placeholder for input handling, to be overridden
    void Sprite::mouseDown(int x, int y) {}

    // Placeholder for rendering, to be overridden
    void Sprite::draw() const {}

    // Placeholder for per-frame logic
    void tick() {}

    // Returns the rectangle representing the sprite's bounds
    SDL_Rect Sprite::getRect() const
    {
        return rect;
    }

    // Returns identifier string for type-checking
    std::string Sprite::getType() const
    {
        return "Sprite";
    }

    // Whether the sprite should be removed on game restart
    bool Sprite::deleteAtRestart() const
    {
        return false;
    }

    // AABB collision check with another sprite
    bool Sprite::checkCollision(Sprite *other)
    {
        const SDL_Rect &rect1 = getRect();
        const SDL_Rect &rect2 = other->getRect();
        return SDL_HasIntersection(&rect1, &rect2) == SDL_TRUE;
    }
}
