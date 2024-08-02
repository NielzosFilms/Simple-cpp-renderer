#include "MainGame.h"

long getTimestamp() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

MainGame::MainGame() :
	window(nullptr),
		screenWidth(1024),
		screenHeight(768),
		running(true),
		fps(0),
		time(0.0) {
}

MainGame::~MainGame() {

}

void MainGame::run() {
	initSystems();
	Settings &settings = Settings::getInstance();

	quad.init(-1, -1, 2, 2);

	int frames = 0;
	long start = getTimestamp();

	while (running) {
		pollEvents();
		time += settings.timeAdd;
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

	window = SDL_CreateWindow("Simple c++ renderer",
	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight,
		SDL_WINDOW_OPENGL);

	if (window == nullptr) {
		fatalError("Failed to create window");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
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

void MainGame::initImGui(SDL_GLContext &glContext) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void) io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(window, glContext);
	ImGui_ImplOpenGL3_Init("#version 400");
}

void MainGame::initShaders() {
	colorProgram.compile("shaders/colorShading.vert", "shaders/colorShading.frag");
	colorProgram.addAttribute("vertexPosition");
	colorProgram.addAttribute("vertexColor");
	colorProgram.link();
}

void MainGame::pollEvents() {
	Settings &settings = Settings::getInstance();

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		ImGui_ImplSDL2_ProcessEvent(&event);
		switch (event.type) {
			case SDL_QUIT:
				running = false;
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

		if (ImGui::Button("Reset time")) {
			time = 0;
		}
		ImGui::SameLine();
		if (ImGui::Button("Reset time addition p.frame")) {
			settings.timeAdd = 0.01;
		}
		ImGui::SliderFloat("Time addition p.frame", &settings.timeAdd, 0.0f, 0.5f);

		static const char* fragmentShaders[] = { "Passthrough color", "Expanding walls", "Simple moving waves", "Rainbow swirl", "Rainbow wave" };
		if (ImGui::Combo("Active fragment shader", &settings.currentFragmentShader, fragmentShaders, 5)) {
			time = 0;
		}

		ImGui::End();
	}
}

void MainGame::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Settings &settings = Settings::getInstance();

	colorProgram.use();
	GLuint timeLocation = colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, time);
	GLuint fragmentShaderLocation = colorProgram.getUniformLocation("fragmentShader");
	glUniform1i(fragmentShaderLocation, settings.currentFragmentShader);
	quad.draw();
	colorProgram.unuse();

	if (settings.debug) {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	SDL_GL_SwapWindow(window);
}

