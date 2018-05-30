#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "VehicleSystem.h"
#include <memory>
#include "VehicleSystem.h"
#include "Vehicle.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 1000), "SFML works!");

	VehicleSystem vSystem;
	Clock gameClock;
	float pressedAddTimer = 0;
	float pressedDeleteTimer = 0;
	vSystem.SpawnVehicles(&window, 10, 1200, 1000);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();	
		}

		// Turn On/Off Separation
		if (Keyboard::isKeyPressed(Keyboard::I))
			if (vSystem.isSeparating)
				vSystem.isSeparating = false;
			else
				vSystem.isSeparating = true;

		// Turn On/Off Alignment
		if (Keyboard::isKeyPressed(Keyboard::O))
			if (vSystem.isAlignmenting)
				vSystem.isAlignmenting = false;
			else
				vSystem.isAlignmenting = true;

		// Turn On/Off Cohesion
		if (Keyboard::isKeyPressed(Keyboard::P))
			if (vSystem.isCohesioning)
				vSystem.isCohesioning = false;
			else
				vSystem.isCohesioning = true;

		// Adds More Vehicles
		if (Keyboard::isKeyPressed(Keyboard::K) && pressedAddTimer <= 0)
		{
			vSystem.AddVehicle();
			pressedAddTimer = 0.1f;
		}
		// Removes Vehicles
		if (Keyboard::isKeyPressed(Keyboard::L) && pressedDeleteTimer <= 0 && vSystem.vehicles.size() > 1)
		{
			vSystem.RemoveVehicle();
			pressedDeleteTimer = 0.1f;
		}

		float deltaTime = gameClock.restart().asSeconds();
		pressedAddTimer -= deltaTime;
		pressedDeleteTimer -= deltaTime;
		vSystem.Update(deltaTime);

		window.clear();
		vSystem.Draw();
		window.display();
	}

	return 0;
}
