#include "stdafx.h"
#include "COwnableSquare.hpp"
#include "CRetailPark.hpp"
#include <iostream>

// Constructor
CRetailPark::CRetailPark(string name, ESquareType type, int cost, int rent) : COwnableSquare(name, type, cost, rent)
{
	// Simply call the base COwnableSquare constructor
}

// Method to perform the land actions for a CRetailPark
void CRetailPark::Land(CPlayer* player)
{
	COwnableSquare::Land(player);

	// Check if the property is owned by another player
	if (GetOwner() != nullptr && GetOwner() != player)
	{
		// Take the rent from the player
		player->ChangeBalance(-GetRent());
		GetOwner()->ChangeBalance(GetRent());
		cout << player->GetName() + " pays " + POUND + to_string(GetRent()) + " of goods" << endl;
	}
}

// Method that returns a pointer to a new CRetailPark object
CRetailPark* CRetailPark::CreateRetailPark()
{
	return new CRetailPark(RETAIL_PARK_NAME, ESquareType::RetailPark, RETAIL_PARK_COST, RETAIL_PARK_RENT);
}