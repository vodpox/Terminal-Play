/*
	Simple demo that should use most Engine's features in a pretty basic form.
*/


#include "Game.h"
#include "Input.h"
#include "Graphics.h"

class TScene : public Scene {
	public:
	  Game *game;
	  TScene(Game &game) : game(&game) {}
		
		// Our player's coordinates
		int x = 5;
		int y = 5;
		
	  void update(){
			// Get input. Arrow keys to move up and down, q quits game.
	    if(game->input.isButtonDown(Keyboard::UP_ARROW)){
				y++;
			}
			else if(game->input.isButtonDown(Keyboard::DOWN_ARROW)){
				y--;
			}
			else if(game->input.isButtonDown(Keyboard::LEFT_ARROW)){
				x--;
			}
			else if(game->input.isButtonDown(Keyboard::RIGHT_ARROW)){
				x++;
			}
			else if(game->input.isButtonDown(Keyboard::Q)){
				game->quit();
			}
	  }
		
		void draw(){
			// Centre camera on player
			game->graphics.setCameraCoordinates(x - (game->graphics.getTerminalSizeX() / 2), y - (game->graphics.getTerminalSizeY() / 2));
			
			//   Draw axis from origin point (0, 0) using fancy graphics
			
			// X axis
			game->graphics.setFormat(Format::FOREGROUND_BLUE);
			for(int i = -39; i < 40; i++){
				if(i < 0) game->graphics.setFormat(Format::NEGATIVE);
				game->graphics.addToScreen(i, 0, "-");
				if(i < 0) game->graphics.unsetFormat(Format::NEGATIVE);
			}
			game->graphics.setFormat(Format::BOLD);
			game->graphics.addToScreen(40, 0, ">");
			game->graphics.resetFormat();
			
			// Y axis
			game->graphics.setFormat(Format::FOREGROUND_RED);
			for(int i = -19; i < 20; i++){
				if(i < 0) game->graphics.setFormat(Format::NEGATIVE);
				game->graphics.addToScreen(0, i, "|");
				if(i < 0) game->graphics.unsetFormat(Format::NEGATIVE);
			}
			game->graphics.setFormat(Format::BOLD);
			game->graphics.addToScreen(0, 20, "^");
			game->graphics.resetFormat();
			
			// Middle
			game->graphics.setFormat(Format::BACKGROUND_GREEN);
			game->graphics.addToScreen(0, 0, " ");
			game->graphics.resetFormat();
			
			// Player
			game->graphics.addToScreen(x, y, "@");
	  }
};

int main(){
  Game game;
  TScene scene(game);
  game.setScene(&scene);
  game.loop();
	return 0;
}
