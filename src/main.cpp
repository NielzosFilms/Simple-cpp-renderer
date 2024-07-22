#include "GL/gl.h"
#include "SDL2/SDL.h"
#include "iostream"

int main(int argc, char** argv) {
    std::cout << "simple-cpp-renderer#main()\n";

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* _window = SDL_CreateWindow("Simple c++ renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_OPENGL);

    std::cout << "Enter any key to quit...\n";
    int a;
    std::cin >> a;

    return 0;
}