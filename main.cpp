

#include <SFML/Graphics.hpp>
#include "./src/View/MapView.h"
#include "src/Map/Map.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 1000), "My window");
    MapView map = MapView(&window);

    Map m("./assets/MapData/node.txt", "./assets/MapData/road.txt");

    while (window.isOpen()){
        sf::Event event{};
        while (window.pollEvent(event))
        {
            map.handleEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
		map.moveLoops();

        window.clear(sf::Color::Black);
        window.setView(map.getView());
        m.draw(window);


        window.display();
    }
    return 0;
}
