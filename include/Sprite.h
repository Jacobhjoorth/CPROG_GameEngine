#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <string>

namespace GameEngine
{

	class Sprite
	{
	public:
		virtual ~Sprite();
		virtual void mouseDown(int x, int y);
		virtual void draw() const = 0;
		virtual void tick() = 0;
		virtual std::string getType() const;
		virtual bool checkCollision(Sprite *other);
		virtual bool deleteAtRestart() const;

		// For collision
		SDL_Rect getRect() const;

	protected:
		Sprite(int x, int y, int width, int height);
		SDL_Rect rect;

	private:
		Sprite(const Sprite &) = delete;
		const Sprite &operator=(const Sprite &) = delete;
	};
}

#endif
