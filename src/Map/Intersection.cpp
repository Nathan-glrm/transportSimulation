//
// Created by natha on 31/10/2022.
//

#include "Intersection.h"
#include <cmath>

float Intersection::inter_size = 10.0f;

Intersection::Intersection(const std::string &name, const sf::Vector2f &position) :
	Node(name, position), shape(Intersection::inter_size - 1.0f)
	{
		shape.setOutlineColor(sf::Color::Magenta);
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineThickness(1.0f);
		updateShape();
}

void Intersection::setPosition(const sf::Vector2f &position) {
    Node::setPosition(position);
	updateShape();
}



void Intersection::draw(sf::RenderWindow &window) const{
    window.draw(shape);
}

void Intersection::updateShape() {
	//shape.setOrigin(shape.getSize().x/2, shape.getSize().y/2); //Only used for rectangle

	//Only for circle
	shape.setOrigin(shape.getRadius(), shape.getRadius());


	shape.setPosition(Node::getPosition());
}

std::array<Node *, 2> Intersection::createPathBetween(const Intersection *from, const Intersection *to) {
	//Calculer l'angle d'entre de chaque intersection

	//Calculer le delta X et Y
	float deltaX = to->getPosition().x - from->getPosition().x;
	float deltaY = to->getPosition().y - from->getPosition().y;


	//Calcul de l'angle partant de from et partant de to
	double fromAngle = fmod(std::atan2(deltaY, deltaX) * 180.0 / M_PI + 90.0 + 360.0, 360.0);
	double toAngle = fmod(fromAngle + 180, 360);


	//Calcul des coordonées des nodes

	//Node de from
	sf::Vector2f coordsNodeFrom(0,0);
	coordsNodeFrom.x = from->getPosition().x + Intersection::inter_size * sin(M_PI * 2 * fromAngle / 360);
	coordsNodeFrom.y = from->getPosition().y - Intersection::inter_size * cos(M_PI * 2 * fromAngle / 360);
	Node * fromNode = new Node(from->name + Node::getNextId(),coordsNodeFrom);

	//Node de to
	sf::Vector2f coordsNodeTo(0,0);
	coordsNodeTo.x = to->getPosition().x + Intersection::inter_size * sin(M_PI * 2 * toAngle / 360);
	coordsNodeTo.y = to->getPosition().y - Intersection::inter_size * cos(M_PI * 2 * toAngle / 360);
	Node * toNode = new Node(Node::getNextId(),coordsNodeTo);

	return std::array<Node *, 2> {fromNode, toNode};

}


