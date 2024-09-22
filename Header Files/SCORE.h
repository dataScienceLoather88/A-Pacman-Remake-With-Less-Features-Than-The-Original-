#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<fstream>
#include"Global Variables.h"

using namespace std;

class SCORE {
	int score;
	int highScore;
	int tempVar;
	int scoreArray[5];
	int highScoreArray[5];
	const int arraySize = 5;
	const int maxScore = 99999;
	sf::Texture numberTextureArray[10];
	sf::Sprite numberSpriteArray[10];
	sf::Texture highScoreTexture;
	sf::Sprite highScoreSprite;

	sf::Texture ghostBonusTextureArray[9];
	sf::Sprite ghostBonusSpriteArray[9];

	ifstream highScoreIN;
	ofstream highscoreOUT;

	const int ghostBonus = 10;
	int ghostBonusMultiplier;

public:
	SCORE() {
		highScoreIN.open("highscore.txt");
		highScoreIN >> highScore;
		highScoreIN.close();
		if (highScore > maxScore)
			highScore = maxScore;
		this->tempVar = this->highScore;
		for (int i = this->arraySize - 1; i >= 0; i--) {
			this->highScoreArray[i] = this->tempVar % 10;
			this->tempVar /= 10;
		}

		this->score = 0;
		this->tempVar = this->score;
		for (int i = 0; i < this->arraySize; i++) {
			this->scoreArray[i] = 0;
		}

		this->ghostBonusTextureArray[1].loadFromFile("PACMAN assets/10.png");
		this->ghostBonusSpriteArray[1].setTexture(this->ghostBonusTextureArray[1]);
		this->ghostBonusSpriteArray[1].setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->ghostBonusTextureArray[2].loadFromFile("PACMAN assets/20.png");
		this->ghostBonusSpriteArray[2].setTexture(this->ghostBonusTextureArray[2]);
		this->ghostBonusSpriteArray[2].setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->ghostBonusTextureArray[4].loadFromFile("PACMAN assets/40.png");
		this->ghostBonusSpriteArray[4].setTexture(this->ghostBonusTextureArray[4]);
		this->ghostBonusSpriteArray[4].setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->ghostBonusTextureArray[8].loadFromFile("PACMAN assets/80.png");
		this->ghostBonusSpriteArray[8].setTexture(this->ghostBonusTextureArray[8]);
		this->ghostBonusSpriteArray[8].setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));

		this->highScoreTexture.loadFromFile("PACMAN assets/highscore.png");
		this->highScoreSprite.setTexture(this->highScoreTexture);
		this->highScoreSprite.setTextureRect(sf::IntRect(0, 0, 79, 7));

		this->numberTextureArray[0].loadFromFile("PACMAN assets/zero3.png");
		this->numberSpriteArray[0].setTexture(this->numberTextureArray[0]);
		this->numberSpriteArray[0].setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

		this->numberTextureArray[1].loadFromFile("PACMAN assets/one3.png");
		this->numberSpriteArray[1].setTexture(this->numberTextureArray[1]);
		this->numberSpriteArray[1].setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

		this->numberTextureArray[2].loadFromFile("PACMAN assets/two3.png");
		this->numberSpriteArray[2].setTexture(this->numberTextureArray[2]);
		this->numberSpriteArray[2].setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

		this->numberTextureArray[3].loadFromFile("PACMAN assets/three3.png");
		this->numberSpriteArray[3].setTexture(this->numberTextureArray[3]);
		this->numberSpriteArray[3].setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

		this->numberTextureArray[4].loadFromFile("PACMAN assets/four3.png");
		this->numberSpriteArray[4].setTexture(this->numberTextureArray[4]);
		this->numberSpriteArray[4].setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

		this->numberTextureArray[5].loadFromFile("PACMAN assets/five3.png");
		this->numberSpriteArray[5].setTexture(this->numberTextureArray[5]);
		this->numberSpriteArray[5].setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

		this->numberTextureArray[6].loadFromFile("PACMAN assets/six3.png");
		this->numberSpriteArray[6].setTexture(this->numberTextureArray[6]);
		this->numberSpriteArray[6].setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

		this->numberTextureArray[7].loadFromFile("PACMAN assets/seven3.png");
		this->numberSpriteArray[7].setTexture(this->numberTextureArray[7]);
		this->numberSpriteArray[7].setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

		this->numberTextureArray[8].loadFromFile("PACMAN assets/eight3.png");
		this->numberSpriteArray[8].setTexture(this->numberTextureArray[8]);
		this->numberSpriteArray[8].setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

		this->numberTextureArray[9].loadFromFile("PACMAN assets/nine3.png");
		this->numberSpriteArray[9].setTexture(this->numberTextureArray[9]);
		this->numberSpriteArray[9].setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
	}

	~SCORE() {
		cout << "SCORE destroyed\n";
	}

	void operator+=(int n) {
		this->score += n;
		if (this->score > this->maxScore) {
			this->score = 0;
			this->highScore = this->maxScore;
			for (int i = 0; i < this->arraySize; i++) {
				this->scoreArray[i] = 0;
				this->highScoreArray[i] = 9;
			}
			return;
		}

		this->tempVar = this->score;

		if (this->score > this->highScore) {
			this->highScore = this->score;
			for (int i = this->arraySize - 1; i >= 0; i--) {
				this->scoreArray[i] = this->tempVar % 10;
				this->highScoreArray[i] = this->scoreArray[i];
				this->tempVar /= 10;
			}
			return;
		}

		for (int i = this->arraySize - 1; i >= 0; i--) {
			this->scoreArray[i] = this->tempVar % 10;
			this->tempVar /= 10;
		}
	}

	void print() {
		for (int i = 0; i < this->arraySize; i++) {
			cout << this->scoreArray[i];
		}
		cout << ", ";
		for (int i = 0; i < this->arraySize; i++) {
			cout << this->highScoreArray[i];
		}
		cout << endl;
	}

	void drawScore(sf::RenderWindow& window) {
		this->highScoreSprite.setPosition(9.5 * boxPixelsX, 1);
		window.draw(this->highScoreSprite);

		for (int i = 0, j = 3; i < this->arraySize; i++, j++) {
			this->numberSpriteArray[this->scoreArray[i]].setPosition(j * (boxPixelsX - 1), boxPixelsY);
			window.draw(this->numberSpriteArray[this->scoreArray[i]]);
		}

		for (int i = 0, j = 13; i < this->arraySize; i++, j++) {
			this->numberSpriteArray[this->highScoreArray[i]].setPosition(j * (boxPixelsX - 1), boxPixelsY);
			window.draw(this->numberSpriteArray[this->highScoreArray[i]]);
		}
		//this->livesSprite.setPosition((i * 15), (35 * boxPixelsY)-8);
		//window.draw(livesSprite);
	}

	void updateHighScore() {
		if (this->score < this->highScore)
			return;
		this->highscoreOUT.open("highscore.txt");
		highscoreOUT << this->highScore;
		this->highscoreOUT.close();
	}

	void setScoreZero() {
		this->score = 0;
		this->tempVar = this->score;
		for (int i = 0; i < this->arraySize; i++) {
			this->scoreArray[i] = 0;
		}
	}

	void initializeGhostBonusMultiplier() {
		this->ghostBonusMultiplier = 1;
	}

	void multiplyGhostBonusMultiplier() {
		this->ghostBonusMultiplier *= 2;
	}

	int getGhostBonusMultiplier() {
		return this->ghostBonusMultiplier;
	}

	int getGhostBonus() {
		return this->ghostBonus;
	}

	void drawGhostBonus(sf::RenderWindow& window, int X_ColCoordinate, int Y_RowCoordinate) {
		this->ghostBonusSpriteArray[this->ghostBonusMultiplier].setPosition((X_ColCoordinate * boxPixelsX) - 3, (Y_RowCoordinate * boxPixelsY) - 3);
		window.draw(this->ghostBonusSpriteArray[this->ghostBonusMultiplier]);
	}
};
