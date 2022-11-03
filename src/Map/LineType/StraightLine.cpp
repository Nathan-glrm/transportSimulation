//
// Created by natha on 01/11/2022.
//

#include "StraightLine.h"

StraightLine::StraightLine(const sf::Vector2f &fromPoint, const sf::Vector2f &toPoint) : Line(fromPoint, toPoint) {

}

void StraightLine::draw(sf::RenderWindow &window) const {
    sf::Vertex line[] =
            {
                    sf::Vertex(fromPoint),
                    sf::Vertex(toPoint)
            };
    window.draw(line, 2, sf::Lines);
}
