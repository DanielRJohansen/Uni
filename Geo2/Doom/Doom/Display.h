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


	Player* player;

	void renderTopView();
	void prepFront();
	Double2 projectOnFocalPlane(Vec3d segment);
	void handleWallBehindPlayer(Vec3d* w1, Vec3d* w2, Wall* wallsegment);
	void handleFlipwall(Double2* br, Double2* tr, Double2* bl, Double2* tl);
	void addSegment(Wall* segment);


	sf::VertexArray* visibleSegments;
	int n_visible = 0;




	Wall* all_walls;
	int total_walls;


	double horizon = 1800;

};

