#pragma once
#include "CPlayer.hpp"
#include "COwnableSquare.hpp"

using namespace std;

// Const values for a RetailPark tile
const int RETAIL_PARK_COST = 200;
const int RETAIL_PARK_RENT = 10;
const string RETAIL_PARK_NAME = "Retail Park";

class CRetailPark : public COwnableSquare
{
public:
	// Constructor
	CRetailPark(string name, ESquareType type, int cost, int rent);

	// Static method to create and return a return park square
	static CRetailPark* CreateRetailPark();

	// Overriden land method for Retail Park tiles
	// Calls the OwnableSquare Land method and outputs the text specific to retail parks
	void Land(CPlayer* player) override;
};