//
// Created by natha on 31/10/2022.
//

#ifndef MAINPROJECT_INTERSECTION_H
#define MAINPROJECT_INTERSECTION_H


#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "Node.h"


class Intersection : public Node{
public:
    Intersection(const std::string &name, const sf::Vector2f & position);
	void setPosition(const sf::Vector2f &position) override;
    void draw(sf::RenderWindow & window) const;

	/**
	 *
	 * @param from L'intersection de départ
	 * @param to L'intersection d'arrivé
	 * @param fromNode Une node tout juste créer qui servira a stocker les coordonnées du point d'entrée de From
	 * @param toNode Une node tout juste créer qui servira a stocker les coordonnées du point d'entrée de To
	 */
	static std::array<Node *, 2> createPathBetween(const Intersection * from, const Intersection * to);


	static float inter_size;
protected:

	void updateShape();

private:
	const std::string name;
    sf::CircleShape shape;



};


#endif //MAINPROJECT_INTERSECTION_H
