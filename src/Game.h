#ifndef GAME_H
#define GAME_H

#include "Graphics.h"
#include "Scene.h"

class Game{
	
	private:
		Scene *currentScene;
		bool quitGame = false;
	
	public:
		Graphics graphics;
		//Input input;
		
		void setScene(Scene *newScene);
		void loop();
		void quit();
	
};

#endif