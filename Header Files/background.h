#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<fstream>
#include "PACMAN.h"
#include"Global Variables.h"

using namespace std;

class background {
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Texture backgroundTexture2;
	sf::Sprite backgroundSprite2;

	sf::Texture pacmanLevelCompleteTexture;
	sf::Sprite pacmanLevelCompleteSprite;

	sf::Clock transitionWaitForLevelCompleteAnimation;
	sf::Clock transitionWaitForLevelCompleteAnimation2;
	const int transitionWaitLimit = 200;
	const int transitionWaitLimit2 = 1000;

public:
	background() {
		backgroundTexture.loadFromFile("PACMAN assets/background.png");
		backgroundSprite.setTexture(backgroundTexture);
		backgroundSprite.setColor(sf::Color(255, 255, 255, 255 * 1.0));

		backgroundTexture2.loadFromFile("PACMAN assets/background2.png");
		backgroundSprite2.setTexture(backgroundTexture2);
		backgroundSprite2.setColor(sf::Color(255, 255, 255, 255 * 1.0));

		pacmanLevelCompleteTexture.loadFromFile("PACMAN assets/pacman level complete.png");
		pacmanLevelCompleteSprite.setTexture(pacmanLevelCompleteTexture);
		pacmanLevelCompleteSprite.setTextureRect(sf::IntRect(0, 0, largeSpriteDimensionX, largeSpriteDimensionY));
	}

	~background() {
		cout << "background destroyed\n";
	}

	void drawBackground(sf::RenderWindow& window) {
		window.draw(this->backgroundSprite);
	}

	void drawBackground2(sf::RenderWindow& window) {
		window.draw(this->backgroundSprite2);
	}

	void drawPacmanLevelComplete(sf::RenderWindow& window, int& pacmanX, int& pacmanY) {
		this->pacmanLevelCompleteSprite.setPosition((pacmanX * boxPixelsX) - 3, (pacmanY * boxPixelsY) - 3);
		window.draw(this->pacmanLevelCompleteSprite);
	}

	//waits between background changes
	void clockWait() {
		while (true) {
			if (this->transitionWaitForLevelCompleteAnimation.getElapsedTime().asMilliseconds() > this->transitionWaitLimit) {
				this->transitionWaitForLevelCompleteAnimation.restart();
				return;
			}
		}
	}

	void clockWait2() {
		this->transitionWaitForLevelCompleteAnimation2.restart();
		while (true) {
			if (this->transitionWaitForLevelCompleteAnimation2.getElapsedTime().asMilliseconds() > this->transitionWaitLimit2) {
				//this->transitionWaitForLevelCompleteAnimation2.restart();
				return;
			}
		}
	}

	void PlayLevelCompleteAnimation(sf::RenderWindow& window, int pacmanX, int pacmanY) {
		this->drawBackground(window);
		this->drawPacmanLevelComplete(window, pacmanX, pacmanY);
		window.display();
		this->clockWait2();
		window.clear();
		for (int i = 1; i <= 10; i++) {
			switch (i % 2) {
			case 0:
				this->drawBackground(window);
				this->drawPacmanLevelComplete(window, pacmanX, pacmanY);
				window.display();
				this->clockWait();
				window.clear();
				break;
			default:
				this->drawBackground2(window);
				this->drawPacmanLevelComplete(window, pacmanX, pacmanY);
				window.display();
				this->clockWait();
				window.clear();
				break;
			}
		}
	}
};
