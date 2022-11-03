//
// Created by natha on 31/10/2022.
//

#include <fstream>
#include <iostream>
#include <limits>
#include "Map.h"
#include "../utils/explode.h"

Map::Map(const std::string &nodeFileName, const std::string &linksFileName)
: intersectionList(), nodeList() ,pathList(), placeList(), matrixCar(){
    constructMap(nodeFileName, linksFileName);
}

void Map::constructMap(const std::string &nodeFileName, const std::string &linksFileName) {

    /* Intersection */
    std::cout << "Setup Node" << std::endl;
    std::ifstream intersectionsFile(nodeFileName);
    if (intersectionsFile.is_open()){
        while(intersectionsFile.good()){
            std::string line;
            std::getline(intersectionsFile, line);
            auto params = explode(line, ',');

            intersectionList.emplace(params[0], new Intersection(sf::Vector2f(std::stof(params[1]), std::stof(params[2]))));
            //TODO implémentation temporaire des nodes
            nodeList.emplace(params[0], new Node(params[0], sf::Vector2f(std::stof(params[1]), std::stof(params[2]))));
        }
    }
    else{
        throw std::domain_error("File not open");
    }


    std::cout << "Setup Path" << std::endl;
    std::ifstream linksFile(linksFileName);
    if (linksFile.is_open()){
        while(linksFile.good()){
            std::string line;
            std::getline(linksFile, line);
            auto params = explode(line, ',');

            pathList.push_back(new Path(*nodeList.find(params[0])->second, *nodeList.find(params[1])->second));
        }
    }
    else{
        throw std::domain_error("File not open");
    }

    /* Matrix */

    const float neutral = std::numeric_limits<float>::max();
    const int neutralInt = std::numeric_limits<int>::max();

    //Initialisation des de la matrice de calcul
    //TODO simplifier avec une seul boucle
    auto** matrixCarCalc = new float*[nodeList.size()];
    for (int i = 0; i < nodeList.size(); i++) {
        matrixCarCalc[i] = new float[nodeList.size()];
    }
    for (int i = 0; i < nodeList.size(); i++) {
        for (int j = 0; j < nodeList.size(); j++) {
            matrixCarCalc[i][j] = neutral;
        }
    }

    //Initialisation de la matrice de calcul pour les chemins existants
    for (auto path: pathList) {
        auto from = nodeList.find(path->getFrom().getName());
        auto to = nodeList.find(path->getTo().getName());
        if (from == nodeList.end() || to == nodeList.end()){
            throw std::range_error("Try to find unlisted node");
        }
        int indexFrom = (int) std::distance(nodeList.begin(), from);
        int indexTo = (int) std::distance(nodeList.begin(), to);
        matrixCarCalc[indexFrom][indexTo] = path->getLength();
    }

    //Intialisation de la matrice résultat
    matrixCar = new int*[nodeList.size()];
    for (int i = 0; i < nodeList.size(); i++) {
        matrixCar[i] = new int[nodeList.size()];
        for (int j = 0; j < nodeList.size(); j++) {
            if (matrixCarCalc[i][j] == neutral){
                matrixCar[i][j] = neutralInt;
            }
            else{
                matrixCar[i][j] = j;
            }
        }
    }

    //Application de l'algorithme de Warshall
    //TODO à déplacer dans une fonction
    for (int k = 0; k < nodeList.size(); k++){
        for (int i = 0; i < nodeList.size(); i++) {
            for (int j = 0; j < nodeList.size(); j++) {
                float newLenght = std::min(matrixCarCalc[i][j], matrixCarCalc[i][k] + matrixCarCalc[k][j]);
                if (matrixCarCalc[i][j] > newLenght){
                    matrixCarCalc[i][j] = newLenght;
                    matrixCar[i][j] = matrixCar[i][k];
                }
            }
        }
    }

    //Suppression allocation dynamique
    for (int i = 0; i < nodeList.size(); ++i) {
        delete [] matrixCarCalc[i];
    }
    delete [] matrixCarCalc;

    //Output de la matrice pour deboguage
    //TODO Supprimer cet output
    for (int i = 0; i < nodeList.size(); i++) {
        for (int j = 0; j < nodeList.size(); j++) {
            std::cout << matrixCar[i][j] << "\t";
        }
        std::cout << std::endl;
    }

}

void Map::draw(sf::RenderWindow &window) const {
    for (const auto& elem: intersectionList) {
        elem.second->draw(window);
    }
    for (auto elem: pathList) {
        elem->draw(window);
    }
}
