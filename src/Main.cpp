#include "Game.h"

int main(int argc, char** argv)
{
	SDL_SetMainReady();
	Game game;
	bool success = game.Initialize();
	if (success)
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}
