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

#include "Errors.h"

#include "Quad.h"
#include "Settings.h"
#include "GLSLProgram.h"

class MainGame {
public:
	MainGame();
	~MainGame();

	void run();
private:
	SDL_Window* window;
	int screenWidth;
	int screenHeight;
	bool running;
	int fps;
	float time;

	Quad quad;
	GLSLProgram colorProgram;

	void initSystems();
	void initImGui(SDL_GLContext& glContext);
	void initShaders();

	void pollEvents();
	void drawGame();

};
