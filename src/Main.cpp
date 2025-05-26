#include "Constants.h" 
#include "GameEngine.h"
#include "System.h"
#include "EnemySpawner.h"
#include "Sprite.h"
#include "Pistol.h"
#include "EnemyShip.h"
#include "Sledgehammer.h"
#include "EnemyRabbit.h"
#include "HealthHandler.h"

using namespace GameEngine;

int main(int argc, char **argv)
{
    // -- ACTIVE GAME: STARSHIP --
    // Create and add player weapon, enemy spawner, and health logic to the game
    Pistol *pistol = Pistol::getInstance();
    EnemySpawner *spawner = EnemySpawner::getInstance();
    HealthHandler *handler = HealthHandler::getInstance();
    ge.addSprite(pistol);
    ge.addSprite(spawner);
    ge.addSprite(handler);

    // -- ALTERNATIVE GAME: RABBITHAMMER --
    // Uncomment to switch to hammer-based game
    // Sledgehammer *sledgehammer = Sledgehammer::getInstance();
    // EnemySpawner *spawner = EnemySpawner::getInstance();
    // HealthHandler *handler = HealthHandler::getInstance();
    // ge.addSprite(sledgehammer);
    // ge.addSprite(spawner);
    // ge.addSprite(handler);

    // Start the main game loop
    ge.run();

    return 0;
}
