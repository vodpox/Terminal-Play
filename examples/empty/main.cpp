#include <iostream>
#include "Game.h"
#include "Input.h"

class TScene : public Scene {
	public:
		bool doDraw = true;
		int x = 5;
		int y = 5;
	  Game *game;
	  TScene(Game game) : game(&game) {}
	  void update(){
	    if(game->input.getButton(Keyboard::W)){
				y--;
				doDraw = true;
			}
			else if(game->input.getButton(Keyboard::S)){
				y++;
				doDraw = true;
			}
			else if(game->input.getButton(Keyboard::A)){
				x--;
				doDraw = true;
			}
			else if(game->input.getButton(Keyboard::D)){
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
