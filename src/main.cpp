#include "iostream"
#include "../include/MainGame.h"

int main(int argc, char **argv) {
	std::cout << "simple-cpp-renderer#main()" << std::endl;

	MainGame mainGame;
	mainGame.run();

	return 0;
}
