#pragma once
#include "CSquare.hpp"
#include "CProperty.hpp"
#include <vector>

using namespace std;

// Constant values for the number of turns and player names
const int NUMBER_OF_TURNS = 20;
const string DOG_PLAYER_NAME = "dog";
const string CAR_PLAYER_NAME = "car";

// Constant char array size used in reading from files
const int CHAR_ARRAY_SIZE = 256;

// Typedefs of vectors of CSquares, CPlayers and CGroups
typedef vector<CSquare*> SquareList;
typedef vector<CPlayer*> PlayerList;
typedef vector<CGroup*> GroupList;

class Monopoly
{
	// Vector data member that contains a list of game squares
	SquareList mSquareList;

	// Vector data member that contains a list of players
	PlayerList mPlayerList;

	// Vector data member that contains a list of property groups
	GroupList mGroupList;

	// Boolean data member that prevents execution if the class has not been initialised correctly
	bool mInitialised;
	
	// Method used to load the game squares from the file given.
	bool LoadSquares(string fileName);

	// Method use to load the seed from the file given.
	bool LoadSeed(string seedFileName) const;
public:
	// Constructor
	Monopoly(string fileName, string seedFileName, vector<string> players);

	// Destructor
	~Monopoly();

	// Method to run the monopoly simulation for the given number of turns
	void StartSimulation(int numberOfTurns);
};