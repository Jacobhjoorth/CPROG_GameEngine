#ifndef BULLET_H
#define BULLET_H

#include "Sprite.h"

using namespace GameEngine;

class Bullet : public Sprite
{
public:
	~Bullet();
	static Bullet *getInstance(int x);
	void draw() const override;
	void tick() override;
	void killOnCollision();
	bool deleteAtRestart() const override;

private:
	Bullet(int x);
	SDL_Texture *texture;
	int counter = 0;
};

#endif