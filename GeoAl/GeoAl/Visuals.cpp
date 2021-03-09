#include "Visuals.h"





Visuals::Visuals(Double2 window_size) {													// Setup window
	int width = window_size.x;
	int height = window_size.y;
	window = new sf::RenderWindow(sf::VideoMode(width, height), "Visible lines-", sf::Style::Close);
	this->window_size = window_size;


	image = new sf::Image();															// Background color
	image->create(width, height, sf::Color(0xEB, 0xEB, 0xEB));

	texture.loadFromImage(*image);
	sprite.setTexture(texture, true);
}


void Visuals::drawLine(sf::RenderTarget* target, LineSegment segment) {
	sf::RectangleShape line(sf::Vector2f(segment.len(), 3));
	if (segment.visibility == SEEN)
		line.setFillColor(sf::Color(0, 255, 0));
	else if (segment.visibility == UNSEEN)
		line.setFillColor(sf::Color(255, 0, 0));
	else
		line.setFillColor(sf::Color(0, 0, 100));

	if (segment.current)
		line.setFillColor(sf::Color(250, 250, 0));

	line.rotate(- segment.angle());
	line.setPosition((int)segment.p1.x , (int)(window_size.y-segment.p1.y));
	window->draw(line);
}



void Visuals::draw(LineSegment* segments,  int num_segments, Double2 center, LineSegment* swpline)
{
	sf::Event event;
	while (true) {																		// I run in this loop to make the window dragable.
		window->draw(sprite);


		// Draw inputs
		sf::CircleShape p(10);
		p.setFillColor(sf::Color(0, 0, 0));
		p.setPosition(center.x, window_size.y - center.y);
		window->draw(p);

		for (int i = 0; i < num_segments; i++) {
			drawLine(window, segments[i]);
		}
		drawLine(window, *swpline);



		window->display();

		window->pollEvent(event);
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Right) {
				break;
			}
		}
	}


}




