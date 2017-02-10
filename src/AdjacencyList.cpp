#include "stdafx.h"
#include "AdjacencyList.h"


AdjacencyList::AdjacencyList(int size)
{
	sizeOfList = size;

	adjacencyList = new SubList[size];

	for (int i = 0; i < size; i++)
	{
		adjacencyList[i].head = nullptr;
	}
}

AdjacencyListNode* AdjacencyList::createNewNode(int info)
{
	AdjacencyListNode* newNode = new AdjacencyListNode;
	newNode->info = info + 1;
	newNode->next = nullptr;
	return newNode;
}

void AdjacencyList::addLink(int linkFrom, int linkTo)
{
	AdjacencyListNode* newNode = createNewNode(linkTo);
	newNode->next = adjacencyList[linkFrom].head;
	adjacencyList[linkFrom].head = newNode;
	newNode = createNewNode(linkFrom);
	newNode->next = adjacencyList[linkTo].head;
	adjacencyList[linkTo].head = newNode;
}

void AdjacencyList::printList()
{
	for (int node = 0; node < sizeOfList; ++node)
	{
		AdjacencyListNode* chain = adjacencyList[node].head;
		
		cout << "\nFriend list of student " << node + 1 << "\nhead ";
		
		while(chain)
		{
			cout << "-> " << chain->info;
			chain = chain->next;
		}
		
		cout << endl;
	}

	cout << endl;
}

bool AdjacencyList::fillFromFile(string filename)
{
	ifstream file;
	file.open(filename, ios::in);

	if (!file.is_open())
		return false;

	char my_character;

	int i = 0, j = 0;

	while (!file.eof())
	{
		file.get(my_character);
		if (my_character == '\n')
		{
			i++;
			j = i;
			for (int k = 0; k<2 * i; k++)
				file.get(my_character);
		}
		else if (my_character == '1')
		{
			addLink(i, j);
			j++;
		}
		else if (my_character != ',')
			j++;
	}
	file.close();

	return true;
}

float AdjacencyList::calculateSizeInMB()
{
	float sizeOfAdjList = 0;

	for (int i = 0; i < sizeOfList; ++i)
	{
		AdjacencyListNode* chain = adjacencyList[i].head;

		while (chain)
		{
			sizeOfAdjList += sizeof(AdjacencyListNode);
			chain = chain->next;
		}
	}

	sizeOfAdjList += (sizeOfList * sizeof(SubList));
	
	return sizeOfAdjList /= 1024;
}

void AdjacencyList::deleteSubList(AdjacencyListNode* head)
{
	if (head->next == nullptr)
	{
		delete head;
		return;
	}
	else
		deleteSubList(head->next);
}

AdjacencyList::~AdjacencyList()
{
	for (int i = 0; i < sizeOfList; i++)
	{
		AdjacencyListNode* chain = adjacencyList[i].head;
		if(chain)
			deleteSubList(chain);
	}
}
