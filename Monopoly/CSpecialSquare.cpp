#include "stdafx.h"
#include "CSquare.hpp"
#include "CSpecialSquare.hpp"
#include "CPlayer.hpp"
#include "Random.hpp"

// Method to perform the land actions for a CSpecialSquare
void CSpecialSquare::Land(CPlayer* player)
{
	// Output the "<player> lands on <square>" message
	CSquare::Land(player);

	// Perform action based on the type of the square
	switch(GetType())
	{
	case Go:
		cout << player->GetName() << " is resting" << endl;
		break;
	case FreeParking:
		cout << player->GetName() << " is resting" << endl;
		break;
	case Jail:
		cout << player->GetName() << " is just visiting" << endl;
		break;
	case GoToJail:
		cout << player->GetName() << " goes to Jail" << endl;
		cout << player->GetName() << " pays " << POUND << JAIL_PENALTY << endl;

		// Decrease balance by 50
		player->ChangeBalance(-JAIL_PENALTY);
		break;
	case Bonus:
		// Give the player a random bonus
		ProcessBonus(player, Random());
		break;
	case Penalty:
		// Give the player a random penalty
		ProcessPenalty(player, Random());
		break;
	default:
		break;
	}
}

// Method to give the player a specified bonus
void CSpecialSquare::ProcessBonus(CPlayer* player, int bonus) const
{
	switch (bonus)
	{
	case 1:
		cout << "Find some money. Player gains " << POUND << FindMoney << endl;
		player->ChangeBalance(FindMoney);
		break;
	case 2:
		cout << "Win competition. Player gains " << POUND << WinCompetition << endl;
		player->ChangeBalance(WinCompetition);
		break;
	case 3:
		cout << "Tax rebate. Player gains " << POUND << TaxRebate << endl;
		player->ChangeBalance(TaxRebate);
		break;
	case 4:
		cout << "Win lottery. Player gains " << POUND << WinLottery << endl;
		player->ChangeBalance(WinLottery);
		break;
	case 5:
		cout << "Bequest. Player gains " << POUND << Bequest << endl;
		player->ChangeBalance(Bequest);
		break;
	case 6:
		cout << "Birthday. Player gains " << POUND << Birthday << endl;
		player->ChangeBalance(Birthday);
		break;
	default:
		break;
	}
}

// Method to give the player a specified penalty
void CSpecialSquare::ProcessPenalty(CPlayer* player, int penalty) const
{
	switch (penalty)
	{
	case 1:
		cout << "Pay food bill. Player loses " << POUND << FoodBill << endl;
		player->ChangeBalance(-FoodBill);
		break;
	case 2:
		cout << "Pay phone bill. Player loses " << POUND << PhoneBill << endl;
		player->ChangeBalance(-PhoneBill);
		break;
	case 3:
		cout << "Pay heating bill. Player loses " << POUND << HeatingBill << endl;
		player->ChangeBalance(-HeatingBill);
		break;
	case 4:
		cout << "Pay vehicle tax. Player loses " << POUND << VehicleTax << endl;
		player->ChangeBalance(-VehicleTax);
		break; 
	case 5:
		cout << "Pay fuel bill. Player loses " << POUND << FuelBill << endl;
		player->ChangeBalance(-FuelBill);
		break;
	case 6:
		cout << "Pay windfall tax. Player loses " << POUND << WindfallTax << endl;
		player->ChangeBalance(-WindfallTax);
		break;
	default:
		break;
	}
}

// Method that returns a pointer to a new CSpecialSquare object created using the given input string
CSpecialSquare* CSpecialSquare::CreateSquare(string inputString)
{
	// Get the name of the special square
	// Used when printing the square the player has landed on
	string name = inputString.substr(2, inputString.length());
	return new CSpecialSquare(name, EnumOfIndex(inputString[0] - '0'));
}