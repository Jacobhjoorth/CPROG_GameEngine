#include "Constants.h"
#include "System.h"
#include <iostream>

namespace GameEngine
{

    System::System()
    {

        // Add window
        SDL_Init(SDL_INIT_EVERYTHING);
        win = SDL_CreateWindow("Game", 100, 60, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        // Add sounds
        Mix_OpenAudio(20050, AUDIO_S16SYS, 2, 4096);
        // musik = Mix_LoadWAV("/Users/kjellna/dev/cpp21/f13b/sounds/bgMusic.wav");
        music = Mix_LoadWAV((constants::gResPath + "sounds/Background.wav").c_str());
        Mix_PlayChannel(-1, music, -1);

        // Text

        // Initialize SDL_ttf
        TTF_Init();

        // Load font (replace "path/to/your/font.ttf" with the actual path to your font file)
        font = TTF_OpenFont((constants::gResPath + "fonts/Silkscreen-Regular.ttf").c_str(), 24);
        if (!font)
        {
            std::cerr << "Error: Unable to load font! " << TTF_GetError() << std::endl;
            // Handle error appropriately
        }
    }

    System::~System()
    {
        Mix_FreeChunk(music);
        Mix_CloseAudio();
        SDL_DestroyWindow(win);
        SDL_DestroyRenderer(ren);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
    }

    SDL_Renderer *System::get_ren() const
    {
        return ren;
    }

    void System::playSound(const char *filePath)
    {
        Mix_PlayChannel(-1, Mix_LoadWAV(filePath), 0);
    }

    void System::renderText(const std::string &text, int x, int y, int w, int h)
    {
        SDL_Color textColor = {255, 255, 255}; // White color

        // Create a surface from the text
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
        if (!textSurface)
        {
            std::cerr << "Error: Unable to create text surface! " << TTF_GetError() << std::endl;
            return;
        }

        // Create texture from the surface
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
        if (!textTexture)
        {
            std::cerr << "Error: Unable to create text texture! " << SDL_GetError() << std::endl;

            SDL_FreeSurface(textSurface);
            return;
        }

        // Set the position and dimensions of the text
        SDL_Rect textRect = {x, y, w, h};

        // Render the text
        SDL_RenderCopy(ren, textTexture, nullptr, &textRect);

        // Clean up
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }

    System sys;
}
