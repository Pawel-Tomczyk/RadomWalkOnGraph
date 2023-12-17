#pragma once
#include "Node.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <queue>
#include <Eigen/Dense>

class Graph
{
private:
	double greedyChance;
public:
	std::vector<Node> nodes;
	int size;
	std::vector<Node*> endNodes;
	std::vector<Node*> startingNodes;
	Graph(std::vector<std::vector<double>> adjacencyMatrix);//adjacency matrix NxN
	void showGraph();
	void showMatrixGraph();
	std::vector<std::vector<double>> matrixGraph();
	void showStopien();
	std::vector<double> bruteForceStart(Node* start);
	void bruteForce(Node* node, double chance, std::vector<std::vector<double>>& probabilities);
	std::vector<std::vector<double>> klasycznaMetodaMacierzowa();//z ksi¹¿ki
	double greedyAnswer(Node* node);
};

std::vector<std::vector<double>> graphGenerator(int n, int f, int starting, int ending);
std::vector<int> randomFromVector(std::vector<int> v, int n);
std::vector<double> generateNumbers(int n);
bool removeCycle(std::vector<std::vector<double>>& graph, int n, int starting, int ending, bool kill);
bool detectCycle(int node, std::vector<std::vector<double>>& graph, std::vector<bool>& visited, std::vector<bool>& currentPath, int parent, int starting, int ending, bool kill);
void removeEdge(std::vector<std::vector<double>>& graph, int n, int ending);