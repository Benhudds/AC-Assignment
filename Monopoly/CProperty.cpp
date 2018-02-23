#include "stdafx.h"
#include "CProperty.hpp"
#include <string>
#include <iostream>

using namespace std;

// Constructor
CProperty::CProperty(string name, ESquareType type, int cost, int rent, CGroup* group) : COwnableSquare(name, type, cost, rent)
{
	mGroup = group;

	// Initialise mortgaged to false
	mMortgaged = false;
}

// Method to perform the land actions for a CProperty
// Purchases a property if possible and pays rent if it is already owned and unmortgaged
void CProperty::Land(CPlayer* player)
{
	// Purchase the property if available
	COwnableSquare::Land(player);

	// Check if we should take rent
	if (GetOwner() != nullptr && GetOwner() != player && !mMortgaged)
	{
		// Check if we should take double rent
		// (all properties in this group are owned by the same player)
		if (GetOwner()->TakeDoubleRent(mGroup))
		{
			PayRent(player, 2 * GetRent());
		}
		else
		{
			PayRent(player, GetRent());
		}
	}
}

// Method to pay a given rent value to the given player
void CProperty::PayRent(CPlayer* player, int rent) const
{
	// Subtract the rent from the player and add it to the balance of the owner
	player->ChangeBalance(-rent);
	GetOwner()->ChangeBalance(rent);

	// Output the console message
	cout << player->GetName() << " pays " << POUND << to_string(rent) << endl;
}

// Method that returns a pointer to a CProperty object created using an input string read from a file
CProperty* CProperty::CreateProperty(string inputString, vector<CGroup*>* groups)
{
	// Start parsing the string from the third character, the first two are the type and space.
	int startPos = 2;
	int offset = startPos;
	char delimiter = ' ';

	// Find the name of the property. The name always has two parts separated by a space.
	offset = inputString.find(delimiter, offset);
	offset = inputString.find(delimiter, offset + 1);
	string name = inputString.substr(startPos, offset - 2);

	startPos = offset;

	// Find the cost of the property.
	offset = inputString.find(delimiter, offset + 1);
	int cost = atoi(inputString.substr(startPos, offset).c_str());

	startPos = offset;

	// Find the rent of the property.
	offset = inputString.find(delimiter, offset + 1);
	int rent = atoi(inputString.substr(startPos, offset).c_str());

	startPos = offset;

	// Find the group of the property.
	offset = inputString.find(delimiter, offset);
	int intGroup = atoi(inputString.substr(startPos, offset).c_str());

	// Get the group
	CGroup* group = GetGroupFromVector(intGroup, *groups);

	// Create the group if it does not already exist
	if (group == nullptr)
	{
		group = new CGroup(intGroup);
		groups->push_back(group);
	}

	// Add one to the group size
	group->SetGroupSize(group->GetGroupSize() + 1);

	return new CProperty(name, ESquareType::Property, cost, rent, group);
}

// Method that returns a pointer to the CGroup if it is in the groups vector, otherwise nullptr
CGroup* CProperty::GetGroupFromVector(int group, vector<CGroup*> groups)
{
	for (auto it = groups.begin(); it != groups.end(); ++it)
	{
		if ((*it)->GetGroup() == group)
		{
			return *it;
		}
	}

	return nullptr;
}

