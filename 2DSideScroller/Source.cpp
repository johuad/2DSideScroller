#include "Game.h"
#include "GameStateMenu.h"

int main()
{
	//TODO: change raw pointers to smart pointers.
	//TODO: figure out a better way to set up the menu UI.

	//Start the game.
	//Game game = Game(1280, 700);

	std::shared_ptr<Game> game;

	game = std::shared_ptr<Game>(new Game(1280, 700));

	game->ChangeState(std::shared_ptr<GameStateMenu>(new GameStateMenu(game)));
	game->GameLoop();

	return 0;
}