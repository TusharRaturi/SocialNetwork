#if _pragma_once_support
#pragma once
#endif

#include <string>
#include <fstream>

class AdjacencyMatrix
{
public:

	//Constructor
	AdjacencyMatrix(int size);
	
	//Destructor
	~AdjacencyMatrix();

	//Display the matrix
	void display();

	//Fills the list from a file
	bool fillFromFile(string filename);

	//Calculates the size of the list in Mega Bytes
	double calculateSizeInMB();

private:

	//The size of the matrix
	int sizeOfMat;

	//The matrix reference
	int **matrix;

	//adding link between two nodes
	void add_link(int linkFrom, int linkTo);
};

