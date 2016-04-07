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
	  }
		
		void draw(){
			// Axis from origin point
			for(int i = -39; i < 40; i++){
				game->graphics.addToScreen(i, 0, "-");
			}
			game->graphics.addToScreen(40, 0, ">");
			for(int i = -19; i < 20; i++){
				game->graphics.addToScreen(0, i, "|");
			}
			game->graphics.addToScreen(0, 20, "^");
			game->graphics.addToScreen(0, 0, "+");
			
			// "Player"
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
