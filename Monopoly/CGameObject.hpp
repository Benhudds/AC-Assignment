#pragma once
#include <string>

const char POUND = 156;

using namespace std;

// CGameObject class
class CGameObject
{
	// Name data member
	string mName;
public:
	// Constructor
	CGameObject(string name) { mName = name; };

	// Getter for the mName data member
	string GetName() const { return mName; };
};