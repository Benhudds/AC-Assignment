#include "stdafx.h"
#include "CGroup.hpp"

// Constructor
CGroup::CGroup(int group)
{
	mGroup = group;
	mGroupSize = 0;
}

// Overloaded equality operator
// Return true if mGroup == group
bool CGroup::operator==(const CGroup &other) const
{
	return mGroup == other.GetGroup();
}