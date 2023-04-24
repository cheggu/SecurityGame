#pragma once
float WIDTH = 1920;
float HEIGHT = 1080;
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SecurityGame", sf::Style::Fullscreen); //, sf::Style::Fullscreen
bool EndCondition = false;
sf::View view;
sf::View uiView;

int playerid;
int boss01id;
int boss02id;
int boss03id;

bool spawnFinalBoss = false;
bool finalBossBruteHit = false;
bool drawCredits = false;
bool drawInfo = false;

bool signalPlayerHit = false;

#include "Cheats.h"