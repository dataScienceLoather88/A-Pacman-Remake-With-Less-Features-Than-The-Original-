#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<fstream>
#include"PACMAN.h"
#include"pellets.h"
#include"background.h"
#include"GHOST.h"
#include"RED.h"
#include"PINK.h"
#include"BLUE.h"
#include"ORANGE.h"
#include"Global Variables.h"

using namespace std;

class gameGrid {
	const int gridTemplate[gameRows][gameColumns] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
													 ,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
													 ,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
													 ,{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
													 ,{2,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,2}
													 ,{2,3,2,2,2,2,1,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1,2,2,2,2,3,2}
													 ,{2,1,2,2,2,2,1,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1,2,2,2,2,1,2}
													 ,{2,1,2,2,2,2,1,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1,2,2,2,2,1,2}
													 ,{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2}
													 ,{2,1,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,1,2}
													 ,{2,1,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,1,2}
													 ,{2,1,1,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,1,1,2}
													 ,{2,2,2,2,2,2,1,2,2,2,2,2,0,2,2,0,2,2,2,2,2,1,2,2,2,2,2,2}
													 ,{0,0,0,0,0,2,1,2,2,2,2,2,0,2,2,0,2,2,2,2,2,1,2,0,0,0,0,0}
													 ,{0,0,0,0,0,2,1,2,2,0,0,0,0,0,0,0,0,0,0,2,2,1,2,0,0,0,0,0}
													 ,{0,0,0,0,0,2,1,2,2,0,2,2,2,2,2,2,2,2,0,2,2,1,2,0,0,0,0,0}
													 ,{2,2,2,2,2,2,1,2,2,0,2,2,0,0,0,0,2,2,0,2,2,1,2,2,2,2,2,2}
													 ,{0,0,0,0,0,0,1,0,0,0,2,2,0,2,2,0,2,2,0,0,0,1,0,0,0,0,0,0}
													 ,{2,2,2,2,2,2,1,2,2,0,2,2,0,0,0,0,2,2,0,2,2,1,2,2,2,2,2,2}
													 ,{0,0,0,0,0,2,1,2,2,0,2,2,2,2,2,2,2,2,0,2,2,1,2,0,0,0,0,0}
													 ,{0,0,0,0,0,2,1,2,2,0,0,0,0,0,0,0,0,0,0,2,2,1,2,0,0,0,0,0}
													 ,{0,0,0,0,0,2,1,2,2,0,2,2,2,2,2,2,2,2,0,2,2,1,2,0,0,0,0,0}
													 ,{2,2,2,2,2,2,1,2,2,0,2,2,2,2,2,2,2,2,0,2,2,1,2,2,2,2,2,2}
													 ,{2,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,2}
													 ,{2,1,2,2,2,2,1,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1,2,2,2,2,1,2}
													 ,{2,1,2,2,2,2,1,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1,2,2,2,2,1,2}
													 ,{2,1,1,1,2,2,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,2,2,1,1,1,2}
													 ,{2,2,2,1,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,1,2,2,2}
													 ,{2,2,2,1,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,1,2,2,2}
													 ,{2,1,1,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,1,1,2}
													 ,{2,3,2,2,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,2,2,3,2}
													 ,{2,1,2,2,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,2,2,1,2}
													 ,{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2}
													 ,{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
													 ,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
													 ,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };
	int gridToBeUsed[gameRows][gameColumns];
	int pelletsOnBoardForWinCondition;
	bool turnOnRunModeForGhosts_QuestionMark;
	pellets pelletsOnGrid;
	PACMAN player;
	int playerLives;
	const int maxPlayerLives = 3;
	const int numberOfGhosts = 4;
	GHOST* ghosts[4];
	//RED blinky;
	//PINK pinky;
	//BLUE inky;
	//ORANGE clyde;

	//collision variables
	bool collisionDetectionArray[4];

	bool fullyInitializeLevel;
	bool partiallyReinitializeLevel;
	bool replenishLives;

	//gamepause stuff
	sf::Clock gamePauseClock;
	const float gamePauseClockTimer = 0.5;

	//lives
	sf::Texture livesTexture;
	sf::Sprite livesSprite;
	sf::Texture readyTexture;
	sf::Sprite readySprite;

	//score
	SCORE score;

	//levels
	int level;
	int difficultyStatus;
	const int level1 = 1;
	const int level2 = 2;
	const int level3 = 3;

	sf::Texture appleTexture;
	sf::Sprite appleSprite;

	sf::Texture strawberryTexture;
	sf::Sprite strawberrySprite;

	sf::Texture cherryTexture;
	sf::Sprite cherrySprite;

public:
	gameGrid() {
		ghosts[0] = new RED; //blinky
		ghosts[1] = new PINK; //pinky
		ghosts[2] = new BLUE; //inky
		ghosts[3] = new ORANGE; //clyde

		this->level = 1;
		this->difficultyStatus = 0;
		this->replenishLives = true;
		this->initializeGameGrid();
		this->InitializeGhostVariablesThroughGameGrid();

		this->livesTexture.loadFromFile("PACMAN assets/pacman left.png");
		this->livesSprite.setTexture(this->livesTexture);
		this->livesSprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->readyTexture.loadFromFile("PACMAN assets/ready.png");
		this->readySprite.setTexture(this->readyTexture);
		this->readySprite.setTextureRect(sf::IntRect(0, 0, 54, 27));

		this->appleTexture.loadFromFile("PACMAN assets/apple.png");
		this->appleSprite.setTexture(this->appleTexture);
		this->appleSprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->strawberryTexture.loadFromFile("PACMAN assets/strawberry.png");
		this->strawberrySprite.setTexture(this->strawberryTexture);
		this->strawberrySprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->cherryTexture.loadFromFile("PACMAN assets/cherry.png");
		this->cherrySprite.setTexture(this->cherryTexture);
		this->cherrySprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));
	}

	~gameGrid() {
		for (int i = 0; i < numberOfGhosts; i++) {
			delete ghosts[i];
			ghosts[i] = nullptr;
		}
		cout << "gameGrid destroyed\n";
	}

	void initializeGameGrid() {
		this->turnOnRunModeForGhosts_QuestionMark = false;
		this->pelletsOnBoardForWinCondition = 245;
		this->gridToBeUsedInitializer();
		player.initializePacmanOnGrid(this->gridToBeUsed); //will initialize pacman on the game grid (20,13) along with the x/y coordinates of the player
		if (this->replenishLives) {
			this->level = 1;
			this->playerLives = maxPlayerLives;
		}
		//ghost stuff
		//ghosts[0] = &blinky;
		//ghosts[1] = &pinky;
		//ghosts[2] = &inky;
		//ghosts[3] = &clyde;

		//collision stuff
		for (int i = 0; i < numberOfGhosts; i++) {
			this->collisionDetectionArray[i] = false;
		}

		this->fullyInitializeLevel = false;
		this->partiallyReinitializeLevel = false;
		this->replenishLives = true;
	}

	void PartiallyInitializeGameGrid() {
		this->turnOnRunModeForGhosts_QuestionMark = false;
		player.initializePacmanOnGrid(this->gridToBeUsed); //will initialize pacman on the game grid (20,13) along with the x/y coordinates of the player

		//collision stuff
		for (int i = 0; i < numberOfGhosts; i++) {
			this->collisionDetectionArray[i] = false;
		}

		this->fullyInitializeLevel = false;
		this->partiallyReinitializeLevel = false;
	}

	//temporary
	void ghostModeSelection() {
		for (int i = 0; i < numberOfGhosts; i++) {
			ghosts[i]->changeGhostMode(this->turnOnRunModeForGhosts_QuestionMark);
		}
		this->turnOnRunModeForGhosts_QuestionMark = false;
	}

	void assignGhostTargetTiles() {
		for (int i = 0; i < numberOfGhosts; i++) {
			ghosts[i]->getTargetTiles(player, ghosts[0]);
		}
	}

	void InitializeGhostVariablesThroughGameGrid() {
		for (int i = 0; i < numberOfGhosts; i++) {
			ghosts[i]->initializeGhostVariables();
		}
	}

	void moveGhostsOnGridThroughGameGrid() {
		for (int i = 0; i < numberOfGhosts; i++) {
			ghosts[i]->moveGhostOnGrid(this->gridToBeUsed);
		}
	}

	void drawGhostsOnGridThroughGameGrid(sf::RenderWindow& window) {
		for (int i = 0; i < numberOfGhosts; i++) {
			ghosts[i]->drawGhostOnGrid(window);
		}
	}
	//temporary end

	void movePacmanOnGrid() {
		player.movePacman(this->gridToBeUsed, pelletsOnBoardForWinCondition, this->turnOnRunModeForGhosts_QuestionMark, score);
	}

	void drawPacmanOnGrid(sf::RenderWindow& window) {
		this->player.drawPacmanOnGrid(window);
	}

	void drawPelletsOnGrid(sf::RenderWindow& window) {
		for (int i = 0; i < pelletsOnGrid.smallPelletCount; i++)
			if (this->gridToBeUsed[pelletsOnGrid.smallPelletRowHolder[i]][pelletsOnGrid.smallPelletColHolder[i]] == 1)
				pelletsOnGrid.drawPellet1(window, pelletsOnGrid.smallPelletRowHolder[i], pelletsOnGrid.smallPelletColHolder[i]);

		for (int i = 0; i < pelletsOnGrid.largePelletCount; i++)
			if (this->gridToBeUsed[pelletsOnGrid.largePelletRowHolder[i]][pelletsOnGrid.largePelletColHolder[i]] == 3)
				pelletsOnGrid.drawPellet2(window, pelletsOnGrid.largePelletRowHolder[i], pelletsOnGrid.largePelletColHolder[i]);
	}

	bool areThePelletsGone_QuestionMark() {
		switch (this->pelletsOnBoardForWinCondition) {
		case 0:
			return true;
			break;
		default:
			return false;
			break;
		}
	}

	//collision functions

	// 2 is ghost is eaten, 1 if pacman dies, 0 for no collision
	void CollisionDetection() {
		for (int i = 0; i < numberOfGhosts; i++) {
			if (this->player.RowGetter() == this->ghosts[i]->getGhostCurrentRowTile() && this->player.ColGetter() == this->ghosts[i]->getGhostCurrentColTile() && ghosts[i]->getGhostMode() != 3)
				this->collisionDetectionArray[i] = true;
		}
	}

	int detectCollisionsInMain() {
		this->CollisionDetection();
		for (int i = 0; i < numberOfGhosts; i++) {
			if (this->collisionDetectionArray[i]) {
				switch (ghosts[i]->getGhostMode()) {
				case 2:
					return 2;
					break;
				case 1:
					return 1;
					break;
				case 0:
					return 1;
					break;
				case 3:
					return 0;
					break;
				default:
					return 0;
					break;
				}
			}
		}
	}

	void executeCollisionOutcome(static int collisionStatus, sf::RenderWindow& window) {
		switch (collisionStatus) {
		case 2:
			for (int i = 0; i < numberOfGhosts; i++) {
				if (this->collisionDetectionArray[i]) {
					this->collisionDetectionArray[i] = false;
					this->pauseGameOnGhostDeath(window);
					//cout << score.getGhostBonus() * score.getGhostBonusMultiplier();
					score += (score.getGhostBonus() * score.getGhostBonusMultiplier());
					score.multiplyGhostBonusMultiplier();
					ghosts[i]->moveGhostToGhostHouse();
				}
			}
			break;
		case 1:
			this->playerLives -= 1;
			if (this->playerLives == 0) {
				score.updateHighScore();
				score.setScoreZero();
				this->fullyInitializeLevel = true;
				this->pauseGameOnPlayerDeath(window);
				player.deathAnimation(window);

			}
			else {
				this->partiallyReinitializeLevel = true;
				this->pauseGameOnPlayerDeath(window);
			}
			//cout << "execute collision outcome: pacman dead\n";
			break;
		case 0:
			break;
		default:
			break;
		}
	}

	//score functions
	void drawScoreOnGrid(sf::RenderWindow& window) {
		this->score.drawScore(window);
	}

	//misc functions
	void pauseGameOnGhostDeath(sf::RenderWindow& window) {
		this->drawGhostsOnGridThroughGameGrid(window);
		score.drawGhostBonus(window, player.ColGetter(), player.RowGetter());
		//this->drawPacmanOnGrid(window);
		window.display();
		this->gamePauseClock.restart();
		while (this->gamePauseClock.getElapsedTime().asSeconds() < this->gamePauseClockTimer) {}
		window.clear();
	}

	void pauseGameOnPlayerDeath(sf::RenderWindow& window) {
		this->drawGhostsOnGridThroughGameGrid(window);
		window.display();
		this->gamePauseClock.restart();
		while (this->gamePauseClock.getElapsedTime().asSeconds() < this->gamePauseClockTimer) {}
		window.clear();
	}

	void drawLives(sf::RenderWindow& window) {
		for (int i = 0; i < this->playerLives; i++) {
			this->livesSprite.setPosition((i * 15), (35 * boxPixelsY) - 8);
			window.draw(livesSprite);
		}
	}

	bool getPartialInitializationCondition() {
		return this->partiallyReinitializeLevel;
	}

	void setPartialReinitializationFalse() {
		this->partiallyReinitializeLevel = false;
	}

	bool getFullInitializationCondition() {
		return this->fullyInitializeLevel;
	}

	void setFullInitializationTrue() {
		this->fullyInitializeLevel = true;
	}

	void setFullInitializationFalse() {
		this->fullyInitializeLevel = false;
	}

	void setReplenishLivesFalse() {
		this->replenishLives = false;
	}

	int getPacmanRow() {
		return player.RowGetter();
	}

	int getPacmanCol() {
		return player.ColGetter();
	}

	void ready(sf::RenderWindow& window, background& Background) {
		this->readySprite.setPosition(11 * boxPixelsX, 16 * boxPixelsY);
		Background.drawBackground(window);
		this->drawPelletsOnGrid(window);
		this->drawLives(window);
		this->difficultyIndicator(window);
		this->drawPacmanOnGrid(window);
		window.draw(this->readySprite);
		window.display();
		while (true) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				break;
		}
		window.clear();
	}

	void outputArray() {
		for (int i = 0; i < gameRows; i++) {
			for (int j = 0; j < gameColumns; j++) {
				cout << this->gridToBeUsed[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}

	void incrementLevel() {
		this->level += 1;
	}

	void levelUpdate() {
		switch (this->level) {
		case 1:
			if (difficultyStatus == level1)
				break;
			for (int i = 0; i < numberOfGhosts; i++) {
				ghosts[i]->startLevel1();
			}
			this->difficultyStatus = level1;
			cout << "Level 1 set\n";
			break;
		case 5:
			if (difficultyStatus == level2)
				break;
			for (int i = 0; i < numberOfGhosts; i++) {
				ghosts[i]->startLevel2();
			}
			this->difficultyStatus = level2;
			cout << "Level 2 set\n";
			break;
		case 10:
			if (difficultyStatus == level3)
				break;
			for (int i = 0; i < numberOfGhosts; i++) {
				ghosts[i]->startLevel3();
			}
			this->difficultyStatus = level3;
			cout << "Level 3 set\n";
			break;
		default:
			break;
		}
	}

	void difficultyIndicator(sf::RenderWindow& window) {
		switch (this->difficultyStatus) {
		case 1:
			this->strawberrySprite.setPosition((26 * 9), (35 * boxPixelsY) - 8);
			window.draw(strawberrySprite);
			break;
		case 2:
			this->cherrySprite.setPosition((26 * 9), (35 * boxPixelsY) - 8);
			window.draw(cherrySprite);
			break;
		case 3:
			this->appleSprite.setPosition((26 * 9), (35 * boxPixelsY) - 8);
			window.draw(appleSprite);
			break;
		default:
			break;
		}
	}


	void outputLevel() {
		cout << level;
	}

private:
	void gridToBeUsedInitializer() {
		for (int i = 0; i < gameRows; i++)
			for (int j = 0; j < gameColumns; j++)
				this->gridToBeUsed[i][j] = this->gridTemplate[i][j];

	}

};
