#include "MainGame.h"

MainGame::MainGame() {
	_window = nullptr;
	_screenWidth = 1024;
	_screenHeight = 768;
	_running = true;
}

MainGame::~MainGame() {

}

void MainGame::run() {
	initSystems();

	while (_running) {
		pollEvents();
		drawGame();
	}
}

void MainGame::initSystems() {
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Simple c++ renderer",
	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight,
		SDL_WINDOW_OPENGL);

	if (_window == nullptr) {
		std::cout << "Failed to create window" << std::endl;
		SDL_Quit();
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		std::cout << "Failed to create SDL_GL context" << std::endl;
		SDL_Quit();
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0, 0, 0, 1.0);
}

void MainGame::pollEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				_running = false;
				break;
		}
	}
}

void MainGame::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_COLOR_ARRAY);
	glBegin(GL_TRIANGLES);

	glColor3f(1, 0, 1);
	glVertex2f(0, 0.25);
	glVertex2f(0.25, -0.25);
	glVertex2f(-0.25, -0.25);

	glEnd();

	SDL_GL_SwapWindow(_window);
}

