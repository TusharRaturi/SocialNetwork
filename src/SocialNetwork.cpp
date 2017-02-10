#include "stdafx.h"
#include "SocialNetwork.h"

SocialNetwork::SocialNetwork(int members)
{
	if (members <= 0)
		handleException("Members less than or equal to zero.");
	
	numMembers = members;

	al = new AdjacencyList(getNumMembers());
	am = new AdjacencyMatrix(getNumMembers());
}

void SocialNetwork::fillFromFile(string filename)
{
	FILECHECK fc = correctFile(filename);

	switch (fc)
	{
		case FC_NOT_OPEN: handleException("Could not open the file.");
			break;

		case FC_MEMBER_MISMATCH: handleException("The members of the network of the file is different from that provided.");
			break;

		case FC_NOT_CSV: handleException("The file is not of the CSV format.");
			break;

		case FC_CORRECT: break;
	}

	if (!al->fillFromFile(filename))
		handleException("Could not open file.");

	if (!am->fillFromFile(filename))
		handleException("Could not open file.");
}

FILECHECK SocialNetwork::correctFile(string filename)
{
	ifstream file(filename);
	string line;
	int height = 0;

	if (!file.is_open())
		return FC_NOT_OPEN;

	while (getline(file, line))
	{
		int width = 0;
		for (unsigned j = 0; j < line.length(); j++)
		{
			if (line.at(j) != '1' && line.at(j) != '0' && line.at(j) != ',' && line.at(j) != '\n' && line.at(j) != EOF)
				return FC_NOT_CSV;
			
			if (line.at(j) == '1' || line.at(j) == '0')
				width++;

			if (j == line.length() - 1)
				if(!(line.at(j) == '0' || line.at(j) == '1' || line.at(j) == EOF))
					return FC_NOT_CSV;
		}

		if(width != getNumMembers())
			return FC_MEMBER_MISMATCH;
		
		height++;
	}

	file.close();

	if (height != getNumMembers())
	{
		return FC_MEMBER_MISMATCH;
	}

	return FC_CORRECT;
}

void SocialNetwork::generateRandomCSV(bool sparse)
{
	string filename = "SN_GENERATED.csv";
	ofstream ofs(filename, ofstream::out);
	
	char **mat = new char*[getNumMembers()];
	for (int i = 0; i < getNumMembers(); i++)
		mat[i] = new char[getNumMembers()];
	
	for (int i = 0; i < getNumMembers(); i++)
	{
		for (int j = 0; j < getNumMembers(); j++)
		{
			int median = 0;
			if (sparse)
				median = (RAND_MAX / 2) + (rand() / 4);
			else
				median = (RAND_MAX / 2) - (rand() / 4);

			if (rand() < median)
				mat[i][j] = mat[j][i] = '0';
			else
				mat[i][j] = mat[j][i] = '1';
		}
	}

	for (int i = 0; i < getNumMembers(); i++)
	{
		for (int j = 0; j < getNumMembers(); j++)
		{
			ofs << mat[i][j];

			if(j != getNumMembers() - 1)
				ofs << ',';
		}
		ofs << '\n';
	}

	for (int i = 0; i < getNumMembers(); i++)
	{
		delete[] mat[i];
	}

	delete[] mat;

	ofs.close();

	if (!al->fillFromFile(filename))
		handleException("Could not open file.");

	if (!am->fillFromFile(filename))
		handleException("Could not open file.");
}

void SocialNetwork::handleException(string exception)
{
	cout << exception << endl;
	getchar();
	exit(-1);
}

void SocialNetwork::compareSizes()
{
	cout << "The size of Adjacency List storage is: " << al->calculateSizeInMB() << " MB" << endl;
	cout << "The size of Adjacency Matrix  storage is: " << am->calculateSizeInMB() << " MB" << endl;
}

void SocialNetwork::print()
{
	cout << "The Adjacency List is: " << endl;
	al->printList();
	cout << "The Adjacency Matrix is: " << endl;
	am->display();
}

SocialNetwork::~SocialNetwork()
{
	delete al;
	delete am;
}