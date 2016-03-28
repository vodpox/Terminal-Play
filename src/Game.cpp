#include "Game.h"


void Game::setScene(Scene *newScene){
	currentScene = newScene;
}

void Game::loop(){
	while(!quitGame){
		//TODO: input (already non blocking so that should be easy)
		graphics.updateSize();
		currentScene->update();
	}
}

void Game::quit(){
	quitGame = true;
}