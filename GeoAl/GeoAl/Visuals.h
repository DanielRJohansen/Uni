#pragma once

#include <SFML\graphics.hpp>
#include "Containers.h"

class Visuals
{
public:
	Visuals(Int2 window_size);

	void draw(LineSegment* segments, int num_segments, Int2 center, LineSegment* swpline);


private:
	sf::Image* image;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RenderWindow* window;




	void drawLine(sf::RenderTarget* target, LineSegment segment);
};

