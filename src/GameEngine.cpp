#include "GameEngine.h"
#include "Constants.h"
#include <SDL2/SDL.h>
#include "Sprite.h"
#include "System.h"
#include "HealthHandler.h"

namespace GameEngine
{
#define FPS 100 // Frames per second target

	// Increments enemy kill counter
	void GameEngine::addEnemyKilled()
	{
		enemyKilledCounter++;
	}

	// Decrease player health by one
	void GameEngine::reducePlayerHealth()
	{
		playerHealthCounter--;
	}

	// Set maximum player health
	void GameEngine::setTotalHealth(int health)
	{
		playerHealth = health;
	}

	// Set current player health
	void GameEngine::setCurrentHealth(int health)
	{
		playerHealthCounter = health;
	}

	// Set total enemies required to win
	void GameEngine::setEnemiesToKill(int other)
	{
		enemiesToKill = other;
	}

	// Set the UI text label for enemies-to-kill
	void GameEngine::setEnemiesToKillTxt(std::string name)
	{
		enemiesToKillTxt = name;
	}

	// Check whether mouse is being held down
	bool GameEngine::isMouseDown()
	{
		if (mouseDown)
		{
			return true;
		}
		return false;
	}

	// Add a sprite to the game in the next frame
	void GameEngine::addSprite(Sprite *comp)
	{
		added.push_back(comp);
	}

	// Mark a sprite for removal
	void GameEngine::removeSprite(Sprite *comp)
	{
		removed.push_back(comp);
	}

	// Get all active components (sprites) in the game
	const std::vector<Sprite *> &GameEngine::getComps() const
	{
		return comps;
	}

	// Reset the game state to initial conditions
	void GameEngine::resetGame()
	{
		// Delete all sprites marked for deletion
		for (std::vector<Sprite *>::iterator it = comps.begin(); it != comps.end();)
		{
			if ((*it)->deleteAtRestart())
			{
				delete *it;
				it = comps.erase(it);
			}
			else
			{
				++it;
			}
		}

		// Reset engine state flags
		quit = false;
		exitProgram = false;
		gameWon = false;
		gameLost = false;
		enemyKilledCounter = 0;
		added.clear();
		removed.clear();

		// Add the health UI handler again
		HealthHandler *handler = HealthHandler::getInstance();
		addSprite(handler);
	}

	// Show the end screen and wait for ENTER to restart or exit
	void GameEngine::endScreen()
	{
		bool enterPressed = false;

		// Render gray background and win/loss message
		SDL_SetRenderDrawColor(sys.get_ren(), 50, 50, 50, 255);
		SDL_RenderClear(sys.get_ren());
		if (gameWon && !gameLost)
		{
			sys.renderText("You won!", (sys.SCREEN_WIDTH - 110) / 2, (sys.SCREEN_HEIGHT - 50) / 2, 110, 25);
			sys.renderText("Press ENTER to restart", (sys.SCREEN_WIDTH - 260) / 2, (sys.SCREEN_HEIGHT) / 2, 260, 25);
		}
		else if (gameLost && !gameWon)
		{
			sys.renderText("You lost!", (sys.SCREEN_WIDTH - 110) / 2, (sys.SCREEN_HEIGHT - 50) / 2, 110, 25);
			sys.renderText("Press ENTER to restart", (sys.SCREEN_WIDTH - 260) / 2, (sys.SCREEN_HEIGHT) / 2, 260, 25);
		}

		SDL_RenderPresent(sys.get_ren());

		// Poll for quit or enter event
		while (!enterPressed && !exitProgram)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					quit = true;
					exitProgram = true;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_RETURN:
					case SDLK_KP_ENTER:
						enterPressed = true;
						break;
					}
					break;
				}
			}
		}

		// Restart the game state
		resetGame();
	}

	// Main game loop
	void GameEngine::run()
	{
		quit = false;
		exitProgram = false;
		Uint32 tickInterval = 1000 / FPS;

		while (!quit && !exitProgram)
		{
			Uint32 nextTick = SDL_GetTicks() + tickInterval;
			SDL_Event event;

			// Input handling
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					for (Sprite *c : comps)
					{
						dynamic_cast<Sprite *>(c)->mouseDown(event.button.x, event.button.y);
						mouseDown = true;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					mouseDown = false;
				}
			}

			// Add and remove sprites as needed
			for (Sprite *c : added)
			{
				comps.push_back(c);
			}
			added.clear();

			for (Sprite *c : removed)
			{
				for (std::vector<Sprite *>::iterator i = comps.begin(); i != comps.end();)
				{
					if (*i == c)
					{
						i = comps.erase(i);
						delete c;
					}
					else
					{
						i++;
					}
				}
			}
			removed.clear();

			// ---- RENDERING ----
			SDL_SetRenderDrawColor(sys.get_ren(), 50, 50, 50, 255);
			SDL_RenderClear(sys.get_ren());

			// Draw and update all game sprites
			for (Sprite *c : comps)
			{
				c->draw();
				c->tick();
			}

			// Render UI text
			std::string enemiesText = enemiesToKillTxt + std::to_string(enemyKilledCounter) + "/" + std::to_string(enemiesToKill);
			std::string healthText = "Health: " + std::to_string(playerHealthCounter) + "/" + std::to_string(playerHealth);
			sys.renderText(enemiesText, 10, 10, 270, 30);
			sys.renderText(healthText, 10, 50, 120, 28);
			SDL_RenderPresent(sys.get_ren());

			// Frame limiting to maintain FPS
			int delay = nextTick - SDL_GetTicks();
			if (delay > 0)
				SDL_Delay(delay);

			// Check win/loss conditions
			if (gameWon || gameLost)
			{
				endScreen();
			}

			if (enemyKilledCounter >= enemiesToKill)
			{
				gameWon = true;
			}

			if (playerHealthCounter == 0)
			{
				gameLost = true;
			}
		}
	}

	// Global instance of GameEngine
	GameEngine ge;
}
