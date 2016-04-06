#include <iostream>
#include "Game.h"
#include "Input.h"

class TScene : public Scene {
	public:
		bool doDraw = true;
		int x = 5;
		int y = 5;
	  Game *game;
	  TScene(Game &game) : game(&game) {}
	  void update(){
	    if(game->input.isButtonDown(Keyboard::UP_ARROW)){
				y--;
				doDraw = true;
			}
			else if(game->input.isButtonDown(Keyboard::DOWN_ARROW)){
				y++;
				doDraw = true;
			}
			else if(game->input.isButtonDown(Keyboard::LEFT_ARROW)){
				x--;
				doDraw = true;
			}
			else if(game->input.isButtonDown(Keyboard::RIGHT_ARROW)){
				x++;
				doDraw = true;
			}
	  }
		
		void draw(){
	    if(doDraw){
				game->graphics.addToScreen(x, y, "Hello, world!");
				game->graphics.draw();
				doDraw = false;
			}
	  }
};

int main(){
  Game game;
  TScene scene(game);
  game.setScene(&scene);
  game.loop();
	return 0;
}
