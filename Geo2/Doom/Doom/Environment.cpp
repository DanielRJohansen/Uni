#include "Environment.h"




void Environment::drawAll(int n_walls) {
    display.clearWalls();
    for (int i = 0; i < n_walls; i++) {
        display.drawWallsegment(&walls[i]);
    }
    display.renderFront();
}



void Environment::handleKeypress(sf::Event* event) {
    switch (event->key.code) {
    case sf::Keyboard::W:
        movement[0] = 1;
        break;
    case sf::Keyboard::A:
        movement[1] = 1;
        break;
    case sf::Keyboard::S:
        movement[2] = 1;
        break;
    case sf::Keyboard::D:
        movement[3] = 1;
        break;
    default:
        break;
    }
}
void Environment::handleKeyrelease(sf::Event* event) {
    switch (event->key.code) {
    case sf::Keyboard::W:
        movement[0] = 0;
        break;
    case sf::Keyboard::A:
        movement[1] = 0;
        break;
    case sf::Keyboard::S:
        movement[2] = 0;
        break;
    case sf::Keyboard::D:
        movement[3] = 0;
        break;
    default:
        break;
    }
}


void Environment::handleMovement() {
    for (int i = 0; i < 4; i++) {
        player.move(angles[i], dt, movement[i]);    // player ignores if movement[i] = 0;
    }
}

void Environment::handleRotation() {
    double x = sf::Mouse::getPosition(*display.front_view).x * 2/display.window_size.x - 1;
    player.rotate( - x * 3.14 / 4 * 0.5);
    sf::Mouse::setPosition(sf::Vector2i(display.window_size.x / 2, display.window_size.y / 2), *display.front_view);
    

}



void Environment::run() {
	while (true) {


        sf::Event event;
        while (display.front_view->pollEvent(event))
        {
            // check the type of the event...
            switch (event.type) {
                // window closed
            case sf::Event::Closed:
                display.front_view->close();
                display.top_view->close();
                break;
            case sf::Event::GainedFocus:
                pause = 0;
                sf::Mouse::setPosition(sf::Vector2i(display.window_size.x/2, display.window_size.y/2), *display.front_view);
                break;
            case sf::Event::LostFocus:
                pause = 1;
                break;
            case sf::Event::KeyPressed:
                handleKeypress(&event);
                break;
            case sf::Event::KeyReleased:
                handleKeyrelease(&event);
                break;
            default:
                break;
            }
        }

        if (pause) {
            continue;
        }

        bsp.paint(&player, &display);

        handleMovement();
        handleRotation();
        //drawAll(this->n_walls);


        //while (true) {}

	}
}