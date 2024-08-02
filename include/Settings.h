#pragma once

#include "imgui.h"

class Settings {
public:
	// Delete the copy constructor and the assignment operator
	Settings(const Settings&) = delete;
	Settings& operator = (const Settings&) = delete;

	static Settings& getInstance();

	bool debug;
	bool vSync;

	float timeAdd;

	int currentFragmentShader;

private:
	Settings();
	~Settings();
};
