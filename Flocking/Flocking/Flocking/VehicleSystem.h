#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <memory>
#include "Vehicle.h"

using namespace sf;
using namespace std;

class VehicleSystem
{
public:

	vector<Vehicle*> vehicles;
	RenderWindow* gameWindow;
	int gameWidth;
	int gameHeight;

	bool isSeparating = false;
	bool isCohesioning = false;
	bool isAlignmenting = false;
	VehicleSystem();

	void HandleScreenWrap();
	void SpawnVehicles(RenderWindow* window, int count, int windowWidth, int windowHeight);
	void AddVehicle();
	void RemoveVehicle();
	void SetSeparation(float num);
	void SetAlignment(float num);
	void SetCohesion(float num);
	void Update(float dt);
	void Draw();
	~VehicleSystem();
};

