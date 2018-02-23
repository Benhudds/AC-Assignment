// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CMonopoly.hpp"

int main()
{
	vector<string> players;
	players.push_back(DOG_PLAYER_NAME);
	players.push_back(CAR_PLAYER_NAME);

	// Create the monopoly model
	Monopoly* monopoly = new Monopoly("Monopoly.txt", "seed.txt", players);

	// Start the simulation
	monopoly->StartSimulation(NUMBER_OF_TURNS);

	// Delete the object
	delete monopoly;
	system("pause");

    return 0;
}

