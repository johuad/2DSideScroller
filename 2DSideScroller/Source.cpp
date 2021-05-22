#include "Game.h"
#include "GameStateMenu.h"
#include <memory>

int main()
{
	//TODO: Implement settings & saving/loading settings from file.
	//TODO: I still want to do this.

	//set up initial game screen.
	Game *game = new Game(1280, 700);

	game->PushState(new GameStateMenu(game));
	game->GameLoop();

	return 0;
}