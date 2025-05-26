#ifndef SLEDGEHAMMER_H
#define SLEDGEHAMMER_H

#include "Sprite.h"

using namespace GameEngine;

class Sledgehammer : public Sprite
{
public:
	~Sledgehammer();
	static Sledgehammer *getInstance();

	void draw() const override;
	void tick() override;
	void followMouse();
	void mouseDown(int x, int y) override;
	bool deleteAtRestart() const override;

private:
	Sledgehammer();
	SDL_Texture *sledgehammerTexture;
};

#endif