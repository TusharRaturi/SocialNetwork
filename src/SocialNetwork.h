#if _pragma_once_support
#pragma once
#endif

#include "stdafx.h"
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include <sstream>

enum FILECHECK
{
	FC_NOT_OPEN,
	FC_NOT_CSV,
	FC_MEMBER_MISMATCH,
	FC_CORRECT
};

class SocialNetwork
{
public:
	//Constructor
	SocialNetwork(int members);

	//Destructor
	~SocialNetwork();

	//Getter for number of members
	int getNumMembers() { return numMembers; }

	//Prints the lista adn the matrix representation of the data
	void print();

	//Prints the sizes of both the representations
	void compareSizes();

	void fillFromFile(string filename);

	//Generate a random CSV delimited Social Network
	void generateRandomCSV(bool sparse);

private:
	//Checks weather the file is correct
	FILECHECK correctFile(string filename);

	//Handles exceptions
	void handleException(string exception);

	//The number of members in the network
	int numMembers;

	AdjacencyList* al;
	AdjacencyMatrix* am;
};