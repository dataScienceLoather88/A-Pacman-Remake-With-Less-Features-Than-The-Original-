#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<fstream>
#include "PACMAN.h"
#include"Global Variables.h"

using namespace std;

class GHOST {
protected:
	sf::Texture upTexture;
	sf::Sprite upSprite;

	sf::Texture downTexture;
	sf::Sprite downSprite;

	sf::Texture rightTexture;
	sf::Sprite rightSprite;

	sf::Texture leftTexture;
	sf::Sprite leftSprite;

	sf::Texture runTexture;
	sf::Sprite runSprite;

	sf::Texture run2Texture;
	sf::Sprite run2Sprite;

	sf::Texture eyeTexture;
	sf::Sprite eyeSprite;

	sf::Clock ghostMovementClock;
	sf::Clock chaseModeClock;
	sf::Clock scatterModeClock;
	sf::Clock runModeClock;

	float ghostMovementTimer;
	float chaseModeTimer;
	float scatterModeTimer;
	float runModeTimer;

	const float eyeSpeed = 0.075;
	const float GhostSpeedLevel1 = 0.15;
	const float GhostSpeedLevel2 = 0.125;
	const float GhostSpeedLevel3 = 0.095;
	const float slowGhostSpeed = 0.5;
	const float scatterLevel1 = 6;
	const float scatterLevel2 = 4;
	const float scatterLevel3 = 2;
	const float runLevel1 = 6;
	const float runLevel2 = 4;
	const float runLevel3 = 2;
	float assignGhostSpeed;
	float assignScatter;
	float assignRun;

	int ghostMode; //0 chase, 1 scatter, 2 run
	int direction; //0 = R, 1 = U, 2 = L, 3 = D
	const int reverseDirectionValueHolder[4] = { 2, 3, 0, 1 };
	int directionOfTileBehindGhost;

	int randomDirectionHolder;
	int randomNumberGenerationDivisor;
	int runAnimationAlternator;

	int currentTileRow;
	int currentTileColumn;

	int targetTileRow;
	int targetTileColumn;

	int rightTileRowDifference;
	int rightTileColDifference;
	int rightTileTotalDifference;

	int leftTileRowDifference;
	int leftTileColDifference;
	int leftTileTotalDifference;

	int upTileRowDifference;
	int upTileColDifference;
	int upTileTotalDifference;

	int downTileRowDifference;
	int downTileColDifference;
	int downTileTotalDifference;

	int tileDifferenceHolderArray[4];
	int tileDifferenceDirectionHolder[4];

	void calculateRightTileDifference(int grid[][gameColumns]) {
		//if the right tile is behind the ghost it sets the distance as the highest possible value and breaks;
		switch (this->directionOfTileBehindGhost) {
		case 0:
			this->rightTileTotalDifference = 162;
			return;
			break;
		default:
			break;
		}

		//if tile to the right is a wall it sets the distance as the highest possible value and breaks
		switch (grid[this->currentTileRow][this->currentTileColumn + 1]) {
		case 2:
			this->rightTileTotalDifference = 162;
			return;
			break;
		default:
			break;
		}

		//distance calculation
		this->rightTileRowDifference = this->currentTileRow - this->targetTileRow;
		this->rightTileColDifference = (this->currentTileColumn + 1) - this->targetTileColumn;
		if (this->rightTileRowDifference < 0)
			this->rightTileRowDifference *= -1;
		if (this->rightTileColDifference < 0)
			this->rightTileColDifference *= -1;
		this->rightTileTotalDifference = this->rightTileRowDifference + this->rightTileColDifference;
	}

	void calculateLeftTileDifference(int grid[][gameColumns]) {
		//if the right tile is behind the ghost it sets the distance as the highest possible value and breaks;
		switch (this->directionOfTileBehindGhost) {
		case 2:
			this->leftTileTotalDifference = 162;
			return;
			break;
		default:
			break;
		}

		//if tile to the right is a wall it sets the distance as the highest possible value and breaks
		switch (grid[this->currentTileRow][this->currentTileColumn - 1]) {
		case 2:
			this->leftTileTotalDifference = 162;
			return;
			break;
		default:
			break;
		}

		//distance calculation
		this->leftTileRowDifference = this->currentTileRow - this->targetTileRow;
		this->leftTileColDifference = (this->currentTileColumn - 1) - this->targetTileColumn;
		if (this->leftTileRowDifference < 0)
			this->leftTileRowDifference *= -1;
		if (this->leftTileColDifference < 0)
			this->leftTileColDifference *= -1;
		this->leftTileTotalDifference = this->leftTileRowDifference + this->leftTileColDifference;
	}

	void calculateUpTileDifference(int grid[][gameColumns]) {
		//if the right tile is behind the ghost it sets the distance as the highest possible value and breaks;
		switch (this->directionOfTileBehindGhost) {
		case 1:
			this->upTileTotalDifference = 162;
			return;
			break;
		default:
			break;
		}

		//if tile to the right is a wall it sets the distance as the highest possible value and breaks
		switch (grid[this->currentTileRow - 1][this->currentTileColumn]) {
		case 2:
			this->upTileTotalDifference = 162;
			return;
			break;
		default:
			break;
		}

		//distance calculation
		this->upTileRowDifference = (this->currentTileRow - 1) - this->targetTileRow;
		this->upTileColDifference = this->currentTileColumn - this->targetTileColumn;
		if (this->upTileRowDifference < 0)
			this->upTileRowDifference *= -1;
		if (this->upTileColDifference < 0)
			this->upTileColDifference *= -1;
		this->upTileTotalDifference = this->upTileRowDifference + this->upTileColDifference;
	}

	void calculateDownTileDifference(int grid[][gameColumns]) {
		//if the right tile is behind the ghost it sets the distance as the highest possible value and breaks;
		switch (this->directionOfTileBehindGhost) {
		case 3:
			this->downTileTotalDifference = 162;
			return;
			break;
		default:
			break;
		}

		//if tile to the right is a wall it sets the distance as the highest possible value and breaks
		switch (grid[this->currentTileRow + 1][this->currentTileColumn]) {
		case 2:
			this->downTileTotalDifference = 162;
			return;
			break;
		default:
			break;
		}

		//distance calculation
		this->downTileRowDifference = (this->currentTileRow + 1) - this->targetTileRow;
		this->downTileColDifference = this->currentTileColumn - this->targetTileColumn;
		if (this->downTileRowDifference < 0)
			this->downTileRowDifference *= -1;
		if (this->downTileColDifference < 0)
			this->downTileColDifference *= -1;
		this->downTileTotalDifference = this->downTileRowDifference + this->downTileColDifference;
	}

	void MOVEghost(int grid[][gameColumns]) {
		//algorithm for mode 2
		if (this->ghostMode == 2) {
			this->calculateRightTileDifference(grid);
			this->calculateLeftTileDifference(grid);
			this->calculateUpTileDifference(grid);
			this->calculateDownTileDifference(grid);

			//original assignment order was right up left down (0,1,2,3)
			this->tileDifferenceDirectionHolder[0] = 1;
			this->tileDifferenceDirectionHolder[1] = 2;
			this->tileDifferenceDirectionHolder[2] = 3;
			this->tileDifferenceDirectionHolder[3] = 0;

			this->tileDifferenceHolderArray[0] = this->upTileTotalDifference;
			this->tileDifferenceHolderArray[1] = this->leftTileTotalDifference;
			this->tileDifferenceHolderArray[2] = this->downTileTotalDifference;
			this->tileDifferenceHolderArray[3] = this->rightTileTotalDifference;

			bubbleSort(this->tileDifferenceHolderArray, this->tileDifferenceDirectionHolder, 4);

			for (this->randomNumberGenerationDivisor = 0; this->tileDifferenceHolderArray[this->randomNumberGenerationDivisor + 1] != 162; this->randomNumberGenerationDivisor++) {}
			this->randomDirectionHolder = rand() % (this->randomNumberGenerationDivisor + 1);
			this->randomDirectionHolder = this->tileDifferenceDirectionHolder[this->randomDirectionHolder];

			switch (this->randomDirectionHolder) {
			case 0:
				this->currentTileColumn += 1;
				if (this->currentTileRow == 17 && this->currentTileColumn == 27) {
					this->currentTileColumn = 1;
					this->direction = 0;
					this->directionOfTileBehindGhost = this->reverseDirectionValueHolder[this->direction];
				}
				this->direction = 0;
				this->directionOfTileBehindGhost = this->reverseDirectionValueHolder[this->direction];
				break;
			case 1:
				this->currentTileRow -= 1;
				this->direction = 1;
				this->directionOfTileBehindGhost = this->reverseDirectionValueHolder[this->direction];
				break;
			case 2:
				this->currentTileColumn -= 1;
				if (this->currentTileRow == 17 && this->currentTileColumn == 0) {
					this->currentTileColumn = 26;
					this->direction = 2;
					this->directionOfTileBehindGhost = this->reverseDirectionValueHolder[this->direction];
				}
				this->direction = 2;
				this->directionOfTileBehindGhost = this->reverseDirectionValueHolder[this->direction];
				break;
			case 3:
				this->currentTileRow += 1;
				this->direction = 3;
				this->directionOfTileBehindGhost = this->reverseDirectionValueHolder[this->direction];
				break;
			}
			return;
		}

		//algorithm for modes 0 and 1
		this->calculateRightTileDifference(grid);
		this->calculateLeftTileDifference(grid);
		this->calculateUpTileDifference(grid);
		this->calculateDownTileDifference(grid);

		//original assignment order was right up left down (0,1,2,3)
		this->tileDifferenceDirectionHolder[0] = 1;
		this->tileDifferenceDirectionHolder[1] = 2;
		this->tileDifferenceDirectionHolder[2] = 3;
		this->tileDifferenceDirectionHolder[3] = 0;

		this->tileDifferenceHolderArray[0] = this->upTileTotalDifference;
		this->tileDifferenceHolderArray[1] = this->leftTileTotalDifference;
		this->tileDifferenceHolderArray[2] = this->downTileTotalDifference;
		this->tileDifferenceHolderArray[3] = this->rightTileTotalDifference;


		bubbleSort(this->tileDifferenceHolderArray, this->tileDifferenceDirectionHolder, 4);

		//teleports eyes inside of the ghost house/handles eye loops
		if (this->ghostMode == 3) {
			//loop handling
			switch (this->currentTileRow) {
			case 8:
				switch (this->currentTileColumn) {
				case 9:
					this->tileDifferenceDirectionHolder[0] = 3;
					break;
				case 18:
					this->tileDifferenceDirectionHolder[0] = 3;
					break;
				default:
					break;
				}
				break;
			case 26:
				switch (this->currentTileColumn) {
				case 12:
					this->tileDifferenceDirectionHolder[0] = 1;
					break;
				case 15:
					this->tileDifferenceDirectionHolder[0] = 1;
					break;
				default:
					break;
				}
				break;
			case 14:
				switch (this->currentTileColumn) {
				case 12:
					this->tileDifferenceDirectionHolder[0] = 0;
					break;
				case 15:
					this->tileDifferenceDirectionHolder[0] = 2;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}

			//teleportation
			switch (this->currentTileRow) {
			case 14:
				switch (this->currentTileColumn) {
				case 13:
					this->currentTileRow = 16;
					return;
					break;
				case 14:
					this->currentTileRow = 16;
					return;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}

		//teleports outside of the ghost house
		if (this->ghostMode != 3) {
			switch (this->currentTileRow) {
			case 16:
				switch (this->currentTileColumn) {
				case 13:
					this->currentTileRow = 14;
					return;
					break;
				case 14:
					this->currentTileRow = 14;
					return;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}

		//checks for tiles where its illegal to go up
		if (this->ghostMode != 3) {
			switch (this->currentTileRow) {
			case 14:
				switch (this->currentTileColumn) {
				case 12:
					switch (this->tileDifferenceDirectionHolder[0]) {
					case 1:
						this->tileDifferenceDirectionHolder[0] = this->direction;
						break;
					default:
						break;
					}
					break;
				case 15:
					switch (this->tileDifferenceDirectionHolder[0]) {
					case 1:
						this->tileDifferenceDirectionHolder[0] = this->direction;
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
				break;
			case 26:
				switch (this->currentTileColumn) {
				case 12:
					switch (this->tileDifferenceDirectionHolder[0]) {
					case 1:
						this->tileDifferenceDirectionHolder[0] = this->direction;
						break;
					default:
						break;
					}
					break;
				case 15:
					switch (this->tileDifferenceDirectionHolder[0]) {
					case 1:
						this->tileDifferenceDirectionHolder[0] = this->direction;
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}

		//actually moves the ghosts
		switch (this->tileDifferenceDirectionHolder[0]) {
		case 0:
			this->currentTileColumn += 1;
			if (this->currentTileRow == 17 && this->currentTileColumn == 27) {
				this->currentTileColumn = 1;
			}
			this->direction = 0;
			this->directionOfTileBehindGhost = this->reverseDirectionValueHolder[this->direction];
			break;
		case 1:
			this->currentTileRow -= 1;
			this->direction = 1;
			this->directionOfTileBehindGhost = this->reverseDirectionValueHolder[this->direction];
			break;
		case 2:
			this->currentTileColumn -= 1;
			if (this->currentTileRow == 17 && this->currentTileColumn == 0) {
				this->currentTileColumn = 26;
			}
			this->direction = 2;
			this->directionOfTileBehindGhost = this->reverseDirectionValueHolder[this->direction];
			break;
		case 3:
			this->currentTileRow += 1;
			this->direction = 3;
			this->directionOfTileBehindGhost = this->reverseDirectionValueHolder[this->direction];
			break;
		}
	}

public:
	virtual ~GHOST() {
		cout << "GHOST destroyed\n";
	}
	virtual void startLevel1() {}
	virtual void startLevel2() {}
	virtual void startLevel3() {}
	virtual void initializeGhostVariables() {};
	virtual void moveGhostToGhostHouse() {};
	virtual void changeGhostMode(bool& turnOnRunModeForGhosts_QuestionMark) {};
	virtual void getTargetTiles(PACMAN& player, GHOST*& ghosts) {};
	virtual void moveGhostOnGrid(int grid[][gameColumns]) {};
	virtual void drawGhostOnGrid(sf::RenderWindow& window) {};
	virtual int getGhostMode() { return 0; };
	virtual int getGhostCurrentRowTile() { return 0; };
	virtual int getGhostCurrentColTile() { return 0; };
};
