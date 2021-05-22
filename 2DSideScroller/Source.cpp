#include "Game.h"
#include "GameStateMenu.h"

int main()
{
	//TODO: Implement settings & saving/loading settings from file.

	//set up initial game screen.
	Game *game = new Game(1280, 700);

	game->PushState(new GameStateMenu(game));
	game->GameLoop();

	return 0;
}