#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include "Sprite.h"

using namespace GameEngine;

class EnemySpawner : public Sprite
{

public:
    ~EnemySpawner();
    static EnemySpawner *getInstance();
    void randomSpawnRabbit();
    void randomSpawnShip();
    void tick() override;
    void draw() const override;
    bool deleteAtRestart() const override;

protected:
private:
    EnemySpawner();
    int lastSpawnTime;
    int spawnInterval = 2000;
};

#endif