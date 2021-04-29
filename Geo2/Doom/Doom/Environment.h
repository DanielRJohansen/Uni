#pragma once

#include <iostream>
#include <SFML\system.hpp>

#include "Types.h"
#include "Display.h"
#include "BSP.h"

class Environment
{
public:
	Environment(Wall* walls, int n_walls): n_walls(n_walls) {
		this->walls = walls;
		display = Display(Double2(1920, 1080), walls, n_walls, &player);
		bsp = BSP(walls, n_walls);
	}

	void run();


private:
	Display display;
	Player player;
	BSP bsp;
	Wall* walls;
	int n_walls;

	double dt = 5;
	int fps_limit = 60;
	bool pause = 0;


	void runningAverageFPS(sf::Time frame_time);
	const int nums = 20;
	int framesum = 0;
	int cnt = 0;

	bool movement[4];	// wasd
	double angles[4] = { 0, PI / 2, PI, -PI / 2 };

	void drawAll(int n_walls);
	void handleMovement();
	void handleRotation();
	void handleKeypress(sf::Event* event);
	void handleKeyrelease(sf::Event* event);
};

