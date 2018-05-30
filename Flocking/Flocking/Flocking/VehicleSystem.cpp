#include "VehicleSystem.h"



VehicleSystem::VehicleSystem()
{
}

void VehicleSystem::HandleScreenWrap()
{
	for (int i = 0; i < vehicles.size(); ++i)
	{
		if (vehicles[i]->position.x < 0)
			vehicles[i]->position.x = gameWidth;
		if (vehicles[i]->position.x > gameWidth)
			vehicles[i]->position.x = 0;
		if (vehicles[i]->position.y < 0)
			vehicles[i]->position.y = gameHeight;
		if (vehicles[i]->position.y > gameHeight)
			vehicles[i]->position.y = 0;
	}
}

void VehicleSystem::SpawnVehicles(RenderWindow* window, int count, int windowWidth, int windowHeight)
{
	gameWidth = windowWidth;
	gameHeight = windowHeight;
	gameWindow = window;
	for (int i = 0; i < count; i++)
	{
		int angle = rand() % 361;
		int xPosition = rand() % (windowWidth + 1);
		int yPosition = rand() % (windowHeight + 1);
		Vehicle* temp = new Vehicle(window, 0, Vector2f(xPosition, yPosition));
		vehicles.push_back(temp);
	}

	for (int i = 0; i < count; i++)
	{
		vehicles[i]->influenceVehicles = vehicles;
	}
}

void VehicleSystem::AddVehicle()
{
	int angle = rand() % 361;
	int xPosition = rand() % (gameWidth + 1);
	int yPosition = rand() % (gameHeight + 1);
	Vehicle* temp = new Vehicle(gameWindow, 0, Vector2f(xPosition, yPosition));
	vehicles.push_back(temp);

	for (int i = 0; i < vehicles.size() ; i++)
	{
		vehicles[i]->influenceVehicles = vehicles;
	}
}

void VehicleSystem::RemoveVehicle()
{
	delete vehicles[vehicles.size()-1];
	vehicles[vehicles.size()-1] = nullptr;
	vehicles.erase(vehicles.begin() + vehicles.size()-1);
	//vehicles.resize(vehicles.size()-1);
	for (int i = 0; i < vehicles.size(); i++)
	{
		vehicles[i]->influenceVehicles = vehicles;
	}
}

void VehicleSystem::Update(float dt)
{
	for (int i = 0; i < vehicles.size(); i++)
	{
		HandleScreenWrap();
		vehicles[i]->CreateForce();
		vehicles[i]->ApplyForce(isSeparating, isAlignmenting, isCohesioning);
		vehicles[i]->Update(dt);
	}
}

void VehicleSystem::Draw()
{
	for (int i = 0; i < vehicles.size(); i++)
	{
		vehicles[i]->Draw();
	}
}

void VehicleSystem::SetSeparation(float num)
{
	for (int i = 0; i < vehicles.size(); i++)
	{
		vehicles[i]->separationScalingForce = num;
	}
}

void VehicleSystem::SetAlignment(float num)
{
	for (int i = 0; i < vehicles.size(); i++)
	{
		vehicles[i]->alignmentScalingForce = num;
	}
}

void VehicleSystem::SetCohesion(float num)
{
	for (int i = 0; i < vehicles.size(); i++)
	{
		vehicles[i]->cohesionScalingForce = num;
	}
}

VehicleSystem::~VehicleSystem()
{
}
