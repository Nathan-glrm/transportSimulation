//
// Created by natha on 31/10/2022.
//

#ifndef MAINPROJECT_LINE_H
#define MAINPROJECT_LINE_H


#include <SFML/System/Vector2.hpp>

class Line {
public:
    Line(const sf::Vector2f & fromPoint, const sf::Vector2f & toPoint);

protected:
    sf::Vector2f fromPoint;
    sf::Vector2f toPoint;
};


#endif //MAINPROJECT_LINE_H
