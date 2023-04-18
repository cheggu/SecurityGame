#pragma once
#include "SFML/Graphics.hpp"

namespace Font {
	sf::Font arial;
	
	void bootstrap() {
		if (!arial.loadFromFile("Content/Fonts/arial.ttf")) {
			
		}
	}
}