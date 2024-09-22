#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<fstream>
#include "SCORE.h"
#include"Global Variables.h"

using namespace std;

class PACMAN {
	sf::Texture pacmanRightTexture; sf::Sprite pacmanRightSprite;
	sf::Texture pacmanRight2Texture; sf::Sprite pacmanRight2Sprite;
	sf::Texture pacmanRight3Texture; sf::Sprite pacmanRight3Sprite;

	sf::Texture pacmanLeftTexture; sf::Sprite pacmanLeftSprite;
	sf::Texture pacmanLeft2Texture; sf::Sprite pacmanLeft2Sprite;
	sf::Texture pacmanLeft3Texture; sf::Sprite pacmanLeft3Sprite;

	sf::Texture pacmanUpTexture; sf::Sprite pacmanUpSprite;
	sf::Texture pacmanUp2Texture; sf::Sprite pacmanUp2Sprite;
	sf::Texture pacmanUp3Texture; sf::Sprite pacmanUp3Sprite;

	sf::Texture pacmanDownTexture; sf::Sprite pacmanDownSprite;
	sf::Texture pacmanDown2Texture; sf::Sprite pacmanDown2Sprite;
	sf::Texture pacmanDown3Texture; sf::Sprite pacmanDown3Sprite;

	sf::Texture deathTextureArray[5];
	sf::Sprite deathSpriteArray[5];

	sf::Clock pacmanClock;
	sf::Clock pacmanAnimationCycleClock;
	sf::Clock deathAnimationClock;

	const float pacmanMovementTimelimit = 0.1; //0.085
	const float pacmanAnimationTimeLimit = 0.075; //0.075
	const float deathAnimationTimer = 0.3;

	int Y_RowCoordinate;
	int X_ColCoordinate;

	int X_axis_direction;
	int Y_axis_direction;

	int animation_cycle;
	int animation_cycle_incrementer;

	void pacmanMOVER(int grid[][gameColumns], int yRowIncr, int& xColIncr) {
		yRowIncr *= -1;
		grid[this->Y_RowCoordinate + yRowIncr][this->X_ColCoordinate + xColIncr] = 0;
		swap(grid[this->Y_RowCoordinate][this->X_ColCoordinate], grid[this->Y_RowCoordinate + yRowIncr][this->X_ColCoordinate + xColIncr]);
		this->Y_RowCoordinate += yRowIncr;
		this->X_ColCoordinate += xColIncr;
		switch (this->Y_RowCoordinate) {
		case 17:
			switch (this->X_ColCoordinate) {
			case 0:
				this->X_ColCoordinate = 26;
				break;
			case 27:
				this->X_ColCoordinate = 1;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

		//cout << this->Y_RowCoordinate << " " << this->X_ColCoordinate << endl;
		//cout << this->pacmanAnimationTimeLimit << " " << this->pacmanMovementTimelimit << endl;
	}

public:
	PACMAN() {
		this->deathTextureArray[0].loadFromFile("PACMAN assets/death1.png");
		this->deathSpriteArray[0].setTexture(this->deathTextureArray[0]);
		this->deathSpriteArray[0].setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->deathTextureArray[1].loadFromFile("PACMAN assets/death2.png");
		this->deathSpriteArray[1].setTexture(this->deathTextureArray[1]);
		this->deathSpriteArray[1].setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->deathTextureArray[2].loadFromFile("PACMAN assets/death3.png");
		this->deathSpriteArray[2].setTexture(this->deathTextureArray[2]);
		this->deathSpriteArray[2].setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->deathTextureArray[3].loadFromFile("PACMAN assets/death4.png");
		this->deathSpriteArray[3].setTexture(this->deathTextureArray[3]);
		this->deathSpriteArray[3].setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->deathTextureArray[4].loadFromFile("PACMAN assets/death5.png");
		this->deathSpriteArray[4].setTexture(this->deathTextureArray[4]);
		this->deathSpriteArray[4].setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->pacmanRightTexture.loadFromFile("PACMAN assets/pacman right.png");
		this->pacmanRightSprite.setTexture(this->pacmanRightTexture);
		this->pacmanRightSprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));
		this->pacmanRight2Texture.loadFromFile("PACMAN assets/pacman right 2.png");
		this->pacmanRight2Sprite.setTexture(this->pacmanRight2Texture);
		this->pacmanRight2Sprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));
		this->pacmanRight3Texture.loadFromFile("PACMAN assets/pacman right 3.png");
		this->pacmanRight3Sprite.setTexture(this->pacmanRight3Texture);
		this->pacmanRight3Sprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->pacmanLeftTexture.loadFromFile("PACMAN assets/pacman left.png");
		this->pacmanLeftSprite.setTexture(this->pacmanLeftTexture);
		this->pacmanLeftSprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));
		this->pacmanLeft2Texture.loadFromFile("PACMAN assets/pacman left 2.png");
		this->pacmanLeft2Sprite.setTexture(this->pacmanLeft2Texture);
		this->pacmanLeft2Sprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));
		this->pacmanLeft3Texture.loadFromFile("PACMAN assets/pacman left 3.png");
		this->pacmanLeft3Sprite.setTexture(this->pacmanLeft3Texture);
		this->pacmanLeft3Sprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->pacmanUpTexture.loadFromFile("PACMAN assets/pacman up.png");
		this->pacmanUpSprite.setTexture(this->pacmanUpTexture);
		this->pacmanUpSprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));
		this->pacmanUp2Texture.loadFromFile("PACMAN assets/pacman up 2.png");
		this->pacmanUp2Sprite.setTexture(this->pacmanUp2Texture);
		this->pacmanUp2Sprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));
		this->pacmanUp3Texture.loadFromFile("PACMAN assets/pacman up 3.png");
		this->pacmanUp3Sprite.setTexture(this->pacmanUp3Texture);
		this->pacmanUp3Sprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->pacmanDownTexture.loadFromFile("PACMAN assets/pacman down.png");
		this->pacmanDownSprite.setTexture(this->pacmanDownTexture);
		this->pacmanDownSprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));
		this->pacmanDown2Texture.loadFromFile("PACMAN assets/pacman down 2.png");
		this->pacmanDown2Sprite.setTexture(this->pacmanDown2Texture);
		this->pacmanDown2Sprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));
		this->pacmanDown3Texture.loadFromFile("PACMAN assets/pacman down 3.png");
		this->pacmanDown3Sprite.setTexture(this->pacmanDown3Texture);
		this->pacmanDown3Sprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->Y_RowCoordinate = 26;
		this->X_ColCoordinate = 13;

		this->X_axis_direction = 1;
		this->Y_axis_direction = 0;

		this->animation_cycle = 1;
		this->animation_cycle_incrementer = 1;
	}

	~PACMAN() {
		cout << "PACMAN destroyed\n";
	}

	int RowGetter() {
		return this->Y_RowCoordinate;
	}

	int ColGetter() {
		return this->X_ColCoordinate;
	}

	int directionGetter_X_axis() {
		return this->X_axis_direction;
	}

	int directionGetter_Y_axis() {
		return this->X_axis_direction;
	}

	void initializePacmanOnGrid(int grid[][gameColumns]) {
		this->Y_RowCoordinate = 26;
		this->X_ColCoordinate = 13;

		this->X_axis_direction = 1;
		this->Y_axis_direction = 0;

		this->animation_cycle = 1;
		this->animation_cycle_incrementer = 1;

		grid[this->Y_RowCoordinate][this->X_ColCoordinate] = 5;
	}

	void movePacman(int grid[][gameColumns], int& pelletsOnBoardForWinCondition, bool& turnOnRunModeForGhosts_QuestionMark, SCORE& score) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (grid[this->Y_RowCoordinate - 1][this->X_ColCoordinate] != 2)) {
			this->Y_axis_direction = 1; this->X_axis_direction = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (grid[this->Y_RowCoordinate + 1][this->X_ColCoordinate] != 2)) {
			this->Y_axis_direction = -1; this->X_axis_direction = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (grid[this->Y_RowCoordinate][this->X_ColCoordinate + 1] != 2)) {
			this->Y_axis_direction = 0; this->X_axis_direction = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (grid[this->Y_RowCoordinate][this->X_ColCoordinate - 1] != 2)) {
			this->Y_axis_direction = 0; this->X_axis_direction = -1;
		}

		if (grid[this->Y_RowCoordinate + (this->Y_axis_direction * -1)][this->X_ColCoordinate + this->X_axis_direction] != 2) {
			if (this->pacmanAnimationCycleClock.getElapsedTime().asSeconds() > this->pacmanAnimationTimeLimit) {
				if ((this->animation_cycle == 1 && this->animation_cycle_incrementer == -1) || (this->animation_cycle == 3 && this->animation_cycle_incrementer == 1))
					this->animation_cycle_incrementer *= -1;
				this->animation_cycle += this->animation_cycle_incrementer;
				this->pacmanAnimationCycleClock.restart();
			}
		}

		if (this->pacmanClock.getElapsedTime().asSeconds() < this->pacmanMovementTimelimit)
			return;
		this->pacmanClock.restart();

		switch (this->X_axis_direction) {
		case 0:
			switch (this->Y_axis_direction) {
			case 1:
				switch (grid[this->Y_RowCoordinate - 1][this->X_ColCoordinate]) {
				case 2:
					break;
				case 1:
					this->pacmanMOVER(grid, this->Y_axis_direction, this->X_axis_direction);
					pelletsOnBoardForWinCondition -= 1;
					score += 1;
					break;
				case 3:
					this->pacmanMOVER(grid, this->Y_axis_direction, this->X_axis_direction);
					pelletsOnBoardForWinCondition -= 1;
					turnOnRunModeForGhosts_QuestionMark = true;
					score.initializeGhostBonusMultiplier();
					score += 1;
					break;
				default:
					this->pacmanMOVER(grid, this->Y_axis_direction, this->X_axis_direction);
					break;
				}
				break;
			case -1:
				switch (grid[this->Y_RowCoordinate + 1][this->X_ColCoordinate]) {
				case 2:
					break;
				case 1:
					this->pacmanMOVER(grid, this->Y_axis_direction, this->X_axis_direction);
					pelletsOnBoardForWinCondition -= 1;
					score += 1;
					break;
				case 3:
					this->pacmanMOVER(grid, this->Y_axis_direction, this->X_axis_direction);
					pelletsOnBoardForWinCondition -= 1;
					turnOnRunModeForGhosts_QuestionMark = true;
					score.initializeGhostBonusMultiplier();
					score += 1;
					break;
				default:
					this->pacmanMOVER(grid, this->Y_axis_direction, this->X_axis_direction);
					break;
				}
				break;
			}
			break;
		default:
			switch (this->X_axis_direction) {
			case 1:
				switch (grid[this->Y_RowCoordinate][this->X_ColCoordinate + 1]) {
				case 2:
					break;
				case 1:
					this->pacmanMOVER(grid, this->Y_axis_direction, this->X_axis_direction);
					pelletsOnBoardForWinCondition -= 1;
					score += 1;
					break;
				case 3:
					this->pacmanMOVER(grid, this->Y_axis_direction, this->X_axis_direction);
					pelletsOnBoardForWinCondition -= 1;
					turnOnRunModeForGhosts_QuestionMark = true;
					score.initializeGhostBonusMultiplier();
					score += 1;
					break;
				default:
					this->pacmanMOVER(grid, this->Y_axis_direction, this->X_axis_direction);
					break;
				}
				break;
			case -1:
				switch (grid[this->Y_RowCoordinate][this->X_ColCoordinate - 1]) {
				case 2:
					break;
				case 1:
					this->pacmanMOVER(grid, this->Y_axis_direction, this->X_axis_direction);
					pelletsOnBoardForWinCondition -= 1;
					score += 1;
					break;
				case 3:
					this->pacmanMOVER(grid, this->Y_axis_direction, this->X_axis_direction);
					pelletsOnBoardForWinCondition -= 1;
					turnOnRunModeForGhosts_QuestionMark = true;
					score.initializeGhostBonusMultiplier();
					score += 1;
					break;
				default:
					this->pacmanMOVER(grid, this->Y_axis_direction, this->X_axis_direction);
					break;
				}
				break;
			}
			break;
		}
		//cout << pelletsOnBoardForWinCondition << endl;
	}

	void drawPacmanOnGrid(sf::RenderWindow& window) {
		//rendering cycle for right/left movement
		switch (this->X_axis_direction) {
		case 1:
			switch (this->animation_cycle) {
			case 1:
				this->pacmanRightSprite.setPosition((this->X_ColCoordinate * boxPixelsX) - 3, (this->Y_RowCoordinate * boxPixelsY) - 3);
				window.draw(this->pacmanRightSprite);
				break;
			case 2:
				this->pacmanRight2Sprite.setPosition((this->X_ColCoordinate * boxPixelsX) - 3, (this->Y_RowCoordinate * boxPixelsY) - 3);
				window.draw(this->pacmanRight2Sprite);
				break;
			case 3:
				this->pacmanRight3Sprite.setPosition((this->X_ColCoordinate * boxPixelsX) - 3, (this->Y_RowCoordinate * boxPixelsY) - 3);
				window.draw(this->pacmanRight3Sprite);
				break;
			default:
				break;
			}
			break;
		case -1:
			switch (this->animation_cycle) {
			case 1:
				this->pacmanLeftSprite.setPosition((this->X_ColCoordinate * boxPixelsX) - 3, (this->Y_RowCoordinate * boxPixelsY) - 3);
				window.draw(this->pacmanLeftSprite);
				break;
			case 2:
				this->pacmanLeft2Sprite.setPosition((this->X_ColCoordinate * boxPixelsX) - 3, (this->Y_RowCoordinate * boxPixelsY) - 3);
				window.draw(this->pacmanLeft2Sprite);
				break;
			case 3:
				this->pacmanLeft3Sprite.setPosition((this->X_ColCoordinate * boxPixelsX) - 3, (this->Y_RowCoordinate * boxPixelsY) - 3);
				window.draw(this->pacmanLeft3Sprite);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

		//rendering cycle for up/down movement
		switch (this->Y_axis_direction) {
		case 1:
			switch (this->animation_cycle) {
			case 1:
				this->pacmanUpSprite.setPosition((this->X_ColCoordinate * boxPixelsX) - 3, (this->Y_RowCoordinate * boxPixelsY) - 3);
				window.draw(this->pacmanUpSprite);
				break;
			case 2:
				this->pacmanUp2Sprite.setPosition((this->X_ColCoordinate * boxPixelsX) - 3, (this->Y_RowCoordinate * boxPixelsY) - 3);
				window.draw(this->pacmanUp2Sprite);
				break;
			case 3:
				this->pacmanUp3Sprite.setPosition((this->X_ColCoordinate * boxPixelsX) - 3, (this->Y_RowCoordinate * boxPixelsY) - 3);
				window.draw(this->pacmanUp3Sprite);
				break;
			default:
				break;
			}
			break;
		case -1:
			switch (this->animation_cycle) {
			case 1:
				this->pacmanDownSprite.setPosition((this->X_ColCoordinate * boxPixelsX) - 3, (this->Y_RowCoordinate * boxPixelsY) - 3);
				window.draw(this->pacmanDownSprite);
				break;
			case 2:
				this->pacmanDown2Sprite.setPosition((this->X_ColCoordinate * boxPixelsX) - 3, (this->Y_RowCoordinate * boxPixelsY) - 3);
				window.draw(this->pacmanDown2Sprite);
				break;
			case 3:
				this->pacmanDown3Sprite.setPosition((this->X_ColCoordinate * boxPixelsX) - 3, (this->Y_RowCoordinate * boxPixelsY) - 3);
				window.draw(this->pacmanDown3Sprite);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}

	void deathAnimation(sf::RenderWindow& window) {
		window.clear();
		for (int i = 0; i < 4; i++) {
			this->deathSpriteArray[i].setPosition((this->X_ColCoordinate * boxPixelsX) - 3, (this->Y_RowCoordinate * boxPixelsY) - 3);
			window.draw(this->deathSpriteArray[i]);
			window.display();
			this->deathAnimationClock.restart();
			while (true) {
				if (this->deathAnimationClock.getElapsedTime().asSeconds() > this->deathAnimationTimer)
					break;
			}
			window.clear();
		}
		this->deathSpriteArray[4].setPosition((this->X_ColCoordinate * boxPixelsX) - 3, (this->Y_RowCoordinate * boxPixelsY) - 3);
		window.draw(this->deathSpriteArray[4]);
		window.display();
		this->deathAnimationClock.restart();
		while (true) {
			if (this->deathAnimationClock.getElapsedTime().asSeconds() > this->deathAnimationTimer * 2)
				break;
		}
		window.clear();
	}
};
