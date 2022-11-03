//
// Created by natha on 01/11/2022.
//

#ifndef MAINPROJECT_STRAIGHTLINE_H
#define MAINPROJECT_STRAIGHTLINE_H


#include "Line.h"

class StraightLine : public Line {
public:
    StraightLine(const sf::Vector2f & fromPoint, const sf::Vector2f & toPoint);
    void draw(sf::RenderWindow & window) const override;
};


#endif //MAINPROJECT_STRAIGHTLINE_H
