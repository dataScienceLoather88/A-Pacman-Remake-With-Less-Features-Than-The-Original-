#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<fstream>
#include"Global Variables.h"

using namespace std;

class pellets {
	sf::Texture smallPelletTexture;
	sf::Sprite smallPelletSprite;

	sf::Texture largePelletTexture;
	sf::Sprite largePelletSprite;

public:
	//small pellet data
	const int smallPelletCount = 245;
	const int smallPelletRowHolder[245] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7
		, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11
		, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 23, 23, 23, 23
		, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26
		, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29
		, 29, 29, 29, 29, 29, 29, 30, 30, 30, 30, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, };
	const int smallPelletColHolder[245] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 1, 6, 12, 15, 21, 26, 1, 6, 12, 15, 21
		, 26, 1, 6, 12, 15, 21, 26, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 1, 6, 9, 18, 21, 26, 1, 6, 9, 18
		, 21, 26, 1, 2, 3, 4, 5, 6, 9, 10, 11, 12, 15, 16, 17, 18, 21, 22, 23, 24, 25, 26, 6, 21, 6, 21, 6, 21, 6, 21, 6, 21, 6, 21, 6, 21, 6, 21, 6, 21, 6, 21, 6
		, 21, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 1, 6, 12, 15, 21, 26, 1, 6, 12, 15, 21, 26, 1, 2, 3, 6, 7, 8, 9
		, 10, 11, 12, 14, 15, 16, 17, 18, 19, 20, 21, 24, 25, 26, 3, 6, 9, 18, 21, 24, 3, 6, 9, 18, 21, 24, 1, 2, 3, 4, 5, 6, 9, 10, 11, 12, 15, 16, 17, 18, 21
		, 22, 23, 24, 25, 26, 1, 12, 15, 26, 1, 12, 15, 26, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, };

	//large pellet data
	const int largePelletCount = 4;
	const int largePelletRowHolder[4] = { 5,5,30,30 };
	const int largePelletColHolder[4] = { 1,26,1,26 };

	void drawPellet1(sf::RenderWindow& window, const int& rowNumber, const int& columnNumber) {
		this->smallPelletSprite.setPosition(columnNumber * boxPixelsX, rowNumber * boxPixelsY);
		window.draw(this->smallPelletSprite);
	}

	void drawPellet2(sf::RenderWindow& window, const int& rowNumber, const int& columnNumber) {
		this->largePelletSprite.setPosition(columnNumber * boxPixelsX, rowNumber * boxPixelsY);
		window.draw(this->largePelletSprite);
	}

	pellets() {
		this->smallPelletTexture.loadFromFile("PACMAN assets/pellet1.png");
		this->smallPelletSprite.setTexture(this->smallPelletTexture);
		this->smallPelletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

		this->largePelletTexture.loadFromFile("PACMAN assets/pellet2.png");
		this->largePelletSprite.setTexture(this->largePelletTexture);
		this->largePelletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
	}

	~pellets(){
		cout << "pellets destroyed\n";
	}

};
