
#include "../GameEngine/core/Application.h"
#include "game-states/MainScene.h"

int main()
{
	Application app;
	app.addGameState(new MainScene());
	app.runMainLoop();

	return 0;
}