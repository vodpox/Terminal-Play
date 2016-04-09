// Completely empty project. Have fun!

#include "Game.h"


class TScene : public Scene {
	public:
	  Game *game;
	  TScene(Game &game) : game(&game) {}
	  void update(){
			// Called once per frame. Use to get input, move player, etc.
	  }
		
		void draw(){
			// Called after update(). Use only for drawing.
	  }
};

int main(){
  Game game;                // Create game object
  TScene scene(game);       // Create scene
  game.setScene(&scene);    // Set our scene as current running scene
  game.loop();              // Start game loop
	return 0;
}
