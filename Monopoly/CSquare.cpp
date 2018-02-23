#include "stdafx.h"
#include "CSquare.hpp"
#include "CPlayer.hpp"
#include "CGameObject.hpp"
#include <string>
#include <iostream>

using namespace std;

// Constructor
CSquare::CSquare(string name, ESquareType type) : CGameObject(name)
{
	mType = type;
}

// Method to perform the land actions for a CSquare
// Outputs the "<player> lands on <square>" message
void CSquare::Land(CPlayer* player)
{
	cout << player->GetName() + " lands on " + GetName() << endl;
}

// Method to get the ESquareType from an index
ESquareType EnumOfIndex(int i) { return static_cast<ESquareType>(i); }