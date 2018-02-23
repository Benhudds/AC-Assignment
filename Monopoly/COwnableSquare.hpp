#pragma once
#include "CSquare.hpp"
#include "CPlayer.hpp"

using namespace std;

// COwnable class used to represent a square which can be owned
class COwnableSquare : public CSquare
{
	// Data member that stores a pointer to the owner of this square
	CPlayer* mpOwner;

	// Rent datamember
	int mRent;

	// Cost datamember
	int mCost;
public:
	// Constructor
	COwnableSquare(string name, ESquareType type, int cost, int rent);

	// Getter for the mpOwner data member
	CPlayer* GetOwner() const { return mpOwner; };

	// Getter for the mRent data member
	int GetRent() const { return mRent; };

	// Getter for the mCost data member
	int GetCost() const { return mCost; };

	// Overriden land method for ownable tiles
	// Player purchases tile if not already owned and has sufficient funds
	void Land(CPlayer* player) override;
};