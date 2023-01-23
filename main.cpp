

#include <SFML/Graphics.hpp>
#include "./src/View/MapView.h"
#include "src/Map/Map.h"

int main() {

	//Create SFML Window object
	sf::RenderWindow window(sf::VideoMode(1200, 1000), "My window");
    //Create custom View to handle all camera movement
	MapView map = MapView(&window);

	//Create a in-simulation Map
    Map m("./assets/MapData/node.txt", "./assets/MapData/road.txt");

	//Render loop
    while (window.isOpen()){

		//
		//Treatment of events
		//
        sf::Event event{};
        while (window.pollEvent(event))
        {
            map.handleEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

		//Move camera if needed
		map.moveLoops();


		//		 //
		//Drawing//
		//		 //
        window.clear(sf::Color::Black);
        window.setView(map.getView());
        m.draw(window);


        window.display();
    }
    return 0;
}
