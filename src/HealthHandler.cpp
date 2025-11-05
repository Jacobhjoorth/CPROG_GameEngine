#include "HealthHandler.h"
#include "GameEngine.h"

using namespace GameEngine;

HealthHandler::HealthHandler() : Sprite(100, 100, 100, 100)
{
    ge.setTotalHealth(3);

    ge.setCurrentHealth(3);

    // - STARSHIP -
    ge.setEnemiesToKillTxt("Ships to destroy: ");
    
    // - RABBITHAMMER -
    // ge.setEnemiesToKillTxt("Rabbits to hit: ");

    // Total number of enemies required to win
    ge.setEnemiesToKill(20);
}

HealthHandler *HealthHandler::getInstance()
{
    return new HealthHandler();
}

HealthHandler::~HealthHandler() {}

void HealthHandler::draw() const {}

void HealthHandler::tick()
{
}

bool HealthHandler::deleteAtRestart() const
{
    return true;
}
