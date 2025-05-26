#ifndef PISTOL_H
#define PISTOL_H

#include "Sprite.h"

using namespace GameEngine;

class Pistol : public Sprite
{
public:
	~Pistol();
	static Pistol *getInstance();
	void draw() const override;
	void tick() override;
	void followMouse();
	void mouseDown(int x, int y) override;
	void killOnCollision();
	bool deleteAtRestart() const override;

private:
	Pistol();
	SDL_Texture *pistolTexture;
};

#endif