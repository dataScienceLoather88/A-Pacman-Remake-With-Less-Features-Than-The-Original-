#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<fstream>
#include "PACMAN.h"
#include"Global Variables.h"

using namespace std;

class menu {
	sf::Music menuBGM;
	sf::Texture menuTexture;
	sf::Sprite menuSprite;
public:
	menu() {
		this->menuBGM.openFromFile("PACMAN assets/Micom.ogg");
		this->menuBGM.setLoop(true);

		menuTexture.loadFromFile("PACMAN assets/menu.png");
		menuSprite.setTexture(menuTexture);
		menuSprite.setColor(sf::Color(255, 255, 255, 255 * 1.0));
	}

	~menu() {
		cout << "menu destroyed\n";
	}

	void loadMenu(sf::RenderWindow& window) {
		this->menuBGM.play();
		window.draw(this->menuSprite);
		window.display();
		while (true) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				break;
		}
		this->menuBGM.stop();
		window.clear();
	}

};