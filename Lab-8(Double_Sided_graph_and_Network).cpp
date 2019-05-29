#include <iostream>
#include <vector>
#include <string.h>
#include <limits.h>
#include <iomanip>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>

#define V 10 

using namespace std;

int graph_DoubleSided[V][V] = {
	//   a  b  c  d  e  f  g  i  j  z
		{0 ,11,8 ,8 ,0 ,0 ,0, 0,12, 0 }, //a
		{11,0 ,0 ,15,0 ,15,0 ,0 ,0 ,0 }, //b
		{8 ,0 ,0 ,12,0 ,0 ,0 ,0 ,0 ,0 }, //c
		{8 ,15,12,0 ,25,0 ,33,0 ,5 ,0 }, //d
		{0 ,0 ,0 ,25,0 ,18,0 ,0 ,14,9 }, //e
		{0 ,15,0 ,0 ,18,0 ,0 ,0 ,31,0 }, //f
		{0 ,0 ,0 ,33,0 ,0 ,0 ,0 ,0 ,7 }, //g
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,16,52}, //i
		{12,0 ,0 ,5 ,14,31,0 ,16,0 ,0 }, //j
		{0 ,0 ,0 ,0 ,9 ,0 ,7 ,52,0 ,0 }, //z
};

class Graph {
public:
	void maxPairsSecondMethod();
private:
	vector<vector<int>> DoubleEdges;
	vector<vector<int>> DoubleEdges_r;
	vector<vector<int>> adjMatrix;
	int size;
	void free(int& from, int& to, map<int, int>& pairs, map<int, int>& reversed, set<int>& used_right, set<int>& freeing);
public:
	Graph() {
		size = 0;
	}
	void FillDoubleVariant();
	void PrintDouble();
	void maxPairsFirstMethod();
};

void Graph::maxPairsSecondMethod() {
	map<int, int> reversed;
	map<int, int> pairs;
	set<int> used_right;
	set<int> freeing;

	for (int s = 0; s < size; s++) {
		for (const auto& vertex : DoubleEdges[s]) {
			if (used_right.find(vertex) != used_right.end()) {
				int to = vertex;
				int from = reversed[to];
				freeing.insert(to);
				free(from, to, pairs, reversed, used_right, freeing);
			}
			if (used_right.find(vertex) == used_right.end()) {
				pairs[s] = vertex;
				reversed[vertex] = s;
				used_right.insert(vertex);
				break;
			}
		}
	}

	for (const auto& x : pairs) {
		adjMatrix[x.first][x.second] = 2;
	}
	cout << endl;
	cout << "0 means : there's no pair possible" << endl;
	cout << "1 means : there's a pair possible" << endl;
	cout << "2 means : there's a pair" << endl;
	cout << "The matrix:\n";
	cout << "   ";
	char i = 65;
	for (int c = 0; c < size; i++, c++) {
		cout << " " << i;
	}
	cout << endl;
	cout << "   ";
	for (int c = 0; c < size; c++) {
		cout << "__";
	}
	cout << endl;
	i = 97;
	for (int c = 0; c < size; c++, i++) {
		cout << i << " |";
		for (int j = 0; j < size; j++) {
			cout << " " << adjMatrix[c][j];
		}
		cout << endl;
	}
	cout << endl;
}

void Graph::FillDoubleVariant() {
	size = 6;
	DoubleEdges = {
		{1, 2},    //a - 0
		{1, 2, 4}, //b - 1
		{3, 5},    //c - 2
		{0, 4, 5}, //d - 3
		{1, 3},    //e - 4
		{0, 4},    //f - 5
	};

	vector<vector<int>> temp(size, vector<int>(size, 0));
	adjMatrix = temp;
	for (int i = 0; i < size; i++) {
		for (const auto& number : DoubleEdges[i]) {
			adjMatrix[i][number] = 1;
		}
	}

	DoubleEdges_r = {
		{3, 5},    //A - 0
		{0, 1, 4}, //B - 1 
		{0, 1},    //C - 2
		{2, 4},    //D - 3
		{1, 3, 5}, //E - 4
		{2, 3},    //F - 5
	};
}

void Graph::PrintDouble() {
	cout << "Matrix of adjacency of the \"double-sided\" graf:\n";
	cout << endl;
	cout << "   ";
	char i = 65;
	for (int c = 0; c < size; i++, c++) {
		cout << " " << i;
	}
	cout << endl;
	cout << "   ";
	for (int c = 0; c < size; c++) {
		cout << "__";
	}
	cout << endl;
	i = 97;
	for (int c = 0; c < size; c++, i++) {
		cout << i << " |";
		for (int j = 0; j < size; j++) {
			cout << " " << adjMatrix[c][j];
		}
		cout << endl;
	}

	cout << "\nEdges:\n";
	for (int i = 0; i < size; i++) {
		cout << setw(2) << i << setw(2) << " : ";
		for (const auto& x : DoubleEdges[i]) {
			cout << x << " ";
		}
		cout << endl;
	}

	cout << "\nReversed:\n";
	for (int i = 0; i < size; i++) {
		cout << setw(2) << i << setw(2) << " : ";
		for (const auto& x : DoubleEdges_r[i]) {
			cout << x << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Graph::free(int& from, int& to, map<int, int> & pairs, map<int, int> & reversed, set<int> & used_right, set<int> & freeing) {
	for (const auto& vertex : DoubleEdges[from]) {
		if (vertex != to) {
			if (used_right.find(vertex) != used_right.end()) {
				if (freeing.find(vertex) != freeing.end()) continue;
				int to_t = vertex;
				int from_t = reversed[to_t];
				freeing.insert(to_t);
				free(from_t, to_t, pairs, reversed, used_right, freeing);
			}
			if (used_right.find(vertex) == used_right.end()) {
				pairs[from] = vertex;
				reversed[vertex] = from;
				used_right.insert(vertex);
				used_right.erase(to);
				freeing.erase(to);
				break;
			}
		}
	}
}

void Graph::maxPairsFirstMethod() {
	map<int, int> reversed;
	map<int, int> pairs;
	set<int> used_right;
	set<int> freeing;

	for (int s = 0; s < size; s++) {
		for (const auto& vertex : DoubleEdges[s]) {
			if (used_right.find(vertex) != used_right.end()) {
				int to = vertex;
				int from = reversed[to];
				freeing.insert(to);
				free(from, to, pairs, reversed, used_right, freeing);
			}
			if (used_right.find(vertex) == used_right.end()) {
				pairs[s] = vertex;
				reversed[vertex] = s;
				used_right.insert(vertex);
				break;
			}
		}
	}

	cout << "Pairs:\n" << endl;
	char start = 97, end = 65;
	for (const auto& item : pairs) {
		start += item.first;
		end += item.second;
		cout << start << " -> " << end << endl;
		start = 97;
		end = 65;
	}
	cout << "\nDone!";
	cout << endl;
}

bool bfs(int rGraph[V][V], int s, int t, int parent[])
{
	bool visited[V];
	memset(visited, 0, sizeof(visited));

	queue <int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	while (!q.empty())
	{
		int u = q.front();
		q.pop();

		for (int v = 0; v < V; v++)
		{
			if (visited[v] == false && rGraph[u][v] > 0)
			{
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}
	return (visited[t] == true);
}

void dfs(int rGraph[V][V], int s, bool visited[])
{
	visited[s] = true;
	for (int i = 0; i < V; i++)
		if (rGraph[s][i] && !visited[i])
			dfs(rGraph, i, visited);
}

void minCut(int graph[V][V], int s, int t)
{
	int u, v;
	int rGraph[V][V];
	for (u = 0; u < V; u++) {
		for (v = 0; v < V; v++) {
			rGraph[u][v] = graph[u][v];
		}
	}
	int parent[V];
	while (bfs(rGraph, s, t, parent))
	{
		int path_flow = INT_MAX;
		for (v = t; v != s; v = parent[v])
		{
			u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]);
		}
		for (v = t; v != s; v = parent[v])
		{
			u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}
	}
	bool visited[V];
	memset(visited, false, sizeof(visited));
	dfs(rGraph, s, visited);

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (visited[i] && !visited[j] && graph[i][j]) {
				cout << i << " - " << j << endl;
			}
		}
	}
	return;
}

int fordFulkerson(int graph[V][V], int s, int t)
{
	int u, v;

	int rGraph[V][V];
	for (u = 0; u < V; u++) {
		for (v = 0; v < V; v++) {
			rGraph[u][v] = graph[u][v];
		}
	}
	int parent[V];
	int max_flow = 0;
	while (bfs(rGraph, s, t, parent))
	{
		int path_flow = INT_MAX;
		for (v = t; v != s; v = parent[v])
		{
			u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]);
		}
		for (v = t; v != s; v = parent[v])
		{
			u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}
		max_flow += path_flow;
	}
	return max_flow;
}

int main() {
	Graph graph;
	graph.FillDoubleVariant();
	graph.PrintDouble();
	graph.maxPairsFirstMethod();
	cout << "Max flow: " << fordFulkerson(graph_DoubleSided, 0, 9) << endl;
	cout << "Min cut: " << endl;
	minCut(graph_DoubleSided, 0, 9);
	system("pause");
	return 0;
}
