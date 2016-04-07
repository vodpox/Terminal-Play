#include <iostream>
#include "Game.h"
#include "Input.h"

class TScene : public Scene {
	public:
		int x = 5;
		int y = 5;
	  Game *game;
	  TScene(Game &game) : game(&game) {}
	  void update(){
	    if(game->input.isButtonDown(Keyboard::UP_ARROW)){
				y--;
			}
			else if(game->input.isButtonDown(Keyboard::DOWN_ARROW)){
				y++;
			}
			else if(game->input.isButtonDown(Keyboard::LEFT_ARROW)){
				x--;
			}
			else if(game->input.isButtonDown(Keyboard::RIGHT_ARROW)){
				x++;
			}
	  }
		
		void draw(){
			game->graphics.addToScreen(x, y, "Hello, world!");
	  }
};

int main(){
  Game game;
  TScene scene(game);
  game.setScene(&scene);
  game.loop();
	return 0;
}
