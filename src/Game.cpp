#include "Game.h"
#include <unistd.h>


namespace tplay {
	
	void Game::setScene(Scene *newScene) {
		if (currentScene != NULL) currentScene->onExit();
		currentScene = newScene;
		currentScene->onEnter();
	}

	void Game::loop() {
		while (!quitGame) {
			graphics.updateSize();
			input.getInput();
			currentScene->update();
			currentScene->draw(); // scene tells what to draw
			graphics.draw(); // actuall drawing
			usleep(0); // without this not all input is accepted
		}
	}

	void Game::quit() {
		quitGame = true;
	}
	
}