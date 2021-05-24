#include "Game.h"
#include "GameStateMenu.h"
#include <memory>

int main()
{
	//Start the game.
	std::shared_ptr<Game> game;

	game = std::shared_ptr<Game>(new Game(1280, 700));

	game->ChangeState(std::shared_ptr<GameStateMenu>(new GameStateMenu(game)));
	game->GameLoop();

	return 0;
}