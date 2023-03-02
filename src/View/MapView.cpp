//
// Created by natha on 31/10/2022.
//

#include <iostream>
#include "MapView.h"

const float MapView::CAMOFFSET = .2;

MapView::MapView(sf::RenderWindow * window) :
        window(window),isMoving(false), view(sf::Vector2f(0.f, 0.f), sf::Vector2f(window->getSize().x, window->getSize().y)),
		isDownPressed(false), isLeftPressed(false), isRightPressed(false), isUpPressed(false)
{
	view.setCenter(450,400);
}




void MapView::handleMovementBools(const sf::Event &event, const bool action) {
	switch (event.key.code) {
		case sf::Keyboard::Q:
			isRightPressed = action;
			break;
		case sf::Keyboard::D:
			isLeftPressed = action;
			break;
		case sf::Keyboard::S:
			isDownPressed = action;
			break;
		case sf::Keyboard::Z:
			isUpPressed = action;
			break;
	}
}

void MapView::handleEvent(const sf::Event &event) {
	switch (event.type) {
		case sf::Event::KeyPressed:
			handleMovementBools(event, true);
			if (event.key.code == sf::Keyboard::R) {
				view.setCenter(0, 0);
				view.setSize(window->getSize().x, window->getSize().y);
			}
			break;
		case sf::Event::KeyReleased:
			handleMovementBools(event, false);
			break;
		case sf::Event::MouseWheelScrolled:
			if (event.mouseWheelScroll.delta == -1) {
				view.zoom(1.05);
			} else {
				view.zoom(0.95);
			}
			break;
		case sf::Event::Resized:
			view.setSize(sf::Vector2f(event.size.width, event.size.height));
			break;

			//3 next cases : Code from https://stackoverflow.com/questions/41788847/dragging-screen-in-sfml
		case sf::Event::MouseButtonPressed:
			// Mouse button is pressed, get the position and set moving as active
			if (event.mouseButton.button == sf::Mouse::Right) {
				this->isMoving = true;
				this->mousePos = this->window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Right) {
				this->isMoving = false;
			}
			break;
		case sf::Event::MouseMoved:
			// Ignore mouse movement unless a button is pressed (see above)
			if (this->isMoving) {
				// Determine the new position in world coordinates
				const sf::Vector2f newPos = this->window->mapPixelToCoords(
						sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
				// Determine how the cursor has moved
				// Swap these to invert the movement direction
				const sf::Vector2f deltaPos = this->mousePos - newPos;

				// Move our view accordingly and update the window
				this->view.setCenter(view.getCenter() + deltaPos);
				this->window->setView(view);

				// Save the new position as the old one
				// We're recalculating this, since we've changed the view
				this->mousePos = this->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
			}
			break;
	}
}

const sf::View &MapView::getView() const {
    return view;
}


void MapView::moveLoops() {
	float y = 0;
	float x = 0;
	if (isUpPressed){
		y -= MapView::CAMOFFSET;
	}
	if (isDownPressed){
		y += MapView::CAMOFFSET;
	}
	if (isRightPressed){
		x -= MapView::CAMOFFSET;
	}
	if (isLeftPressed){
		x += MapView::CAMOFFSET;
	}

	view.move(x, y);
}



