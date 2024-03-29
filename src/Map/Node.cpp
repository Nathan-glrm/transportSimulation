//
// Created by natha on 31/10/2022.
//

#include "Node.h"
int Node::global_nodes_id = 0;

Node::Node(const std::string &name, const sf::Vector2f &coords)  : name(name), coords(coords) {
}

const sf::Vector2f &Node::getPosition() const {
    return coords;
}

void Node::setPosition(const sf::Vector2f &position) {
    coords = position;
}

const std::string &Node::getName() const {
    return name;
}
