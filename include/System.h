#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace GameEngine
{

	class System
	{
	public:
		System();
		~System();
		SDL_Renderer *get_ren() const;
		void playSound(const char *filePath);
		void renderText(const std::string &text, int x, int y, int w, int h);
		static const int SCREEN_HEIGHT = 600;
		static const int SCREEN_WIDTH = 1000;

	protected:
	private:
		Mix_Chunk *music;
		SDL_Window *win;
		TTF_Font *font;
		SDL_Renderer *ren;
	};

	extern System sys;
}

#endif
