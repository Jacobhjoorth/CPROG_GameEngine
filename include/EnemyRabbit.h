#ifndef ENEMYRABBIT_H
#define ENEMYRABBIT_H

#include "Sprite.h"

using namespace GameEngine;

class EnemyRabbit : public Sprite
{
public:
    ~EnemyRabbit();
    static EnemyRabbit *getInstance(int x, int y, int w, int h);

    void draw() const override;
    void tick() override;
    void autoDelete();
    void randomSpawn();
    void setCreationTime(Uint32 time);
    Uint32 getCreationTime() const;
    std::string getType() const override;
    bool deleteAtRestart() const override;

private:
    EnemyRabbit(int x, int y, int w, int h);
    SDL_Texture *rabbitTexture;
    Uint32 creationTime;
};

#endif