/*
	Simple demo that should use most used features in a pretty basic form.
*/

#include "Game.h"
#include "Input.h"
#include "Graphics.h"
#include "Camera.h"


class ExampleScene : public tplay::Scene {
	public:
		tplay::Game *game;
		tplay::Camera camera;
		ExampleScene(tplay::Game &game) : game(&game) {}
		
		// Player's coordinates
		int x = 5;
		int y = 5;
		
		void update() {
			// Get input. Arrow keys to move up and down, q quits game.
			if (game->input.isButtonDown(tplay::Keyboard::UP_ARROW)) {
				y++;
			}
			else if (game->input.isButtonDown(tplay::Keyboard::DOWN_ARROW)) {
				y--;
			}
			else if (game->input.isButtonDown(tplay::Keyboard::LEFT_ARROW)) {
				x--;
			}
			else if (game->input.isButtonDown(tplay::Keyboard::RIGHT_ARROW)) {
				x++;
			}
			else if (game->input.isButtonDown(tplay::Keyboard::Q)) {
				game->quit();
			}
		}
		
		void draw() {
			game->graphics.setCamera(&camera);
			// Centre camera on player
			camera.setCoordinates(x - (game->graphics.getTerminalSizeX() / 2), y - (game->graphics.getTerminalSizeY() / 2));
			
			// Draw axis from (0, 0)
			// X axis
			game->graphics.setFormat(tplay::Format::FOREGROUND_BLUE);
			for (int i = -39; i < 40; i++) {
				if (i < 0) game->graphics.setFormat(tplay::Format::NEGATIVE);
				game->graphics.addToWorld(i, 0, "-");
				if (i < 0) game->graphics.unsetFormat(tplay::Format::NEGATIVE);
			}
			game->graphics.setFormat(tplay::Format::BOLD);
			game->graphics.addToWorld(40, 0, ">");
			game->graphics.resetFormat();
			
			// Y axis
			game->graphics.setFormat(tplay::Format::FOREGROUND_RED);
			for (int i = -19; i < 20; i++) {
				if (i < 0) game->graphics.setFormat(tplay::Format::NEGATIVE);
				game->graphics.addToWorld(0, i, "|");
				if (i < 0) game->graphics.unsetFormat(tplay::Format::NEGATIVE);
			}
			game->graphics.setFormat(tplay::Format::BOLD);
			game->graphics.addToWorld(0, 20, "^");
			game->graphics.resetFormat();
			
			// Middle point
			game->graphics.setFormat(tplay::Format::BACKGROUND_GREEN);
			game->graphics.addToWorld(0, 0, " ");
			game->graphics.resetFormat();
			
			// Player
			game->graphics.addToWorld(x, y, "@");
			
			// UI
			game->graphics.setFormat(tplay::Format::NEGATIVE);
			game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 6, 0, "Health: 100%");
		}
};

int main() {
	tplay::Game game;
	ExampleScene scene(game);
	game.setScene(&scene);
	game.loop();
	return 0;
}
