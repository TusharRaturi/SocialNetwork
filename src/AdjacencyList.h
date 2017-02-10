#if _pragma_once_support
#pragma once
#endif

#include <string>
#include <fstream>

/*
* Linked List Node
*/
struct AdjacencyListNode
{
	int info;
	AdjacencyListNode* next;
};

/*
* Link List
*/
struct SubList
{
	AdjacencyListNode* head;
};

/*
* Adjacency List
*/
class AdjacencyList
{
public:
	
	//Constructor
	AdjacencyList(int size);
	
	//Destructor
	~AdjacencyList();

private:
	//This function creates a new node for the Adjacency List
	AdjacencyListNode* createNewNode(int info);

	//Joins two nodes together
	void addLink(int linkFrom, int linkTo);

public:
	//Prints the Adjacency List
	void printList();

	//Fills the list from a file
	bool fillFromFile(string filename);

	//Calculates the size of the list in Mega Bytes
	float calculateSizeInMB();

private:
	//Deletes a sub list
	void deleteSubList(AdjacencyListNode* head);

	//This variable stores the size of the adjacency list (or in other words the size of the linked list array)
	int sizeOfList;
	
	//This is the base address of the list or the address of the first list's base(or head) which in turn is a LinkedListNode
	SubList* adjacencyList;
};

