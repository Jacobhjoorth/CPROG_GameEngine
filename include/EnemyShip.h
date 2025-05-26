#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "Sprite.h"

using namespace GameEngine;

class EnemyShip : public Sprite
{
public:
    ~EnemyShip();
    static EnemyShip *getInstance(int x, int y, int w, int h);
    void draw() const override;
    void tick() override;
    void moveY();
    std::string getType() const override;
    bool deleteAtRestart() const override;

private:
    EnemyShip(int x, int y, int w, int h);
    SDL_Texture *shipTexture;
};

#endif