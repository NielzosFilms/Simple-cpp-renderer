#include "Settings.h"

Settings& Settings::getInstance() {
	static Settings settings;
	return settings;
}

Settings::Settings() {
	debug = false;
	vSync = true;
	quadColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

Settings::~Settings() {

}

