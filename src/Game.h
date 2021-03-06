#ifndef GAME_H
#define GAME_H

#include "Scene.h"
#include "Graphics.h"
#include "Input.h"

namespace tplay {
	
	class Game {
		
		private:
			Scene *currentScene = NULL;
			bool quitGame = false;
		
		public:
			Graphics graphics;
			Input input;
			
			void setScene(Scene *newScene);
			void loop();
			void quit();
		
	};
	
}

#endif