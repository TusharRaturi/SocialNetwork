#include "stdafx.h"
#include "AdjacencyMatrix.h"


AdjacencyMatrix::AdjacencyMatrix(int size)
{
	sizeOfMat = size;

	matrix = new int*[size];

	for (int i = 0; i < size; i++)
	{
		matrix[i] = new int[size];

		for (int j = 0; j < size; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

void AdjacencyMatrix::add_link(int linkFrom, int linkTo)
{
	matrix[linkFrom][linkTo] = 1;
}

bool AdjacencyMatrix::fillFromFile(string filename)
{
	ifstream file(filename);
	string line;
	int height = 0;

	if (!file.is_open())
		return false;

	while (getline(file, line))
	{
		int width = 0;
		for (int j = 0; j < (int)line.length(); j++)
		{
			if (line.at(j) == '1')
				add_link(height, width);

			if (line.at(j) != ',' && line.at(j) != '\n')
				width++;
		}
		height++;
	}

	file.close();


	return true;
}

double AdjacencyMatrix::calculateSizeInMB()
{
	return ((float)sizeOfMat * (float)sizeOfMat * sizeof(int)) / 1024;
}

void AdjacencyMatrix::display()
{
	for (int i = 0; i < sizeOfMat; i++)
	{
		for (int j = 0; j < sizeOfMat; j++)
			cout << matrix[i][j] << "  ";
		cout << endl;
	}

	cout << endl;
}


AdjacencyMatrix::~AdjacencyMatrix()
{
	for (int i = 0; i < sizeOfMat; i++)
	{
		delete[] matrix[i];
	}

	delete[] matrix;
}
