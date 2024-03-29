//
// Created by natha on 31/10/2022.
//

#include <fstream>
#include <iostream>
#include <limits>
#include "Map.h"
#include "../utils/explode.h"
#include "../utils/json.hpp"
using json = nlohmann::json;

Map::Map(const std::string &jsonFile)
: intersectionList(), nodeList() ,pathList(), placeList(), matrixCar(){
    constructMap(jsonFile);
}

void Map::constructMap(const std::string &jsonFile) {

	//Clear value, in case we force rebuild of the map
	intersectionList.clear();
	nodeList.clear();
	pathList.clear();
	placeList.clear();

	//Open and setup jsondata
	std::ifstream f(jsonFile);
	json mapData = json::parse(f);







    /* Intersection */
    std::cout << "Setup intersections" << std::endl;
	auto intersections = mapData["intersections"];

	for(auto & intersection : intersections){
		//Get name from json
		std::string intersectionId = intersection.at("name");
		//Get coords from json
		auto coords = sf::Vector2f(intersection.at("coords").at("x"),
								   intersection.at("coords").at("y"));
		//Create intersection @name at @coords
		intersectionList.emplace(intersectionId, new Intersection(intersectionId, coords));




		//TODO implémentation temporaire des intersections
		//nodeList.emplace(intersection.at("name"), new Node(intersection.at("name"), sf::Vector2f(intersection.at("coords").at("x"), intersection.at("coords").at("y"))));

	}

    std::cout << "Setup Paths" << std::endl;
	auto paths = mapData["paths"];
	for(auto & path : paths){

		//Dans intersection, faire la "demande" d'un chemin entre @FROM et @TO
		auto from = intersectionList.find(path.at("from"))->second;
		auto to = intersectionList.find(path.at("to"))->second;
		std::array<Node *, 2> nodes = Intersection::createPathBetween(from, to);
		nodeList.emplace(nodes[0]->getName(), nodes[0]);
		nodeList.emplace(nodes[1]->getName(), nodes[1]);


		pathList.push_back(new Path(*nodes[0], *nodes[1]));
	}


    /* Matrix */

    const float neutral = std::numeric_limits<float>::max();
    const int neutralInt = std::numeric_limits<int>::max();

    //Initialisation des de la matrice de calcul
    auto** matrixCarCalc = new float*[nodeList.size()];
    for (int i = 0; i < nodeList.size(); i++) {
        matrixCarCalc[i] = new float[nodeList.size()];
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
