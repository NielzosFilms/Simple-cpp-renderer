#ifndef MAINGAME_H_
#define MAINGAME_H_
#pragma once

#include "SDL2/SDL.h"
#include "iostream"
#include "chrono"

#define GL_GLEXT_PROTOTYPES
#include "GL/gl.h"
#include "GL/glext.h"

#include "Quad.h"

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

	Quad quad;

	void initSystems();

	void pollEvents();
	void drawGame();

};

#endif
