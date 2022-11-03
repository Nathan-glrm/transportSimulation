//
// Created by natha on 31/10/2022.
//

#include "Line.h"
#include <cmath>

Line::Line(const sf::Vector2f &fromPoint, const sf::Vector2f &toPoint)
: fromPoint(fromPoint), toPoint(toPoint){
    length = sqrt(pow(toPoint.x - fromPoint.x, 2) + pow(toPoint.y - fromPoint.y, 2));
}

float Line::getLength() const {
    return length;
}
