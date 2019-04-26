#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class MySquadMatrix {
private:
	int** squadMatrix;
	int size;
public:
	MySquadMatrix();
	MySquadMatrix(int);
	void resize(int);
	int** getMatrix() { return squadMatrix; }
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

class Graph {
private:
	int vertices;
	MySquadMatrix adjacencyMatrix;
public:
	Graph();
	int getvertices() { return vertices; }
	void insert(int*, int*);
	void remove(int);
	void showGraph();
};

Graph::Graph()
{
	vertices = 0;
	adjacencyMatrix.resize(0);
}

void Graph::insert(int* ArrayOfVertices = nullptr, int* ArrayOfWeights = nullptr)
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
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < vertices; j++) {
			if (j == ArrayOfVertices[j]) {
				adjacencyMatrix.getMatrix()[vertices - 1][j] = adjacencyMatrix.getMatrix()[j][vertices - 1] = ArrayOfWeights[count];
				count++;
			}
			else {
				adjacencyMatrix.getMatrix()[vertices - 1][j] = adjacencyMatrix.getMatrix()[j][vertices - 1] = 0;
			}
		}
	}
}

void Graph::remove(int)
{

}

void Graph::showGraph()
{
	cout << "Matrix of adjacent: " << endl;
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			cout << setw(5) << left << adjacencyMatrix.getMatrix()[i][j];
		}
		cout << endl;
	}
}

int main() {
	int num;
	cout << "How many vertex do you wanna add: "; cin >> num;
	Graph graph;
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
		graph.insert(ArrayOfVertices, ArrayOfWeights);
	}
	graph.showGraph();

	system("pause");
	return 0;
}
