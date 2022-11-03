//
// Created by natha on 31/10/2022.
//

#ifndef MAINPROJECT_PATH_H
#define MAINPROJECT_PATH_H


#include "Intersection.h"
#include "LineType/Line.h"
#include "Node.h"

class Path {
public:
    Path(const Node & from, const Node & to);
    void draw(sf::RenderWindow & window) const;
    float getLength() const;
    const Node & getFrom() const;
    const Node & getTo() const;
private:
    std::vector<Line *> lineList;
    const Node & m_from;
    const Node & m_to;
};


#endif //MAINPROJECT_PATH_H
