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

protected:

private:
    bool isMoving;
    sf::Vector2f mousePos;
    sf::View view;
    sf::RenderWindow* window;
};


#endif //MAINPROJECT_MAPVIEW_H
