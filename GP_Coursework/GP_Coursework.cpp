#include <iostream>
#include "Game.h"


/*
method that is being executed on game start up.
creates an instance of Game class and executes its run method
*/
int main(int argc, char** argv) //argument used to call SDL main
{
	Game mainGame;
	mainGame.run();

	return 0;
}