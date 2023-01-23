//
// Created by natha on 31/10/2022.
//

#ifndef MAINPROJECT_MAPVIEW_H
#define MAINPROJECT_MAPVIEW_H

#include <string>
#include <SFML/Graphics.hpp>

class MapView {
public:
    explicit MapView(sf::RenderWindow * window);
    void handleEvent(const sf::Event & event);
    const sf::View & getView() const;
	void moveLoops();

	static const float CAMOFFSET;

protected:
	void handleMovementBools(const sf::Event &event, const bool action);



private:
    bool isMoving;
    sf::Vector2f mousePos;
    sf::View view;
    sf::RenderWindow* window;

	bool isUpPressed;
	bool isDownPressed;
	bool isLeftPressed;
	bool isRightPressed;
};


#endif //MAINPROJECT_MAPVIEW_H
