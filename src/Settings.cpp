#include "Settings.h"

Settings& Settings::getInstance() {
	static Settings settings;
	return settings;
}

Settings::Settings() :
	debug(false),
		vSync(true),
		timeAdd(0.01),
		currentFragmentShader(0) {
}

Settings::~Settings() {

}

