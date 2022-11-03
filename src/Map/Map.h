//
// Created by natha on 31/10/2022.
//

#ifndef MAINPROJECT_MAP_H
#define MAINPROJECT_MAP_H


#include <string>
#include <vector>
#include "Intersection.h"
#include "Path.h"
#include "Place/Place.h"
#include "Node.h"

class Map {
public:
    Map(const std::string & nodeFileName, const std::string & linksFileName);
    void getTrajetCarOnly(const Place & start, const Place & destination) const;
    void draw(sf::RenderWindow & window) const;
private:
    void constructMap(const std::string & nodeFileName, const std::string & linksFileName);

    std::map<std::string, Intersection *> intersectionList;
    std::map<std::string, Node *> nodeList;
    std::vector<Path *> pathList;
    std::vector<Place *> placeList;
    int** matrixCar;
};


#endif //MAINPROJECT_MAP_H
