#include "Game.h"
#include <eng.h>

int main() {
	//create game instance
	Game* game = new Game();

	//create engine instance
	eng::Engine engine;

	//pass the game instance to the engine
	engine.SetApplication(game);

	//initialize engine and game
	//if initialization is successful, enter the main loop
	if (engine.Init()) {

		engine.Run();
	}

	//after exiting the loop, free up resources
	engine.Destroy();
	return 0;
}