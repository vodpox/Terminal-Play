// Empty project. Have fun!

#include "Game.h"


class EmptyScene : public tplay::Scene {
	public:
		tplay::Game *game;
		
		EmptyScene(tplay::Game &game) : game(&game) {}
		
		void update() {
			// Called once per frame. Use to get input, move player, etc.
		}
		
		void draw() {
			// Called after update(). Use only for drawing.
		}
};

int main() {
	tplay::Game game;         // Create game object
	EmptyScene scene(game);   // Create scene object
	game.setScene(&scene);    // Set our scene as current running scene
	game.loop();              // Start game loop
	return 0;
}
