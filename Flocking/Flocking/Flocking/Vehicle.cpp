#include "Vehicle.h"



Vehicle::Vehicle(RenderWindow* gameWindow, int movementAngle, Vector2f spawnPosition)
{
	window = gameWindow;
	angle = movementAngle;
	speed = 20;
	
	position = spawnPosition;
	test.setPosition(spawnPosition);

	//circle.setFillColor(sf::Color::Green);

	// resize it to 5 points
	test.setPointCount(3);

	// define the points
	test.setPoint(0, sf::Vector2f(0, 40));
	test.setPoint(1, sf::Vector2f(-10, 0));
	test.setPoint(2, sf::Vector2f(10, 0));
	test.setRotation(angle);
	test.setFillColor(sf::Color::Green);
}

float Vehicle::length(Vector2f v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

Vector2f Vehicle::Normalize(Vector2f v) {
	Vector2f vector;
	float distance = length(v);

	if (distance != 0) {
		vector.x = v.x / distance;
		vector.y = v.y / distance;
	}

	return vector;
}

void Vehicle::CreateForce()
{
	//Separation
	separationDirection = Vector2f(0, 0);
	alignmentDirection = Vector2f(0, 0);
	cohesionDirection = Vector2f(0, 0);
	float count = 0;
	for (int i = 0; i < influenceVehicles.size() - 1; ++i)
	{
		if (this != influenceVehicles[i])
		{
			Vector2f difference = Vector2f(0, 0);
			difference.x = position.x - influenceVehicles[i]->position.x;
			difference.y = position.y - influenceVehicles[i]->position.y;
			float distance = length(difference);
			if (distance < 100)
			{
				
				difference = Normalize(difference);
				separationDirection += difference/distance;

				count++;
			}
			if (distance < 130)
			{
				alignmentDirection += influenceVehicles[i]->velocity;
			}
			if (distance < 120)
			{
				cohesionDirection += influenceVehicles[i]->position;
			}
		}
	}
	if (count > 0)
	{
		separationDirection = separationDirection / count;
		//separationDirection = Normalize(separationDirection);
		alignmentDirection = alignmentDirection / count;
		//alignmentDirection = Normalize(alignmentDirection);
		cohesionDirection = cohesionDirection / count;
		//cohesionDirection = Normalize(cohesionDirection);
	}
	//Alignment
	//Cohesion
}

void Vehicle::ApplyForce(bool appliesSep, bool appliesAlign, bool appliesCoh)
{
	if (appliesSep)
		separationDirection = Vector2f(0, 0);
	if (appliesAlign)
		alignmentDirection = Vector2f(0, 0);
	if (appliesCoh)
		cohesionDirection = Vector2f(0, 0);

	velocity += separationDirection * separationScalingForce;
	velocity += alignmentDirection * alignmentScalingForce;
	velocity += cohesionDirection * cohesionScalingForce;

	velocity = Normalize(velocity);
}

void Vehicle::Update(float dt)
{
	velocity.y += sin((180 / 3.14)*test.getRotation()) * dt * speed;
	velocity.x += cos((180 / 3.14)*test.getRotation())* dt * speed;

	velocity = Normalize(velocity) * 0.1f;
	position = position - velocity;
	test.setPosition(position);
	float a = atan2f(velocity.y, velocity.x);
	test.setRotation((a * (180/3.14)) + 90 );
}

void Vehicle::Draw()
{
	window->draw(test);
}

Vector2f Vehicle::getCenter()
{
	return position;
}


Vehicle::~Vehicle()
{
}
