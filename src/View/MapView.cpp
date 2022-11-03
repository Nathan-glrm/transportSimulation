//
// Created by natha on 31/10/2022.
//

#include "MapView.h"

MapView::MapView(sf::RenderWindow * window) :
        window(window),isMoving(false), view(sf::Vector2f(0.f, 0.f), sf::Vector2f(window->getSize().x, window->getSize().y))
{}

void MapView::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed)
    {
        float offset = 10;
        if (event.key.code == sf::Keyboard::Q)
        {
            view.move(-offset, 0);
        }
        else if (event.key.code == sf::Keyboard::D)
        {
            view.move(offset, 0);
        }
        else if (event.key.code == sf::Keyboard::S)
        {
            view.move(0, offset);
        }
        else if (event.key.code == sf::Keyboard::Z)
        {
            view.move(0, -offset);
        }

        else if (event.key.code == sf::Keyboard::R){
            view.setCenter(0,0);
            view.setSize(window->getSize().x, window->getSize().y);
        }
    }

    if (event.type == sf::Event::MouseWheelScrolled){
        if (event.mouseWheelScroll.delta == -1){
            view.zoom(1.05);
        }
        else{
            view.zoom(0.95);
        }
    }

    if (event.type == sf::Event::Resized){
        view.setSize(sf::Vector2f(event.size.width, event.size.height));
    }


    //3 next conditions : Code from https://stackoverflow.com/questions/41788847/dragging-screen-in-sfml
    if (event.type == sf::Event::MouseButtonPressed) {
        // Mouse button is pressed, get the position and set moving as active
        if (event.mouseButton.button == sf::Mouse::Right) {
            this->isMoving = true;
            this->mousePos = this->window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        }
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Right) {
            this->isMoving = false;
        }
    }
    if (event.type == sf::Event::MouseMoved){
        // Ignore mouse movement unless a button is pressed (see above)
        if (this->isMoving){
            // Determine the new position in world coordinates
            const sf::Vector2f newPos = this->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
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
    }
}

const sf::View &MapView::getView() const {
    return view;
}

