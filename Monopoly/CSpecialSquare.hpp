#pragma once
#include "CSquare.hpp"

using namespace std;

// Const values for the Go and Jail amounts
const int GO_BONUS = 200;
const int JAIL_PENALTY = 50;

// Enumeration of possible bonuses
enum EBonusType
{
	FindMoney = 20,
	WinCompetition = 50,
	TaxRebate = 100,
	WinLottery = 150,
	Bequest = 200,
	Birthday = 300
};

// Enumeration of possible penalties
enum EPenaltyType
{
	FoodBill = 20,
	PhoneBill = 50,
	HeatingBill = 100,
	VehicleTax = 150,
	FuelBill = 200,
	WindfallTax = 300,
};

class CSpecialSquare : public CSquare
{
	// Method to process a bonus for the given player
	void ProcessBonus(CPlayer* player, int bonus) const;

	// Method to process a penalty for the given player
	void ProcessPenalty(CPlayer* player, int penalty) const;
public:
	// Constructor
	CSpecialSquare(string name, ESquareType type) : CSquare(name, type) { };

	// Overriden land method for special tiles
	void Land(CPlayer* player) override;

	// Static method to create a special square object from an input string
	static CSpecialSquare* CreateSquare(string inputString);
};