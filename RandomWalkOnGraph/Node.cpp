#include "Node.h"

Node::Node()
{
	this->temp = false;
	this->index = NULL;
	this->size = 0;
	this->edges.resize(0);
	this->used = true;
}

Node::Node(int index, std::vector<Node*> nexts, std::vector<double> probabilities) : index(index)
{
	this->used = false;

	if (nexts.size() != probabilities.size())
	{
		printf("There's sth wrong with data. Sorry :(\n");
		exit(0);
	}

	this->size = nexts.size();
	this->sizeWithoutEdges = this->size;

	double whole = 0;
	for (int i = 0; i < this->size; i++)
	{
		whole += probabilities[i];
	}
	//if ((whole > 1.01 || whole < 0.99) && whole > 0)
	//{
	//	printf("Probabilities doesn't add up. Sorry :(\n");
	//	exit(0);
	//}

	Edge x;
	x.used = 1;
	for (int i = 0; i < this->size; i++)
	{
		x.next = nexts[i];
		x.probability = probabilities[i];
		this->edges.push_back(x);
	}
	this->temp = false;
}