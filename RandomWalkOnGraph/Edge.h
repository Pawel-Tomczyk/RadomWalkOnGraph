#pragma once
#include "Node.h"
class Node;

class Edge
{
public:
	Node* next;
	double probability;
	double used;

	Edge();
};

