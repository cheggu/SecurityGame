#pragma once
#include "SFML/Graphics.hpp"

namespace Font {
	sf::Font arial;
	sf::Font emulogic;
	
	void bootstrap() {
		if (!arial.loadFromFile("Content/Fonts/arial.ttf")) {
			std::cout << "missing font: arial.ttf" << std::endl;
		}
		if (!emulogic.loadFromFile("Content/Fonts/emulogic.ttf")) {
			std::cout << "missing font: emulogic.ttf" << std::endl;
		}
	}
}