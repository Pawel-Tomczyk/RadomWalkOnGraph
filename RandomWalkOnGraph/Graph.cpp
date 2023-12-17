#include "Graph.h"

Graph::Graph(std::vector<std::vector<double>> adjacencyMatrix)
{
	this->greedyChance = 1.0;
	this->size = adjacencyMatrix.size();
	for (int i = 0; i < this->size; i++)
	{
		if (adjacencyMatrix.size() != adjacencyMatrix[i].size()) {
			printf("Input matrix isn't quadratic. Sorry :(\n");
			exit(0);
		}
	}

	
	this->nodes.resize(this->size);

	for (int i = 0; i < this->size; i++)
	{
		std::vector<Node*> nodeInput;
		std::vector<double> floatInput;
		for (int j = 0; j < this->size; j++)
		{
			if (adjacencyMatrix[i][j] > 0) {
				nodeInput.push_back(&nodes[j]);
				floatInput.push_back(adjacencyMatrix[i][j]);
			}
		}
		Node node(i, nodeInput, floatInput);
		this->nodes[i] = node;
		if (nodeInput.size() == 0) 
		{
			this->endNodes.push_back(&nodes[i]);
		}
	}
	for (int i = 0; i < this->size; i++) 
	{
		bool isStartNode = true;
		for (int j = 0; j < this->size; j++) 
		{
			if (adjacencyMatrix[j][i] > 0)
			{
				isStartNode = false;
				break;
			}
		}
		if (isStartNode) {
			this->startingNodes.push_back(&nodes[i]);
		}
	}
}

void Graph::showGraph()
{
	for (int i = 0; i < this->size; i++)
	{
		std::cout << i << ": ";
		for (int j = 0; j < this->nodes[i].size; j++)
		{
			std::cout << this->nodes[i].edges[j].next->index << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "\tstaring: ";
	for (int i = 0; i < this->startingNodes.size(); i++)
	{
		std::cout << this->startingNodes[i]->index << " ";
	}
	std::cout << std::endl << "\tending: ";
	for (int i = 0; i < this->endNodes.size(); i++)
	{
		std::cout << this->endNodes[i]->index << " ";
	}
	std::cout << std::endl;
}

void Graph::showMatrixGraph()
{
	for (int i = 0; i < this->size; i++) {
		int h = 0;
		for (int j = 0; j < this->size; j++)
		{
			double write = 0;
			if(h < this->nodes[i].size)
				if (this->nodes[i].edges[h].next->index == j)
				{
					write = this->nodes[i].edges[h].probability;
					h++;
				}
			printf("%f ", write);
		}
		printf("\n");
	}
}

std::vector<std::vector<double>> Graph::matrixGraph() {
	std::vector<std::vector<double>> mG(this->size, std::vector<double>(this->size, 0.0));

	for (int i = 0; i < this->size; i++) {
		int h = 0;
		for (int j = 0; j < this->size; j++) {
			double write = 0.0;
			if (h < this->nodes[i].size) {
				if (this->nodes[i].edges[h].next->index == j) {
					write = this->nodes[i].edges[h].probability;
					h++;
				}
			}
			mG[i][j] = write;
		}
	}
	return mG;
}

void Graph::showStopien()
{
	int stop = 0;
	for (int i = 0; i < this->size - this->endNodes.size(); i++)
	{
		printf("%d: %d\n", i, this->nodes[i].size);
		stop += this->nodes[i].size;
	}
	printf("average = %d\n", stop / this->size);
}

std::vector<double> Graph::bruteForceStart(Node* start)
{
	std::vector<std::vector<double>> probabilities;
	for (int i = 0; i < this->size; i++)
	{
		std::vector<double> empty;
		probabilities.push_back(empty);
	}
	this->bruteForce(start, 1, probabilities);
	std::vector<double> odp;
	double sumB = 0;
	for (int i = 0; i < this->size; i++)
	{
		double sumA = 0;
		for (int j = 0; j < probabilities[i].size(); j++)
		{
			sumA += probabilities[i][j];
		}
		if (probabilities[i].size() != 0 || i >=(this->size - this->endNodes.size())) {
			//std::cout << i << ": " << sumA << std::endl;
			odp.push_back(sumA);
			sumB += sumA;
		}
	}
	//printf("\tsum: %f\n", sumB);
	return odp;
}

void Graph::bruteForce(Node* node, double chance, std::vector<std::vector<double>>& probabilities)
{
	if (node->size == 0) {
			probabilities[node->index].push_back(chance);
	}
	else {
		for (int i = 0; i < node->size; i++)
		{
			if (node->edges[i].used>0)
			{
				//printf("Graph->bruteForce->else{for}%d %d %d\n", i, node->index, node->edges[i].next->index);
				//node->edges[i].used -= 0.01;
				//if (fabs(node->edges[i].used) < 0.001) {
				//	printf("Cycle was cut!!!\n");
				//}
				this->bruteForce(node->edges[i].next, chance * node->edges[i].probability, probabilities);
				//node->edges[i].used += 0.01;
			}
		}
	}
}

std::vector<std::vector<double>> Graph::klasycznaMetodaMacierzowa()
{
	std::vector<std::vector<double>> x = this->matrixGraph();
	Eigen::MatrixXd matrixQ(this->size - this->endNodes.size(), this->size - this->endNodes.size());
	Eigen::MatrixXd matrixI(this->size - this->endNodes.size(), this->size - this->endNodes.size());
	Eigen::MatrixXd matrixT(this->size - this->endNodes.size(), this->endNodes.size());
	for (int i = 0; i < this->size - this->endNodes.size(); i++)
	{
		for (int j = 0; j < this->size - this->endNodes.size(); j++)
		{
			matrixQ(i, j) = x[i][j];
			if (i == j)matrixI(i, j) = 1.0;
			else matrixI(i, j) = 0.0;
		}
		for (int j = this->size - this->endNodes.size(); j < this->size; j++)
		{
			matrixT(i, j - this->size + this->endNodes.size()) = x[i][j];
		}
	}
	Eigen::MatrixXd matrixDifference = matrixI - matrixQ;
	Eigen::MatrixXd matrixM = matrixDifference.inverse();
	Eigen::MatrixXd matrixB = matrixM * matrixT;
	x.clear();
	for (int i = 0; i < matrixB.rows(); i++)
	{
		x.push_back(std::vector<double>());
		double sum = 0.0;
		//std::cout << "\n---------------" << i << "---------------\n";
		for (int j = 0; j < matrixB.cols(); j++)
		{
			//std::cout << this->endNodes[j]->index << ": " << matrixB(i, j) << std::endl;
			sum += matrixB(i, j);
			x[i].push_back(matrixB(i, j));
		}
		//std::cout << "\tsum: " << sum << std::endl;
		//printf("\tsum: %f\n", sum);
	}
	return x;
}

double Graph::greedyAnswer(Node* node)
{
	//printf("%d ", node->index);
	if (node->size == 0) 
	{
		//printf("\n");
		return node->index;
	}
	else 
	{
		double max = node->edges[0].probability;
		Node* next = node->edges[0].next;
		for (int i = 1; i < node->size; i++)
		{
			if (node->edges[i].probability > max)
			{
				max = node->edges[i].probability;
				next = node->edges[i].next;
			}
		}
		//printf("-> ");

		return this->greedyAnswer(next);
	}
}

std::vector<std::vector<double>> graphGenerator(int n, int f, int starting, int ending)
{
	int help = 0;
	srand(time(NULL));
	std::vector<std::vector<double>> graph;
	graph.resize(n);
	for (int i = 0; i < n; i++)
	{
		graph[i].resize(n);
		for (int j = 0; j < n; j++)
		{
			graph[i][j] = 0;
		}
	}
	
	if (n < starting + ending) {
		printf("Error: n is smaller than staring + ending");
		exit(0);
	}
	if (f > n - 1 -starting)f = n - 1;

	for (int i = 0; i < n - ending; i++)
	{
		std::vector<int> v;
		for (int j = starting; j < n; j++)
		{
			if (j != i) {
				v.push_back(j);
			}
		}
		v = randomFromVector(v, f);
		for (int j = 0; j < v.size(); j++)
		{
			graph[i][v[j]] = 1.0;
			if (v[j] >= n - ending)
			{
				graph[v[j]][i] = -1;
			}
		}
	}

	for (int i = starting; i < n; i++)
	{
		bool proper = false;
		for (int j = 0; j < n; j++)
		{
			if (graph[i][j] == -1)
			{
				proper = true;
				break;
			}
		}
		if (!proper)
		{
			int random_number = rand() % (n-ending);
			while (random_number == i) {
				random_number = rand() % (n - ending);
			}
			graph[random_number][i] = 1;
		}
	}

	removeEdge(graph, n, ending);
	removeCycle(graph, n, starting, ending, 1);
	while (removeCycle(graph, n, starting, ending, 1));

	for (int i = 0; i < n - ending; i++)
	{
		int m = 0;
		for (int j = starting; j < n; j++)
		{
			m+=graph[i][j];
		}
		if (m == 0) {
			int random_number = rand() % ending;
			random_number = n - ending;
			graph[i][random_number] = 1;
			m++;
		}
		std::vector<double> v = generateNumbers(m);
		int h = 0;
		for (int j = starting; j < n; j++)
		{
			if (graph[i][j] == 1)
			{
				graph[i][j] = v[h];
				h++;
			}
		}
	}

	return graph;
}

std::vector<int> randomFromVector(std::vector<int> v, int n) {
	if (n >= v.size()) {
		return v;
	}

	std::vector<int> x;
	std::uniform_int_distribution<int> distribution(0, v.size() - 1);

	for (int i = 0; i < n; i++) {
		int random_number = rand() % v.size();
		x.push_back(v[random_number]);
		v.erase(v.begin() + random_number);
	}

	return x;
}

std::vector<double> generateNumbers(int n) {
	using namespace std;
	if (n == 0) {
		std::cout << "Graph - GenerateNumbers - n == 0 - Blad\n";
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(0.0, 1.0);

	std::vector<double> numbers;
	for (int i = 0; i < n; i++) {
		double number = dis(gen) / n;
		numbers.push_back(number);
	}

	double sum = 0.0;
	for (double num : numbers) {
		sum += num;
	}
	double lastNumber = (1.0 - sum) / n;
	for (int i = 0; i < n; ++i) {
		numbers[i] += lastNumber;
	}
	double totalSum = 0;
	for (int i = 0; i < n; ++i) {
		totalSum += numbers[i];
	}
	return numbers;
}

bool removeCycle(std::vector<std::vector<double>>& graph, int n, int starting, int ending, bool kill) {
	std::vector<bool> visited(n, false);
	std::vector<bool> currentPath(n, false);
	bool isCycle = 0;

	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			if (detectCycle(i, graph, visited, currentPath, -1, starting, ending, kill)) {
				isCycle = 1;
			}
		}
	}
	return isCycle;
}

bool detectCycle(int node, std::vector<std::vector<double>>& graph, std::vector<bool>& visited, std::vector<bool>& currentPath, int parent, int starting, int ending, bool kill) {
	visited[node] = true;
	currentPath[node] = true;

	for (int i = 0; i < graph.size(); ++i) {
		if (graph[node][i] > 0) {
			if (!visited[i]) {
				if (detectCycle(i, graph, visited, currentPath, node, starting, ending, kill)) {
					return true;
				}
			}
			else if (currentPath[i] && i != parent) {
				if (kill) 
				if (kill) 
				{
					graph[node][i] = 0;
					int random_number = rand() % ending;
					random_number = graph.size() - ending;
					graph[node][random_number] = 1;
					random_number = rand() % starting;
					graph[random_number][i] = 1;
				}
				return true;
			}
		}
	}

	currentPath[node] = false;
	return false;
}

void removeEdge(std::vector<std::vector<double>>& graph, int n, int ending)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (graph[i][j] == 1 && graph[j][i] == 1)
			{
				graph[j][i] = 0;
				int random_number = rand() % ending;
				random_number = n - ending;
				graph[j][random_number] = 1;
			}
		}
	}
}
