//
// Created by natha on 31/10/2022.
//

#include "Intersection.h"

Intersection::Intersection(const sf::Vector2f &position) : coords(), shape(sf::Vector2f(10, 10)){
    setPosition(position);
    shape.setFillColor(sf::Color::Magenta);
}

void Intersection::setPosition(const sf::Vector2f &position) {
    coords = position;
    shape.setOrigin(shape.getSize().x/2, shape.getSize().y/2);
    shape.setPosition(position);

}

void Intersection::draw(sf::RenderWindow &window) const{
    window.draw(shape);
}

const sf::Vector2f &Intersection::getPosition() const {
    return coords;
}


