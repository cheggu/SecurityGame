#pragma once
float WIDTH = 1920;
float HEIGHT = 1080;
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!"); //, sf::Style::Fullscreen
bool EndCondition = false;
sf::View view;
sf::View uiView;

int playerid;
int boss01id;
int boss02id;

bool signalPlayerHit = false;

#include "Cheats.h"