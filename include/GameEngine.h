#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Sprite.h"
#include <vector>

namespace GameEngine
{

	class GameEngine
	{
	public:
		void addSprite(Sprite *comp);
		void removeSprite(Sprite *comp);
		void endScreen();
		void runGameStarship();
		void startScreenRabbit();
		void run();
		bool isMouseDown();
		void addEnemyKilled();
		void setEnemiesToKill(int amount);
		void setEnemiesToKillTxt(std::string name);
		void reducePlayerHealth();
		void setTotalHealth(int health);
		void setCurrentHealth(int health);
		bool checkCollision(const Sprite *a, const Sprite *b);
		const std::vector<Sprite *> &getComps() const;
		void resetGame();

	protected:
	private:
		std::vector<Sprite *> comps;
		std::vector<Sprite *> added, removed;

		int enemiesToKill = 1;
		std::string enemiesToKillTxt;
		int playerHealth = 1;
		int playerHealthCounter = 1;
		int enemyKilledCounter = 0;
		int lastDeletedSpeed = 1;
		bool gameWon = false;
		bool gameLost = false;
		bool quit;
		bool exitProgram;
		bool mouseDown = false;
	};

	extern GameEngine ge;

}

#endif