#include "Game.h"
#include <unistd.h>


void Game::setScene(Scene *newScene){
	currentScene = newScene;
}

void Game::loop(){
	while(!quitGame){
		graphics.updateSize();
		input.getInput();
		currentScene->update();
		currentScene->draw(); // scene tells what to draw
		graphics.draw(); // actuall drawing
		usleep(0); // without this not all input is accepted
	}
}

void Game::quit(){
	quitGame = true;
}