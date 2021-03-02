#include "Visuals.h"





Visuals::Visuals(Int2 window_size) {													// Setup window
	int width = window_size.x;
	int height = window_size.y;
	window = new sf::RenderWindow(sf::VideoMode(width, height), "Visible lines-", sf::Style::Close);

	image = new sf::Image();															// Background color
	image->create(width, height, sf::Color(0xEB, 0xEB, 0xEB));

	texture.loadFromImage(*image);
	sprite.setTexture(texture, true);
}


void Visuals::drawLine(sf::RenderTarget* target, LineSegment segment) {
	sf::RectangleShape line(sf::Vector2f(segment.len(), 3));
	line.setFillColor(sf::Color(0, 0, 0));
	line.rotate(segment.angle());
	line.setPosition(segment.p1.x , segment.p1.y);
	window->draw(line);
}



void Visuals::draw(LineSegment* segments, int num_segments, Int2 center)
{
	//window->enableKeyRepeat(false);
	//window->setKeyRepeatEnabled(false);

	while (true) {																		// I run in this loop to make the window dragable.
		sf::Event event;
		window->pollEvent(event);
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
			printf("Click\n");
		}





		window->draw(sprite);


		// Draw inputs
		sf::CircleShape p(10);
		p.setFillColor(sf::Color(0, 0, 0));
		p.setPosition(center.x, center.y);
		window->draw(p);

		for (int i = 0; i < num_segments; i++) {
			drawLine(window, segments[i]);
		}



		window->display();

	}


}




