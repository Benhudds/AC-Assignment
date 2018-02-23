#pragma once
#include "CGameObject.hpp"

using namespace std;

// Forward declaration of CPlayer
class CPlayer;

// Enumeration of possible monopoly squares
enum ESquareType
{
	Property = 1,
	Go = 2,
	RetailPark = 3,
	Bonus = 4,
	Penalty = 5,
	Jail = 6,
	GoToJail = 7,
	FreeParking = 8
};

// Method that returns the ESquareType with the given index
ESquareType EnumOfIndex(int i);

// Class to represent a generic square in the monopoly board
class CSquare : public CGameObject
{
	// Enumerated type that identifies which kind of square this is
	ESquareType mType;
public:
	// Constructor
	CSquare(string name, ESquareType type);

	// Getter for the mType data member
	ESquareType GetType() const { return mType; };

	// Virtual method to land on the square
	virtual void Land(CPlayer* player);
};
