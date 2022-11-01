//
// Created by natha on 31/10/2022.
//

#ifndef MAINPROJECT_BEZIERCURVE_H
#define MAINPROJECT_BEZIERCURVE_H

#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "Line.h"

class BezierCurve : public Line {
public:
    BezierCurve(const sf::Vector2f & fromPoint, const sf::Vector2f & fromControlPoint, const sf::Vector2f & toPoint, const sf::Vector2f & toControlPoint);
    const sf::Vertex * getArray() const;
    sf::Vector2f getPositionWithPercent(const float t) const;
    sf::Vector2f getPositionWithDistance(const float t) const;
    sf::Vector2f getPositionWithDistanceByPercent(const float t) const;
    void calcPoint();
    void draw(sf::RenderWindow & window) const;
private:
    std::vector<sf::Vertex> listepoint;
    std::map<float, float> interpolation;
    sf::Vector2f fromControlPoint;
    sf::Vector2f toControlPoint;
    float distance;
};


#endif //MAINPROJECT_BEZIERCURVE_H
