#pragma once

#include <SFML\graphics.hpp>
#include "Types.h"

class Display
{
public:
	Display(){}
	Display(Double2 window_size, Wall* walls, int n_walls, Player *player);

	void drawWallsegment(Wall* wallsegment);
	void clearWalls();
	void renderFront();


	sf::RenderWindow* top_view;
	sf::RenderWindow* front_view;
	
	Double2 window_size;

private:

	Double2 center;
	double room_height;


	Scanline scanline;


	sf::Image* image;
	sf::Texture texture;
	sf::Sprite sprite;
	//sf::RenderWindow* top_view;
	//sf::RenderWindow* front_view;


	Player* player;

	void renderTopView();
	void prepFront();
	void addSegment(Wall* segment);


	sf::VertexArray* visibleSegments;
	int n_visible = 0;




	Wall* all_walls;
	int total_walls;


	double horizon = 1800;

};

