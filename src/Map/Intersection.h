//
// Created by natha on 31/10/2022.
//

#ifndef MAINPROJECT_INTERSECTION_H
#define MAINPROJECT_INTERSECTION_H


#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>


class Intersection {
public:
    explicit Intersection(const sf::Vector2f & position);
    const sf::Vector2f & getPosition() const;
    void setPosition(const sf::Vector2f & position);
    void draw(sf::RenderWindow & window) const;
private:
    sf::Vector2f coords;
    sf::RectangleShape shape;
};


#endif //MAINPROJECT_INTERSECTION_H
