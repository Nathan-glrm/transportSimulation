
#include <iostream>
#include <SFML/Graphics.hpp>
#include "./src/View/MapView.h"
#include "src/Map/Map.h"

int main() {

	//Create SFML Window object
	sf::RenderWindow window(sf::VideoMode(1200, 1000), "My window");
    //Create custom View to handle all camera movement
	MapView mapView = MapView(&window);
	//Create an in-simulation Map
    Map map("./assets/MapData/mapData.json");


	sf::Clock clock;

	//Render loop
    while (window.isOpen()){

		//
		//Treatment of events
		//
        sf::Event event{};
        while (window.pollEvent(event))
        {
            mapView.handleEvent(event);
			if (event.type == sf::Event::Closed){
				window.close();
			}
        }

		if (clock.getElapsedTime().asSeconds() > 2 && sf::Keyboard::isKeyPressed(sf::Keyboard::M) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
			clock.restart();
			map.constructMap("./assets/MapData/mapData.json");
		}

		//Move camera if needed
		mapView.moveLoops();


		//		 //
		//Drawing//
		//		 //
        window.clear(sf::Color::Black);
        window.setView(mapView.getView());
        map.draw(window);


        window.display();
    }
    return 0;
}
