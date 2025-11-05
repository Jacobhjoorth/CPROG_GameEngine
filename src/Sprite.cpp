#include "Sprite.h"

namespace GameEngine
{
    Sprite::Sprite(int x, int y, int width, int height) : rect({x, y, width, height}) {}

    Sprite::~Sprite() {}

    // Placeholder for input handling, to be overridden
    void Sprite::mouseDown(int x, int y) {}

    // Placeholder for rendering, to be overridden
    void Sprite::draw() const {}

    // Placeholder for per-frame logic
    void tick() {}

    SDL_Rect Sprite::getRect() const
    {
        return rect;
    }

    std::string Sprite::getType() const
    {
        return "Sprite";
    }

    bool Sprite::deleteAtRestart() const
    {
        return false;
    }

    bool Sprite::checkCollision(Sprite *other)
    {
        const SDL_Rect &rect1 = getRect();
        const SDL_Rect &rect2 = other->getRect();
        return SDL_HasIntersection(&rect1, &rect2) == SDL_TRUE;
    }
}
