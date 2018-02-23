#pragma once

// CGroup class used to store property group information
class CGroup
{
	// The number (colour) group the property belongs to
	int mGroup;
	
	// The amount of properties in this group
	int mGroupSize;
public:
	// Constructor
	CGroup(int group);

	// Getter for the mGroupSize data member
	int GetGroupSize() const { return mGroupSize; }

	// Setter for the mGroupSize data member
	void SetGroupSize(int groupSize) { mGroupSize = groupSize; }

	// Getter for the mGroup data member
	int GetGroup() const { return mGroup; }

	// == Operator implementation that checks the mGroup data members for equality
	bool operator==(const CGroup &other) const;
};
