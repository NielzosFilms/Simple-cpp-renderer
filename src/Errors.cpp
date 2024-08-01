#include "Errors.h"

void fatalError(std::string msg) {
	std::cout << msg << std::endl;
	std::cout << "Enter any key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
}
