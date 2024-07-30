#include "MainGame.h"

long getTimestamp() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

MainGame::MainGame() {
	_window = nullptr;
	_screenWidth = 1024;
	_screenHeight = 768;
	_running = true;
	fps = 0;
	vSync = true;
	quadColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	x = -0.25;
}

MainGame::~MainGame() {

}

void MainGame::run() {
	initSystems();

	quad.init(x, -0.25, 0.5, 0.5);

	int frames = 0;
	long start = getTimestamp();

	while (_running) {
		pollEvents();
		drawGame();

		frames++;
		long now = getTimestamp();
		long delta = now - start;
		if (delta >= 1000) {
			start = now;
			fps = frames;
			frames = 0;
		}
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
	// vSync
	SDL_GL_SetSwapInterval(1);
	glClearColor(0, 0, 0, 1.0);

	// Setup Dear ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(_window, glContext);
	ImGui_ImplOpenGL3_Init("#version 100");
}

void MainGame::pollEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		ImGui_ImplSDL2_ProcessEvent(&event);
		switch (event.type) {
			case SDL_QUIT:
				_running = false;
				break;
		}
	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Debug");
	ImGui::Text("FPS: %d", fps);

	if (ImGui::Button("Enable V-Sync")) {
		SDL_GL_SetSwapInterval(1);
	}
	if (ImGui::Button("Disable V-Sync")) {
		SDL_GL_SetSwapInterval(0);
	}

	ImGui::ColorEdit3("Quad color", (float*)&quadColor);

	ImGui::SliderFloat("Quad x", &x, -4.0f, 4.0f);
	quad.setX(x);

	ImGui::End();
}

void MainGame::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(quadColor.x * quadColor.w, quadColor.y * quadColor.w, quadColor.z * quadColor.w);

	quad.draw();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_GL_SwapWindow(_window);
}

