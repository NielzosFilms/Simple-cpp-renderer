#ifndef MAINGAME_H_
#define MAINGAME_H_
#pragma once

#include "SDL2/SDL.h"
#include "GL/gl.h"
#include "iostream"

class MainGame {
public:
	MainGame();
	~MainGame();

	void run();
private:
	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	bool _running;

	void initSystems();

	void pollEvents();
	void drawGame();

};

#endif
