//
// Created by natha on 31/10/2022.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include "BezierCurve.h"
#include "cmath"

BezierCurve::BezierCurve(const sf::Vector2f & fromPoint, const sf::Vector2f & fromControlPoint, const sf::Vector2f & toControlPoint, const sf::Vector2f & toPoint) :
        Line(fromPoint, toPoint), fromControlPoint(fromControlPoint), toControlPoint(toControlPoint), listepoint(), interpolation()
{
    calcPoint();
}

void BezierCurve::calcPoint(){
    const int precision = 100;
    for (int i = 0; i <= precision; ++i) {
        float percent = (float)i / precision;
        sf::Vector2f pos = getPositionWithPercent(percent);
        listepoint.emplace_back(pos);
    }
    const int precisionLen = 30;
    //Calc length
    sf::Vector2f lastPosition = getPositionWithPercent(0);
    interpolation.emplace(0, 0);
    length = 0;

    for (int i = 1; i <= precisionLen; ++i) {
        float percent = (float)i / precisionLen;
        sf::Vector2f pos = getPositionWithPercent(percent);
        float dis = sqrt(pow(pos.x - lastPosition.x, 2) + pow(pos.y - lastPosition.y, 2));
        lastPosition = pos;
        length += dis;
        interpolation.emplace(length, percent);
    }
}

const sf::Vertex* BezierCurve::getArray() const {
    return &listepoint[0];
}

sf::Vector2f BezierCurve::getPositionWithPercent(const float t) const {
    if (t < 0 || t > 1) throw std::range_error("t is not between [0..1], t = " + std::to_string(t));
    float x = pow((1-t), 3)* fromPoint.x +
              3*pow((1-t),2) * t * fromControlPoint.x +
              3*(1-t) * pow(t, 2) * toControlPoint.x +
              pow(t, 3) * toPoint.x;

    float y = pow((1-t), 3)* fromPoint.y +
              3*pow((1-t),2) * t * fromControlPoint.y +
              3*(1-t) * pow(t, 2) * toControlPoint.y +
              pow(t, 3) * toPoint.y;

    return {x, y};
}

void BezierCurve::draw(sf::RenderWindow & window) const {
    window.draw(getArray(), listepoint.size(), sf::LinesStrip);
}

sf::Vector2f BezierCurve::getPositionWithDistance(const float t) const {
    auto upper = interpolation.upper_bound(t);
    auto lower(upper);
    if (lower != interpolation.begin()){
        lower--;
    }

    //y = y1 + ((x – x1)/(x2 - x1) × (y2 - y1))
    float estimate = lower->second + ((t - lower->first)/(upper->first - lower->first) * (upper->second - lower->second));
    return getPositionWithPercent(estimate);
}

sf::Vector2f BezierCurve::getPositionWithDistanceByPercent(const float t) const {
    return getPositionWithDistance(t*length);
}

