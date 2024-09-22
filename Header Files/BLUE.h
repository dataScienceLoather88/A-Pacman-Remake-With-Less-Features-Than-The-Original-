#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<fstream>
#include "GHOST.h"
#include"Global Variables.h"

using namespace std;

class BLUE : public GHOST {

	const int blueHomeTileRow = 35;
	const int blueHomeTileCol = 27;
	const int blueGhostHouseHomeRow = 17;
	const int blueGhostHouseHomeCol = 15;
	const int blueGhostHouseHomeDirection = 3;
	const int blueGhostHouseHomeMode = 1;
	int twoTilesAheadOfPacmanRow;
	int twoTilesAheadOfPacmanCol;

public:
	BLUE() {
		this->assignGhostSpeed = this->GhostSpeedLevel1;
		this->assignScatter = this->scatterLevel1;
		this->assignRun = this->runLevel1;

		this->rightTexture.loadFromFile("PACMAN assets/blue right.png");
		this->rightSprite.setTexture(this->rightTexture);
		this->rightSprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->leftTexture.loadFromFile("PACMAN assets/blue left.png");
		this->leftSprite.setTexture(this->leftTexture);
		this->leftSprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->upTexture.loadFromFile("PACMAN assets/blue up.png");
		this->upSprite.setTexture(this->upTexture);
		this->upSprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->downTexture.loadFromFile("PACMAN assets/blue down.png");
		this->downSprite.setTexture(this->downTexture);
		this->downSprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->runTexture.loadFromFile("PACMAN assets/run.png");
		this->runSprite.setTexture(this->runTexture);
		this->runSprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->run2Texture.loadFromFile("PACMAN assets/run2.png");
		this->run2Sprite.setTexture(this->run2Texture);
		this->run2Sprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->eyeTexture.loadFromFile("PACMAN assets/eyes.png");
		this->eyeSprite.setTexture(this->eyeTexture);
		this->eyeSprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));
	}

	virtual ~BLUE() {
		cout << "BLUE destroyed\n";
	}

	void startLevel1() {
		this->assignGhostSpeed = this->GhostSpeedLevel1;
		this->assignScatter = this->scatterLevel1;
		this->assignRun = this->runLevel1;
	}

	void startLevel2() {
		this->assignGhostSpeed = this->GhostSpeedLevel2;
		this->assignScatter = this->scatterLevel2;
		this->assignRun = this->runLevel2;
	}

	void startLevel3() {
		this->assignGhostSpeed = this->GhostSpeedLevel3;
		this->assignScatter = this->scatterLevel3;
		this->assignRun = this->runLevel3;
	}

	void initializeGhostVariables() {
		this->ghostMovementTimer = this->assignGhostSpeed;
		this->ghostMode = 0;

		this->direction = this->blueGhostHouseHomeDirection; //3
		this->directionOfTileBehindGhost = this->reverseDirectionValueHolder[this->direction];

		this->currentTileRow = this->blueGhostHouseHomeRow; //14
		this->currentTileColumn = this->blueGhostHouseHomeCol; //18

		this->chaseModeTimer = 7;
		this->scatterModeTimer = this->assignScatter;
		this->runModeTimer = this->assignRun;

		this->runAnimationAlternator = 1;
	}

	void moveGhostToGhostHouse() {
		this->ghostMode = 3;
		this->targetTileRow = this->blueGhostHouseHomeRow;
		this->targetTileColumn = this->blueGhostHouseHomeCol;
		this->ghostMovementTimer = this->eyeSpeed;
		return;

		this->ghostMode = this->blueGhostHouseHomeMode;
		this->direction = this->blueGhostHouseHomeDirection;
		this->ghostMovementTimer = this->assignGhostSpeed;
		this->directionOfTileBehindGhost = this->reverseDirectionValueHolder[this->direction];
		this->currentTileRow = this->blueGhostHouseHomeRow; //14
		this->currentTileColumn = this->blueGhostHouseHomeCol; //18
	}

	void changeGhostMode(bool& turnOnRunModeForGhosts_QuestionMark) {
		if (this->ghostMode == 3) {
			if (this->currentTileRow == this->blueGhostHouseHomeRow && this->currentTileColumn == this->blueGhostHouseHomeCol) {
				this->ghostMode = this->blueGhostHouseHomeMode;
				this->direction = this->blueGhostHouseHomeDirection;
				this->ghostMovementTimer = this->assignGhostSpeed;
				this->directionOfTileBehindGhost = this->reverseDirectionValueHolder[this->direction];
				this->currentTileRow = this->blueGhostHouseHomeRow; //14
				this->currentTileColumn = this->blueGhostHouseHomeCol; //18
			}
			return;
		}

		if (turnOnRunModeForGhosts_QuestionMark) {
			this->ghostMode = 2;
			this->ghostMovementTimer = this->slowGhostSpeed;
			this->runModeClock.restart();
			swap(this->direction, this->directionOfTileBehindGhost);
		}

		switch (this->ghostMode) {
		case 0:
			if (this->chaseModeClock.getElapsedTime().asSeconds() > this->chaseModeTimer) {
				this->ghostMode = 1;
				this->scatterModeClock.restart();
			}
			break;
		case 1:
			if (this->scatterModeClock.getElapsedTime().asSeconds() > this->scatterModeTimer) {
				this->ghostMode = 0;
				this->chaseModeClock.restart();
			}
			break;
		case 2:
			if (this->runModeClock.getElapsedTime().asSeconds() > this->runModeTimer) {
				this->ghostMode = 1;
				this->ghostMovementTimer = this->assignGhostSpeed;
				this->chaseModeClock.restart();
			}
			break;
		default:
			break;
		}
	}

	void getTargetTiles(PACMAN& player, GHOST*& ghosts) {
		switch (this->ghostMode) {
		case 0:
			this->twoTilesAheadOfPacmanRow = (player.RowGetter() + (player.directionGetter_Y_axis() * 2));
			this->twoTilesAheadOfPacmanCol = (player.ColGetter() + (player.directionGetter_X_axis() * 2));
			this->targetTileRow = this->twoTilesAheadOfPacmanRow + (this->twoTilesAheadOfPacmanRow - ghosts->getGhostCurrentRowTile());
			this->targetTileColumn = this->twoTilesAheadOfPacmanCol + (this->twoTilesAheadOfPacmanCol - ghosts->getGhostCurrentColTile());
			break;
		case 1:
			this->targetTileRow = this->blueHomeTileRow;
			this->targetTileColumn = this->blueHomeTileCol;
			break;
		default:
			break;
		}
	}

	void moveGhostOnGrid(int grid[][gameColumns]) {
		if (this->ghostMovementClock.getElapsedTime().asSeconds() < this->ghostMovementTimer)
			return;
		this->ghostMovementClock.restart();
		this->MOVEghost(grid);
	}

	void drawGhostOnGrid(sf::RenderWindow& window) {
		if (this->ghostMode == 3) {
			this->eyeSprite.setPosition((this->currentTileColumn * boxPixelsX) - 3, (this->currentTileRow * boxPixelsY) - 3);
			window.draw(this->eyeSprite);
			return;
		}

		if (this->ghostMode == 2) {
			switch (this->runAnimationAlternator) {
			case 1:
				this->runSprite.setPosition((this->currentTileColumn * boxPixelsX) - 3, (this->currentTileRow * boxPixelsY) - 3);
				window.draw(this->runSprite);
				this->runAnimationAlternator += 1;
				break;
			case 2:
				this->run2Sprite.setPosition((this->currentTileColumn * boxPixelsX) - 3, (this->currentTileRow * boxPixelsY) - 3);
				window.draw(this->run2Sprite);
				this->runAnimationAlternator -= 1;
				break;
			default:
				break;
			}
			return;
		}

		switch (this->direction) {
		case 0:
			this->rightSprite.setPosition((this->currentTileColumn * boxPixelsX) - 3, (this->currentTileRow * boxPixelsY) - 3);
			window.draw(this->rightSprite);
			break;
		case 1:
			this->upSprite.setPosition((this->currentTileColumn * boxPixelsX) - 3, (this->currentTileRow * boxPixelsY) - 3);
			window.draw(this->upSprite);
			break;
		case 2:
			this->leftSprite.setPosition((this->currentTileColumn * boxPixelsX) - 3, (this->currentTileRow * boxPixelsY) - 3);
			window.draw(this->leftSprite);
			break;
		case 3:
			this->downSprite.setPosition((this->currentTileColumn * boxPixelsX) - 3, (this->currentTileRow * boxPixelsY) - 3);
			window.draw(this->downSprite);
			break;
		default:
			break;
		}
	}

	int getGhostMode() {
		return this->ghostMode;
	}

	int getGhostCurrentRowTile() {
		return this->currentTileRow;
	}

	int getGhostCurrentColTile() {
		return this->currentTileColumn;
	}
};
