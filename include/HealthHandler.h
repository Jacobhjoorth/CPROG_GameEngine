#ifndef PLAYERHANDLER_H
#define PLAYERHANDLER_H

#include "Sprite.h"

using namespace GameEngine;

class HealthHandler : public Sprite
{
public:
    ~HealthHandler();
    static HealthHandler *getInstance();
    void draw() const override;
    void tick() override;
    bool deleteAtRestart() const override;

protected:
private:
    HealthHandler();
};

#endif
