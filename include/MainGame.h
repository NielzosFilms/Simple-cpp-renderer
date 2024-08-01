#pragma once

#include "SDL2/SDL.h"
#include "iostream"
#include "chrono"
#include "string"
#include "vector"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#define GL_GLEXT_PROTOTYPES
#include "GL/gl.h"
#include "GL/glext.h"

#include "Quad.h"
#include "Settings.h"

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
	int fps;

	Quad quad;

	void initSystems();

	void pollEvents();
	void drawGame();

};
