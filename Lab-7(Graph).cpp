#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <list>

using namespace std;

class MySquadMatrix {
private:
	int** squadMatrix;
	int size;
public:
	MySquadMatrix();
	MySquadMatrix(int);
	~MySquadMatrix();
	void resize(int);
	int** getMatrix() { return squadMatrix; }
	int getSize() { return size; }
	MySquadMatrix& operator=(const MySquadMatrix &);
};

MySquadMatrix::MySquadMatrix() {
	squadMatrix = nullptr;
	size = 0;
}

MySquadMatrix::MySquadMatrix(int size)
{
	squadMatrix = new int* [size];
	for (int i = 0; i < size; i++) {
		squadMatrix[i] = new int[size];
	}
	this->size = size;
}

MySquadMatrix::~MySquadMatrix()
{
	for (int i = 0; i < size; i++) {
		delete[] squadMatrix[i];
	}
	delete[] squadMatrix;
}

void MySquadMatrix::resize(int size) {
	if (!size) {
		squadMatrix = nullptr;
		return;
	}
	int** newSquad = new int* [size];
	for (int i = 0; i < size; i++) {
		newSquad[i] = new int[size];
	}
	if (!this->size) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				newSquad[i][j] = 0;
			}
		}
		squadMatrix = newSquad;
		this->size = size;
		return;
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i < this->size && j < this->size) {
				newSquad[i][j] = squadMatrix[i][j];
			}
			else {
				newSquad[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < this->size; i++) {
		delete[] squadMatrix[i];
	}delete[] squadMatrix;
	squadMatrix = newSquad;
	this->size = size;
}

MySquadMatrix& MySquadMatrix::operator=(const MySquadMatrix &other)
{
	if (other.size) {
		this->squadMatrix = nullptr;
	}
	int** newSquad = new int* [other.size];
	for (int i = 0; i < size; i++) {
		newSquad[i] = new int[other.size];
	}
	for (int i = 0; i < other.size; i++) {
		for (int j = 0; j < other.size; j++) {
			newSquad[i][j] = other.squadMatrix[i][j];
		}
	}
	for (int i = 0; i < this->size; i++) {
		delete[] squadMatrix[i];
	}
	delete[] squadMatrix;
	squadMatrix = newSquad;
	this->size = size;

	return *this;
}

class GraphElement {
public:
	int weigth;
	int vertex;
	bool passed;
	GraphElement(int weigth = 0, int vertex = 0, bool passed = false) {
		this->weigth = weigth;
		this->vertex = vertex;
		this->passed = passed;
	}
};

class Graph {
private:
	int vertices;
	MySquadMatrix adjacencyMatrix;
	MySquadMatrix weightMatrix;
	MySquadMatrix roadMatrix;
public:
	Graph();
	int getVertices() { return vertices; }
	void insert(int*, int*, int);
	void randomGraph(int);
	void labGraph();
	void showGraph();
	void showGraphWeight();
	void showGraphRoad();
	void searchInWidth();
	void searchInDepth();
	int DijkstraAlgorithm(int, int);
	int sumWeigth();
	void FloydAlgoithm();
};

Graph::Graph()
{
	vertices = 0;
	adjacencyMatrix.resize(0);
	weightMatrix.resize(0);
	roadMatrix.resize(0);
}

void Graph::insert(int* ArrayOfVertices = nullptr, int* ArrayOfWeights = nullptr, int size = 0)
{
	int count = 0;
	if (++vertices == 1) {
		adjacencyMatrix.resize(1);
		adjacencyMatrix.getMatrix()[0][0] = 0;
		return;
	}
	adjacencyMatrix.resize(vertices);
	if (!ArrayOfVertices && !ArrayOfWeights) {
		for (int i = 0; i < 1; i++) {
			for (int j = 0; j < vertices; j++) {
				adjacencyMatrix.getMatrix()[vertices - 1][j] = adjacencyMatrix.getMatrix()[j][vertices - 1] = 0;
			}
			return;
		}
	}
	for (int i = 0; i < vertices; i++) {
		for (int k = 0; k < size; k++) {
			if (i == ArrayOfVertices[k]) {
				adjacencyMatrix.getMatrix()[vertices - 1][i] = adjacencyMatrix.getMatrix()[i][vertices - 1] = ArrayOfWeights[count];
				count++;
			}
			else {
				if (adjacencyMatrix.getMatrix()[vertices - 1][i] != ArrayOfWeights[count - 1])
					adjacencyMatrix.getMatrix()[vertices - 1][i] = adjacencyMatrix.getMatrix()[i][vertices - 1] = 0;
			}
		}
	}
}

void Graph::randomGraph(int size)
{
	adjacencyMatrix.resize(size);
	srand(time(NULL));
	int count = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < i + 1; j++) {
			if (j == i) {
				adjacencyMatrix.getMatrix()[i][j] = 0;
				count++;
				continue;
			}
			if (count % 3 == 0) {
				adjacencyMatrix.getMatrix()[i][j] = adjacencyMatrix.getMatrix()[j][i] = rand() % 30 + 1;
				count++;
				continue;
			}
			else {
				adjacencyMatrix.getMatrix()[i][j] = adjacencyMatrix.getMatrix()[j][i] = 0;
				count++;
			}
		}
	}
	this->vertices = size;
}

void Graph::labGraph()
{
	int staticMatrix[17][17] = {
		//	 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16
			{0, 4, 7, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//0
			{4, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//1
			{7, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0},//2
			{3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0},//3
			{0, 2, 2, 0, 0, 0, 4, 0, 0, 0, 7, 0, 0, 8, 0, 8, 0},//4
			{0, 0, 0, 0, 0, 0, 0, 7, 3, 0, 0, 0, 1, 9,11, 0, 0},//5
			{0, 0, 0, 0, 4, 0, 0, 0, 4, 0, 6, 0, 0, 0, 0, 0, 0},//6
			{0, 0, 0, 0, 0, 7, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0},//7
			{0, 0, 0, 0, 0, 3, 4, 0, 0, 3, 0, 0, 9, 0, 0,15, 0},//8
			{0, 0, 0, 0, 0, 0, 0, 5, 3, 0, 0, 0, 2, 0, 3, 0,12},//9
			{0, 0, 2, 7, 7, 0, 6, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0},//10
			{0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 4, 0, 0, 0, 0, 0, 0},//11
			{0, 0, 0, 0, 0, 1, 0, 0, 9, 2, 0, 0, 0, 0, 0, 0,11},//12
			{0, 0, 0, 0, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},//13
			{0, 0, 0, 0, 0,11, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 8},//14
			{0, 0, 0, 0, 8, 0, 0, 0,15, 0, 0, 0, 0, 1, 0, 0, 0},//15
			{0, 0, 0, 0, 0, 0, 0, 0, 0,12, 0, 0,11, 0, 8, 0, 0},//16
	};
	adjacencyMatrix.resize(17);
	vertices = adjacencyMatrix.getSize();
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			adjacencyMatrix.getMatrix()[i][j] = staticMatrix[i][j];
		}
	}
}

void Graph::showGraph()
{
	cout << "Matrix of adjacent: " << endl;
	for (int i = 0; i < vertices; i++) {
		if (!i) cout << "	";
		cout << setw(5) << left << i;
	}
	cout << endl << endl;
	for (int i = 0; i < vertices; i++) {
		cout << i << "	";
		for (int j = 0; j < vertices; j++) {
			cout << setw(5) << left << adjacencyMatrix.getMatrix()[i][j];
		}
		cout << endl;
	}
}

void Graph::showGraphWeight()
{
	cout << "Weight matrix: " << endl;
	for (int i = 0; i < vertices; i++) {
		if (!i) cout << "	";
		cout << setw(5) << left << i;
	}
	cout << endl << endl;
	for (int i = 0; i < vertices; i++) {
		cout << i << "	";
		for (int j = 0; j < vertices; j++) {
			cout << setw(5) << left << weightMatrix.getMatrix()[i][j];
		}
		cout << endl;
	}
}

void Graph::showGraphRoad()
{
	cout << "Road matrix: " << endl;
	for (int i = 0; i < vertices; i++) {
		if (!i) cout << "	";
		cout << setw(5) << left << i;
	}
	cout << endl << endl;
	for (int i = 0; i < vertices; i++) {
		cout << i << "	";
		for (int j = 0; j < vertices; j++) {
			cout << setw(5) << left << roadMatrix.getMatrix()[i][j];
		}
		cout << endl;
	}
}

void Graph::searchInWidth()
{
	list<int> tempList_1;
	list<int> passedVertices;
	int count = 0, temp;
	cout << "Input from which element you will start: "; cin >> temp;
	passedVertices.push_back(temp);
	for (int i = temp; count < vertices; count++) {
		for (int j = 0; j < vertices; j++) {
			if (adjacencyMatrix.getMatrix()[i][j] != 0) {
				tempList_1.push_back(j);
			}
		}
		for (auto it = tempList_1.begin(); it != tempList_1.end(); it++) {
			bool flag_3 = true;
			for (auto it2 = passedVertices.begin(); it2 != passedVertices.end(); it2++) {
				if (*it == *it2) flag_3 = false;
			}
			if (flag_3) passedVertices.push_back(*it);
		}
		if (passedVertices.size() < count + 1) break;
		auto iterator = passedVertices.begin();
		advance(iterator, count);
		i = *iterator;
		tempList_1.clear();
	}
	cout << "Search in width: " << endl;
	cout << "Graph from which you start bypass: " << endl;
	for (auto i = passedVertices.begin(); i != passedVertices.end(); ++i) {
		cout << *i << " ";
	}
	cout << endl;
	cout << "Another vertices(not in your graph): " << endl;
	for (int i = 0; i < vertices; i++) {
		bool flag = true;
		for (auto it = passedVertices.begin(); it != passedVertices.end(); ++it) {
			if (i == *it) flag = false;
		}
		if (flag) cout << i << " ";
	}
	cout << endl;
}

void Graph::searchInDepth()
{
	list<int> passedVertices;
	int temp, count_1 = 0;
	cout << "Input element from which you will start: "; cin >> temp;
	passedVertices.push_back(temp);
	for (int i = temp; i < vertices;) {
		int count = 0;
		for (int j = 0; j < vertices; j++) {
			if (adjacencyMatrix.getMatrix()[i][j] != 0) {
				bool flag_1 = true;
				for (auto itpv = passedVertices.begin(); itpv != passedVertices.end(); itpv++) {
					if (j == *itpv) flag_1 = false;
				}
				if (flag_1) {
					passedVertices.push_back(j);
					count++;
					break;
				}
			}
		}
		if (!count) {
			count_1++;
		}
		else {
			count_1 = 0;
		}
		if (passedVertices.size() < count_1 + 1) {
			break;
		}
		auto it = passedVertices.begin();
		advance(it, passedVertices.size() - count_1 - 1);
		i = *it;
	}
	cout << "Search in depth: " << endl;
	cout << "Graph from which you start bypass: " << endl;
	for (auto i = passedVertices.begin(); i != passedVertices.end(); ++i) {
		cout << *i << " ";
	}
	cout << endl;
	cout << "Another vertices(not in your graph): " << endl;
	for (int i = 0; i < vertices; i++) {
		bool flag = true;
		for (auto it = passedVertices.begin(); it != passedVertices.end(); ++it) {
			if (i == *it) flag = false;
		}
		if (flag) cout << i << " ";
	}
	cout << endl;
}

int Graph::DijkstraAlgorithm(int begin, int end)
{
	int count = 0;
	vector<GraphElement> tableOfRoads;
	list<int> queue, tempList_1;
	for (int i = 0; i < vertices; i++) {
		if (i == begin) {
			GraphElement forPush(0, begin, false);
			tableOfRoads.push_back(forPush);
		}
		else {
			GraphElement forPush(this->sumWeigth() * 2, i, false);
			tableOfRoads.push_back(forPush);
		}
	}
	queue.push_back(begin);
	for (int i = begin; count < vertices; count++) {
		for (int j = 0; j < vertices; j++) {
			if (adjacencyMatrix.getMatrix()[i][j] != 0) {
				tempList_1.push_back(j);
				if (tableOfRoads[i].weigth + adjacencyMatrix.getMatrix()[i][j] < tableOfRoads[j].weigth) {
					tableOfRoads[j].weigth = tableOfRoads[i].weigth + adjacencyMatrix.getMatrix()[i][j];
				}
			}
		}
		for (auto it = tempList_1.begin(); it != tempList_1.end(); it++) {
			bool flag_3 = true;
			for (auto it2 = queue.begin(); it2 != queue.end(); it2++) {
				if (*it == *it2) flag_3 = false;
			}
			if (flag_3) queue.push_back(*it);
		}
		if (queue.size() < count + 1) break;
		auto iterator = queue.begin();
		advance(iterator, count);
		i = *iterator;
		tempList_1.clear();
	}
	return tableOfRoads[end].weigth;
}

int Graph::sumWeigth()
{
	int sum = 0;
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			sum += adjacencyMatrix.getMatrix()[i][j];
		}
	}
	return sum;
}

void Graph::FloydAlgoithm()
{
	weightMatrix.resize(vertices);
	roadMatrix.resize(vertices);
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			if (adjacencyMatrix.getMatrix()[i][j] == 0 && i != j) {
				weightMatrix.getMatrix()[i][j] = this->sumWeigth() * 2;
			}
			else {
				weightMatrix.getMatrix()[i][j] = adjacencyMatrix.getMatrix()[i][j];
			}
			if (adjacencyMatrix.getMatrix()[i][j] != 0) {
				roadMatrix.getMatrix()[i][j] = j;
			}
			else {
				roadMatrix.getMatrix()[i][j] = -1;
			}
			if (i == j) {
				roadMatrix.getMatrix()[i][j] = i;
				weightMatrix.getMatrix()[i][j] = 0;
			}
		}
	}

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			if (j == i) continue;
			for (int k = 0; k < vertices; k++) {
				if (k == i) continue;
				if (weightMatrix.getMatrix()[j][i] + weightMatrix.getMatrix()[i][k] < weightMatrix.getMatrix()[j][k]) {
					weightMatrix.getMatrix()[j][k] = weightMatrix.getMatrix()[j][i] + weightMatrix.getMatrix()[i][k];
					int temp_1 = i;
					while (true) {
						if (roadMatrix.getMatrix()[j][temp_1] == temp_1) {
							roadMatrix.getMatrix()[j][k] = temp_1;
							break;
						}
						else {
							temp_1 = roadMatrix.getMatrix()[j][temp_1];
						}
					}
				}
			}
		}
	}
	showGraphWeight();
	showGraphRoad();
}

void DijkstraForAll(Graph & graph) {
	for (int i = 0; i < graph.getVertices(); i++) {
		for (int j = 0; j < graph.getVertices(); j++) {
			if (graph.sumWeigth() * 2 == graph.DijkstraAlgorithm(i, j)) {
				cout << "From " << i << " to " << j << " no road." << endl;
			}
			else {
				cout << "From " << i << " to " << j << " = " << graph.DijkstraAlgorithm(i, j) << endl;
			}
		}
	}
}

int main() {
	int num, temp;
	Graph graph;
	cout << "If you wanna fill manually press 1, if random - 2, graph from lab - 3: "; cin >> temp;
	if (temp == 1) {
		cout << "How many vertex do you wanna add: "; cin >> num;
		for (int i = 0; i < num; i++) {
			int num_2;
			cout << "How many adjacent vertices has " << i << " vertex: "; cin >> num_2;
			if (!num_2) {
				graph.insert();
				continue;
			}
			int* ArrayOfVertices = new int[num_2];
			int* ArrayOfWeights = new int[num_2];
			cout << "Enter the vertices with which it is adjacent: ";
			for (int j = 0; j < num_2; j++) {
				cin >> ArrayOfVertices[j];
			}
			cout << "Enter weights of this edges: ";
			for (int j = 0; j < num_2; j++) {
				cin >> ArrayOfWeights[j];
			}
			graph.insert(ArrayOfVertices, ArrayOfWeights, num_2);
			delete[] ArrayOfVertices;
			delete[] ArrayOfWeights;
		}
		graph.showGraph();
		graph.searchInWidth();
		graph.searchInDepth();
		DijkstraForAll(graph);
	}
	if (temp == 2) {
		cout << "How many vertex do you wanna add: "; cin >> num;
		graph.randomGraph(num);
		graph.showGraph();
		graph.searchInWidth();
		graph.searchInDepth();
		DijkstraForAll(graph);
	}
	if (temp == 3) {
		graph.labGraph();
		graph.showGraph();
		graph.searchInWidth();
		graph.searchInDepth();
		graph.FloydAlgoithm();
	}

	system("pause");
	return 0;
}
