#pragma once
#include "CGameObject.hpp"
#include "CSquare.hpp"
#include "CGroup.hpp"
#include <vector>

using namespace std;

// Forward declaration of COwnableSquare and CProperty
class COwnableSquare;
class CProperty;

// Typedef of a vector of CProperties
typedef vector<CProperty*> PropertiesList;

// Class used to represent a player
class CPlayer : public CGameObject
{
	// Current position of the player on the game board
	int mPosition;

	// Balace data member
	int mBalance;

	// Vector of squares that the player owns
	PropertiesList mOwnedProperties;

	// Method to mortgaged a property
	bool MortgageProperty();

	// Method to re-purchase a mortgaged property
	bool BuyMortgagedProperty();

	// Method to find the lowest value property that is mortgaged or un-mortgaged
	CProperty* FindLowestValueOwnedProperty(bool mortgaged);
public:
	// Constructor
	CPlayer(string name);

	// Getter for the mPosition data member
	int GetPosition() const { return mPosition; };

	// Setter for the mPosition data member
	void SetPosition(int pos) { mPosition = pos; };

	// Getter for the mBalance data member
	int GetBalance() const { return mBalance; };

	// Getter for the mOwnedProperties data member
	vector<CProperty*> GetOwnedProperties() const { return mOwnedProperties; };

	// Method to subtract from or add and amount to the mBalance data member
	void ChangeBalance(int amount);

	// Method to attempt to purchase a square
	// Returns true if purchased, false if not
	bool AttemptPurchase(COwnableSquare* square);

	// Method to check if double rent should be taken
	// ie. all the properties in the group are owned by this player
	bool TakeDoubleRent(CGroup* group);

	// Method that checks if the player is bust
	bool IsBust() const;
};