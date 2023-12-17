#pragma once
#include "Edge.h"
#include <vector>

class Edge;

class Node
{
public:
	int index;
	std::vector<Edge> edges;
	int size;
	int sizeWithoutEdges;
	bool used;
	bool temp;//temporary (for example made by node.resize(...), then there's need to make object without proper constructor)
	Node();
	Node(int index, std::vector<Node*> nexts, std::vector<double> probabilities);
};