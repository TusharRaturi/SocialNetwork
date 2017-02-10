// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SocialNetwork.h"
#include <time.h>

bool StrcmpIgnoreCase(const string& str1, const string& str2)
{
	if (str1.size() != str2.size())
		return false;

	for (int x = 0, y = 0; x < (int)str1.length(); x++, y++)
		if (tolower((int)str1.at(x)) != tolower((int)str2.at(y)))
			return false;

	return true;
}

int main()
{
	//This sets the seed of the pseudo-random function according to the time
	srand((unsigned)time(NULL));

	cout << "Welcome to the GEU Social Network" << endl;

	int members = 0;
	cout << "Enter the number of members to put in the network." << endl;
	cin >> members;

	//Our Social Network!!
	SocialNetwork GEUSocNet(members);

	string in = "";
	bool hasRun = false;
	
	while (!hasRun)
	{
		cout << "Do you want to generate a random CSV File ?" << endl;
		cin >> in;
		if (StrcmpIgnoreCase(in, "y") || StrcmpIgnoreCase(in, "yes"))
		{
			bool chosenGraph = false;
			
			while (!chosenGraph)
			{
				cout << "Do you want a sparse graph or a dense graph ?" << endl;
				cin >> in;
				if (StrcmpIgnoreCase(in, "sparse"))
				{
					GEUSocNet.generateRandomCSV(true);
					hasRun = true;
					chosenGraph = true;
				}
				else if (StrcmpIgnoreCase(in, "dense"))
				{
					GEUSocNet.generateRandomCSV(false);
					hasRun = true;
					chosenGraph = true;
				}
				else
					cout << "Sorry, wrong input. Please enter sparse or dense.";
			}
		}
		else if (StrcmpIgnoreCase(in, "n") || StrcmpIgnoreCase(in, "no"))
		{
			cout << "Then enter the file name of the csv you want to load-->" << endl;
			cin >> in;
			GEUSocNet.fillFromFile(in);
			hasRun = true;
		}
		else
			cout << "Sorry, wrong input. Please enter yes or no.";
	}

	GEUSocNet.print();

	GEUSocNet.compareSizes();

	return 0;
}