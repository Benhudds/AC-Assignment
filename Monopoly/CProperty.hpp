#pragma once
#include "CPlayer.hpp"
#include "COwnableSquare.hpp"
#include "CGroup.hpp"

using namespace std;

// CProperty class used to represent a property
class CProperty : public COwnableSquare
{
	// Group data member
	CGroup* mGroup;

	// Mortgaged data member
	bool mMortgaged;

	// Method to pay rent of a given amount to the specified player
	void PayRent(CPlayer* player, int rent) const;
public:
	// Constructor
	CProperty(string name, ESquareType type, int cost, int rent, CGroup* group);

	// Getter for the mGroup data member
	CGroup* GetGroup() const { return mGroup; }

	// Getter for the mMortgaged data member
	bool GetMortgaged() const { return mMortgaged; }

	// Setter for the mMortgaged data member
	void SetMortgaged(bool mortgaged) { mMortgaged = mortgaged; }

	// Overriden land method for Property tiles
	// Calls the OwnableSquare Land method and outputs the text specific to properties 
	void Land(CPlayer* player) override;

	// Static method to create a property object from an input string
	static CProperty* CreateProperty(string inputString, vector<CGroup*>* groups);

	// Static method to get the CGroup object of the given group from the given vector
	static CGroup* GetGroupFromVector(int group, vector<CGroup*> groups);
};