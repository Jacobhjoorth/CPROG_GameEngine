#include "EnemySpawner.h"
#include "GameEngine.h"
#include "System.h"
#include "EnemyRabbit.h"
#include "EnemyShip.h"

using namespace GameEngine;

// Spawns rabbits at random positions on the screen with decreasing interval
void EnemySpawner::randomSpawnRabbit()
{
    if (SDL_GetTicks() - lastSpawnTime >= spawnInterval)
    {
        int randomX = rand() % (sys.SCREEN_WIDTH - 30);
        int randomY = rand() % (sys.SCREEN_HEIGHT - 30);

        EnemyRabbit *newRabbit = EnemyRabbit::getInstance(randomX, randomY, 30, 30);
        ge.addSprite(newRabbit);
        lastSpawnTime = SDL_GetTicks();

        // Gradually reduce the interval to increase difficulty
        if (spawnInterval > 1000) spawnInterval -= 200;
        if (spawnInterval < 1000) spawnInterval -= 20;
    }
}

// Spawns enemy ships from the top of the screen with increasing frequency
void EnemySpawner::randomSpawnShip()
{
    if (SDL_GetTicks() - lastSpawnTime >= spawnInterval)
    {
        int randomX = rand() % (sys.SCREEN_WIDTH - 30);

        EnemyShip *newEnemyShip = EnemyShip::getInstance(randomX, 0, 30, 30);
        ge.addSprite(newEnemyShip);
        lastSpawnTime = SDL_GetTicks();

        // Gradually reduce the interval to make spawning faster
        if (spawnInterval > 1000) spawnInterval -= 200;
        if (spawnInterval < 1000) spawnInterval -= 20;
    }
}

void EnemySpawner::tick()
{
    // Uncomment one of the following for the appropriate game mode

    // Uncomment for Rabbithammer
    // randomSpawnRabbit();

    // Uncomment for Starship
    randomSpawnShip();
}

// Dummy constructor used to place this spawner in the world
EnemySpawner::EnemySpawner() : Sprite(100, 100, 100, 100) {}

EnemySpawner::~EnemySpawner() {}

EnemySpawner *EnemySpawner::getInstance()
{
    return new EnemySpawner();
}

void EnemySpawner::draw() const {}

bool EnemySpawner::deleteAtRestart() const
{
    return false;
}
