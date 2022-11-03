//
// Created by natha on 31/10/2022.
//

#include "Path.h"
#include "LineType/StraightLine.h"

Path::Path(const Node &from, const Node &to) : m_from(from), m_to(to) {
    lineList.push_back(new StraightLine(from.getPosition(), to.getPosition()));
}

void Path::draw(sf::RenderWindow &window) const {
    for (auto elem : lineList) {
        elem->draw(window);
    }
}

float Path::getLength() const {
    float length = 0;
    for (auto elem : lineList) {
        length += elem->getLength();
    }
    return length;
}

const Node &Path::getFrom() const {
    return m_from;
}

const Node &Path::getTo() const {
    return m_to;
}
