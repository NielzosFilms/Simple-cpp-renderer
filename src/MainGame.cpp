#include "MainGame.h"

long getTimestamp() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()).count();
}

MainGame::MainGame() {
	_window = nullptr;
	_screenWidth = 1024;
	_screenHeight = 768;
	_running = true;
	fps = 0;
}

MainGame::~MainGame() {

}

void MainGame::run() {
	initSystems();

	quad.init(-1, -1, 2, 2);

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
		fatalError("Failed to create window");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		fatalError("Failed to create SDL_GL context");
	}

	std::cout << glGetString(GL_VERSION);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// vSync
	SDL_GL_SetSwapInterval(1);
	glClearColor(0, 0, 0, 1.0);

	initImGui(glContext);
	initShaders();
}

void MainGame::initImGui(SDL_GLContext& glContext) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void) io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(_window, glContext);
	ImGui_ImplOpenGL3_Init("#version 400");
}

void MainGame::initShaders() {
	colorProgram.compile("shaders/colorShading.vert", "shaders/colorShading.frag");
	colorProgram.addAttribute("vertexPosition");
	colorProgram.addAttribute("vertexColor");
	colorProgram.link();
}

void MainGame::pollEvents() {
	Settings& settings = Settings::getInstance();

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		ImGui_ImplSDL2_ProcessEvent(&event);
		switch (event.type) {
			case SDL_QUIT:
				_running = false;
				break;
			case SDL_KEYUP:
				if (event.key.keysym.scancode == SDL_SCANCODE_F4) {
					settings.debug = !settings.debug;
				}
				break;
		}
	}

	if (settings.debug) {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Debug");
		ImGui::Text("FPS: %d", fps);

		if (ImGui::Checkbox("Enable V-Sync", &settings.vSync)) {
			if (settings.vSync) {
				SDL_GL_SetSwapInterval(1);
			} else {
				SDL_GL_SetSwapInterval(0);
			}
		}

		ImGui::ColorEdit3("Quad color", (float*) &settings.quadColor);

		ImGui::End();
	}
}

void MainGame::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Settings& settings = Settings::getInstance();

	glColor3f(settings.quadColor.x * settings.quadColor.w,
		settings.quadColor.y * settings.quadColor.w,
		settings.quadColor.z * settings.quadColor.w);

	colorProgram.use();
	quad.draw();
	colorProgram.unuse();

	if (settings.debug) {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	SDL_GL_SwapWindow(_window);
}

