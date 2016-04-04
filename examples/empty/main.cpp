#include <iostream>
#include "Game.h"
#include "Input.h"

class TScene : public Scene {
public:
  Game *game;
  TScene(Game game) : game(&game) {}
  void update(){
    if(game->input.getButton(game->input.KeyCode::a)) printf("\033[2;31mHello World\033[0m\n");
  }
};

int main(){
  Game game;
  TScene scene(game);
  game.setScene(&scene);
  game.loop();
	return 0;
}
