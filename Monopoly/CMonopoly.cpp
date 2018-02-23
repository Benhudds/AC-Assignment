#include "stdafx.h"
#include "CMonopoly.hpp"
#include "CSpecialSquare.hpp"
#include "CProperty.hpp"
#include <fstream>
#include "CRetailPark.hpp"
#include "Random.hpp"

// Constructor
Monopoly::Monopoly(string fileName, string seedFileName, vector<string> players)
{
	mInitialised = false;

	// Load the squares from the file
	// Create the players and update the properties if the squares are loaded correctly
	if (LoadSquares(fileName) && LoadSeed(seedFileName))
	{
		for(auto it = players.begin(); it != players.end(); ++it)
		{
			mPlayerList.push_back(new CPlayer(*it));
		}

		mInitialised = true;
	}
}

// Destructor
Monopoly::~Monopoly()
{
	// Delete the players
	for(auto it = mPlayerList.begin(); it != mPlayerList.end(); ++it)
	{
		delete *it;
	}

	mPlayerList.clear();

	// Delete the squares
	for(auto it = mSquareList.begin(); it != mSquareList.end(); ++it)
	{
		delete *it;
	}

	mSquareList.clear();

	// Delete the groups
	for(auto it = mGroupList.begin(); it != mGroupList.end(); ++it)
	{
		delete *it;
	}

	mGroupList.clear();
}

// Run the monopoly simulation for the given number of turns
void Monopoly::StartSimulation(int numberOfTurns)
{
	// Check if the monopoly object was constructed correctly
	// If not, output an error messaged and return
	if (!mInitialised)
	{
		cout << "Monopoly was not initialised correctly, can not be run" << endl;
		return;
	}

	cout << "Welcome to Monopoly" << endl << endl;

	// Repeat until there is only one player remaining, or the number of turns has been reached
	for (int i = 0; i < numberOfTurns; ++i)
	{
		for (auto player = mPlayerList.begin(); player != mPlayerList.end(); ++player)
		{
			// Get a random number for the player to move
			// Should be a modulus of the square list size
			int ran = Random();
			int mov = ran;

			cout << (*player)->GetName() << " rolls " << mov << endl;
			
			// Add the player's current position to the roll
			mov += (*player)->GetPosition();

			// Check if the player has passed the end of the board, move back to the start if so
			if (mov >= mSquareList.size())
			{
				cout << (*player)->GetName() << " passes GO and collects " << POUND << GO_BONUS << endl;
				(*player)->ChangeBalance(GO_BONUS);

				// Use the remainder of an integer division by the size so the position is always in range
				mov %= mSquareList.size();
			}

			// Move to the randomly selected square
			mSquareList[mov]->Land(*player);
			(*player)->SetPosition(mov);

			// If the player has landed on the GoToJail square then move them to Jail
			if (mSquareList[mov]->GetType() == GoToJail)
			{
				// Find the Jail square
				for (int j = 0; j < mSquareList.size(); j++)
				{
					if (mSquareList[j]->GetType() != Jail)
					{
						continue;
					}
					
					(*player)->SetPosition(j);
					break;
				}
			}

			// Output player balance
			cout << (*player)->GetName() << " has " << POUND << (*player)->GetBalance() << endl;
		}

		cout << endl;
	}
}

// Method to create the square objects from a file with the given name
bool Monopoly::LoadSquares(string fileName)
{
	// Create an input filestream for reading the Square setup file.
	ifstream file;
	try
	{
		file.open(fileName);

		char* string = new char[CHAR_ARRAY_SIZE];

		while (file.getline(string, CHAR_ARRAY_SIZE))
		{
			// Take the first character as the square type, use this to create the correct square
			switch (string[0] - '0')
			{
			case Property:
				mSquareList.push_back(CProperty::CreateProperty(string, &mGroupList));
				break;
			case RetailPark:
				mSquareList.push_back(CRetailPark::CreateRetailPark());
				break;
			default:
				mSquareList.push_back(CSpecialSquare::CreateSquare(string));
				break;
			}
		}
		
		file.close();
	}
	catch (...)
	{
		cout << "Could not load Monopoly file: " << fileName << endl;
		return false;
	}

	return true;
}

bool Monopoly::LoadSeed(string fileName) const
{
	// Create an input filestream for reading the Square setup file.
	ifstream file;
	try
	{
		file.open(fileName);

		char* string = new char[CHAR_ARRAY_SIZE];
		file.getline(string, CHAR_ARRAY_SIZE);

		srand(stoi(string));

		file.close();
	}
	catch (...)
	{
		cout << "Could not load seed file: " << fileName << endl;
		return false;
	}

	return true;
}
