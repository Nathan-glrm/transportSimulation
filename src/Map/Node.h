//
// Created by natha on 31/10/2022.
//

#ifndef MAINPROJECT_NODE_H
#define MAINPROJECT_NODE_H


#include <SFML/System/Vector2.hpp>
#include <string>

class Node {
public:
    explicit Node(const std::string & name, const sf::Vector2f & coords);
    const sf::Vector2f & getPosition() const;
    void setPosition(const sf::Vector2f & position);
    const std::string & getName() const;
private:
    sf::Vector2f coords;
    const std::string name;
};


#endif //MAINPROJECT_NODE_H
