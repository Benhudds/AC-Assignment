#include "stdafx.h"
#include "COwnableSquare.hpp"
#include "CSquare.hpp"
#include "CPlayer.hpp"
#include <iostream>

using namespace std;

// Constructor
COwnableSquare::COwnableSquare(string name, ESquareType type, int cost, int rent) : CSquare(name, type)
{
	mCost = cost;
	mRent = rent;

	// Initialise the owner as nullptr (unowned)
	mpOwner = nullptr;
}

// Method to perform the land actions for a COwnableSquare
// Purchases the property if possible
void COwnableSquare::Land(CPlayer* player)
{
	// Output the "<player> lands on <square>" message
	CSquare::Land(player);

	// If the square is unowned and the player has sufficient funds, purchase the property
	if (mpOwner == nullptr && player->AttemptPurchase(this))
	{
		mpOwner = player;
		cout << player->GetName() + " buys " + GetName() + " for " + POUND + to_string(mCost) << endl;
	}
	else if (mpOwner != nullptr && mpOwner == player)
	{
		cout << player->GetName() << " owns " << GetName() << endl;
	}
}
