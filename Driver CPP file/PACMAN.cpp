#include"Global Variables.h"
#include"SCORE.h"
#include"PACMAN.h"
#include"GHOST.h"
#include"RED.h"
#include"PINK.h"
#include"BLUE.h"
#include"ORANGE.h"
#include"menu.h"
#include"background.h"
#include"pellets.h"
#include"gameGrid.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<fstream>

using namespace std;

int main() {
	srand(time(0));

	// Declaring RenderWindow.
	sf::RenderWindow window(sf::VideoMode(resolutionX, resolutionY), "PACMAN", sf::Style::Close | sf::Style::Titlebar);

	// Used to resize your window if it's too big or too small. Use according to your needs.
	window.setSize(sf::Vector2u(252 * 2, 324 * 2)); // Recommended for 1366x768 (768p) displays

	// Used to position your window on every launch. Use according to your needs.
	window.setPosition(sf::Vector2i(650, 150));

	// Initializing Background and game grid/menu
	menu titleScreen;
	background Background;
	gameGrid pacmanGrid;

	titleScreen.loadMenu(window);

	//music
	sf::Music BGM;
	BGM.openFromFile("PACMAN assets/Daedalus.ogg");
	BGM.setLoop(true);


	pacmanGrid.ready(window, Background);
	BGM.play();

	Background.drawBackground(window);
	pacmanGrid.drawGhostsOnGridThroughGameGrid(window);
	pacmanGrid.drawPacmanOnGrid(window);
	window.display();
	window.clear();

	while (true) {
		if (pacmanGrid.getFullInitializationCondition()) {
			pacmanGrid.initializeGameGrid();
			pacmanGrid.levelUpdate();
			pacmanGrid.InitializeGhostVariablesThroughGameGrid();
			pacmanGrid.setFullInitializationFalse();

			pacmanGrid.ready(window, Background);

			Background.drawBackground(window);
			pacmanGrid.drawPelletsOnGrid(window);
			pacmanGrid.drawLives(window);
			pacmanGrid.difficultyIndicator(window);
			pacmanGrid.drawGhostsOnGridThroughGameGrid(window);
			pacmanGrid.drawPacmanOnGrid(window);
			window.display();
			window.clear();
		}

		else if (pacmanGrid.getPartialInitializationCondition()) {
			pacmanGrid.PartiallyInitializeGameGrid();
			pacmanGrid.levelUpdate();
			pacmanGrid.InitializeGhostVariablesThroughGameGrid();
			pacmanGrid.setPartialReinitializationFalse();

			pacmanGrid.ready(window, Background);

			Background.drawBackground(window);
			pacmanGrid.drawPelletsOnGrid(window);
			pacmanGrid.drawLives(window);
			pacmanGrid.difficultyIndicator(window);
			pacmanGrid.drawGhostsOnGridThroughGameGrid(window);
			pacmanGrid.drawPacmanOnGrid(window);
			window.display();
			window.clear();
		}

		while (window.isOpen()) {

			Background.drawBackground(window);
			pacmanGrid.drawPelletsOnGrid(window);
			pacmanGrid.drawLives(window);
			pacmanGrid.difficultyIndicator(window);
			//pacmanGrid.drawPacmanOnGrid(window);

			//level select
			pacmanGrid.levelUpdate();

			//ghosts
			pacmanGrid.ghostModeSelection();
			pacmanGrid.assignGhostTargetTiles();

			pacmanGrid.moveGhostsOnGridThroughGameGrid();
			pacmanGrid.executeCollisionOutcome(pacmanGrid.detectCollisionsInMain(), window);
			if (pacmanGrid.getFullInitializationCondition() || pacmanGrid.getPartialInitializationCondition()) {
				break;
			}
			pacmanGrid.movePacmanOnGrid();
			pacmanGrid.executeCollisionOutcome(pacmanGrid.detectCollisionsInMain(), window);
			if (pacmanGrid.getFullInitializationCondition() || pacmanGrid.getPartialInitializationCondition()) {
				break;
			}
			//pacmanGrid.outputArray();

			pacmanGrid.drawGhostsOnGridThroughGameGrid(window);
			pacmanGrid.drawPacmanOnGrid(window);

			pacmanGrid.drawScoreOnGrid(window);

			sf::Event e;
			while (window.pollEvent(e)) {
				if (e.type == sf::Event::Closed) {
					return 0;
				}
			}
			window.display();
			window.clear();

			if (pacmanGrid.areThePelletsGone_QuestionMark()) {
				Background.PlayLevelCompleteAnimation(window, pacmanGrid.getPacmanCol(), pacmanGrid.getPacmanRow());
				pacmanGrid.setFullInitializationTrue();
				pacmanGrid.setReplenishLivesFalse();
				pacmanGrid.incrementLevel();
				break;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				return 0;
		}
	}
	return 0;
}
