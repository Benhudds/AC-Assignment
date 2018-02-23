#include "stdafx.h"
#include "CPlayer.hpp"
#include "CGameObject.hpp"
#include "COwnableSquare.hpp"
#include "CProperty.hpp"
#include <iostream>

using namespace std;

// Constructor
CPlayer::CPlayer(string name) : CGameObject(name)
{
	// Initialise balance to £1500
	mBalance = 1500;

	// Initialise position to 0
	mPosition = 0;
}

// Method that returns true if the player can/has purchased the square, false otherwise
bool CPlayer::AttemptPurchase(COwnableSquare* square)
{
	// Check if sufficient funds are available
	if (mBalance > 0)
	{
		// Deduct from balance
		ChangeBalance(-square->GetCost());

		// Add the square to the list of stored properties if it is a property
		if (square->GetType() == Property)
		{
			mOwnedProperties.push_back(static_cast<CProperty*>(square));
		}

		return true;
	}

	// Otherwise return false
	return false;
}

// Method to change the balance of this player by an amount
// Contains logic for the mortgaging of properties
void CPlayer::ChangeBalance(int amount)
{
	// Add the amount to the balance
	mBalance += amount;

	// If the player's balance is above 0 then we will buy back properties that are mortgaged
	// May buy back multiple properties during a turn
	if (!IsBust())
	{
		while (BuyMortgagedProperty())
		{
		}
	}
	// If the player's balance goes below 0 then we should mortgage a property
	// Will repeatedly mortgage properties until either the player is no longer bust,
	// or no more properties can be mortgaged
	while(IsBust())
	{
		if (!MortgageProperty())
		{
			return;
		}
	}
}

// Method that returns a pointer to the CProperty of the lowest value in the mOwnedProperties member variable
// The mortgaged parameter specifies if this property must be mortgaged (true) or un-mortgaged (false)
CProperty* CPlayer::FindLowestValueOwnedProperty(bool mortgaged)
{
	CProperty* lowestValueProperty = nullptr;

	// First, find the lowest value property that is not mortgaged
	// This list won't be ordered so will need to search the entire list
	for(auto it = mOwnedProperties.begin(); it != mOwnedProperties.end(); ++it)
	{
		// Check if mortgaged and the property is mortgaged, or not mortgaged and property not mortgaged
		// Overwrite if this is the first applicable property, or if the cost is less than the one previously stored
		if ((mortgaged && static_cast<CProperty*>(*it)->GetMortgaged() || !mortgaged && !static_cast<CProperty*>(*it)->GetMortgaged()) &&
			(lowestValueProperty == nullptr || static_cast<CProperty*>(*it)->GetCost() < lowestValueProperty->GetCost()))
		{
			lowestValueProperty = static_cast<CProperty*>(*it);
		}
	}	

	return lowestValueProperty;
}

// Method to re-purchase mortgaged properties
// Returns true if a property was purchased, false otherwise
// Re-purchases cheaper properties before more expensive ones
bool CPlayer::BuyMortgagedProperty()
{
	// Get a pointer to the lowest value property
	// If the pointer returned is nullptr, a mortgaged property was not found
	CProperty* lowestValueMortgagedProperty = FindLowestValueOwnedProperty(true);

	// Return if nullptr or re-purchasing the property will make the player bust
	if (lowestValueMortgagedProperty == nullptr || mBalance - lowestValueMortgagedProperty->GetCost() < 0)
	{
		return false;
	}

	// Re-purchase the proprety
	lowestValueMortgagedProperty->SetMortgaged(false);
	mBalance -= lowestValueMortgagedProperty->GetCost();

	cout << GetName() << " re-purchased " << lowestValueMortgagedProperty->GetName() << endl;

	return true;
}

// Method to mortgage properties
// Returns true if a property was successfully mortgaged, false otherwise
// Mortgages cheaper properties before more expensive ones
bool CPlayer::MortgageProperty()
{
	// Get a pointer to the lowest value property
	// If the pointer returned is nullptr, an un-mortgaged property was not found
	CProperty* lowestValueProperty = FindLowestValueOwnedProperty(false);

	// Return false if we could not find an unmortgaged property
	if (lowestValueProperty == nullptr)
	{
		return false;
	}

	// Set the property as mortgaged and credit the cost to the player
	lowestValueProperty->SetMortgaged(true);
	mBalance += lowestValueProperty->GetCost();

	cout << GetName() << " mortgaged " << lowestValueProperty->GetName() << endl;

	return true;
}

// Method that returns true if double rent should be taken for a property of a given group, false otherwise
bool CPlayer::TakeDoubleRent(CGroup* group)
{
	int count = 0;

	// Count the number of properties owned by this player that belong to the given group
	for(auto it = mOwnedProperties.begin(); it != mOwnedProperties.end(); ++it)
	{
		if (static_cast<CProperty*>(*it)->GetGroup() == group)
		{
			count++;
		}
	}

	// Return true if the player owns all the properties in this group
	return count == group->GetGroupSize();
}

// Method that returns true if the players balance is less than 0, false otherwise
bool CPlayer::IsBust() const
{
	return mBalance < 0;
}
