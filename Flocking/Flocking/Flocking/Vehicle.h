#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <memory>

using namespace sf;
using namespace std;

class Vehicle
{
public:

	RenderWindow* window;
	CircleShape circle;
	ConvexShape test;
	vector<Vehicle*> influenceVehicles;

	Vector2f position;
	Vector2f velocity;
	Vector2f separationDirection;
	Vector2f alignmentDirection;
	Vector2f cohesionDirection;
	Vector2f totalForce;

	float separationScalingForce = 3;
	float alignmentScalingForce = 0.7f;
	float cohesionScalingForce = 0.6f;
	int angle;
	int speed;
	bool deleteNextCycle = false;
		
	Vehicle(RenderWindow* gameWindow, int movementAngle, Vector2f position);
	float length(Vector2f v);
	Vector2f Normalize(Vector2f v);
	void CreateForce();
	void ApplyForce(bool appliesSep, bool appliesAlign, bool appliesCoh);
	void Update(float dt);
	void Draw();
	Vector2f getCenter();
	~Vehicle();
};

