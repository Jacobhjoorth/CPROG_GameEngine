#include "HealthHandler.h"
#include "GameEngine.h"

using namespace GameEngine;

// Constructor: Initializes player health and number of enemies to kill
HealthHandler::HealthHandler() : Sprite(100, 100, 100, 100)
{
    // Set total health points
    ge.setTotalHealth(3);

    // Set current health
    ge.setCurrentHealth(3);

    // UI text for number of enemies to kill
    // - STARSHIP -
    ge.setEnemiesToKillTxt("Ships to destroy: ");
    // - RABBITHAMMER -
    // ge.setEnemiesToKillTxt("Rabbits to hit: ");

    // Total number of enemies required to win
    ge.setEnemiesToKill(20);
}

// Factory method to create a HealthHandler instance
HealthHandler *HealthHandler::getInstance()
{
    return new HealthHandler();
}

HealthHandler::~HealthHandler() {}

// This component does not render anything
void HealthHandler::draw() const {}

// This component has no tick behavior
void HealthHandler::tick()
{
}

// Should be removed when the game resets
bool HealthHandler::deleteAtRestart() const
{
    return true;
}