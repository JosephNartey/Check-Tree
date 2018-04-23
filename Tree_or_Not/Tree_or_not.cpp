
// Joseph Nartey Opey
#include<iostream>
#include <list>
#include <limits.h>
using namespace std;

// Class for an undirected graph
class Graph
{
	int V; // No. of vertices
	list<int> *adjacen; // Pointer to an array containing adjacency lists
	bool Cyclic_Util(int v, bool visited[], int parent);
public:
	Graph(int V); // Constructor
	void Include_Edge(int v, int w); // to add an edge to graph
	bool Cyclic(); // returns true if there is a cycle
};

Graph::Graph(int V)
{
	this->V = V;
	adjacen = new list<int>[V];
}

void Graph::Include_Edge(int v, int w)
{
	adjacen[v].push_back(w); // Add w to v’s list.
	adjacen[w].push_back(v); // Add v to w’s list.
}

// A recursive function that uses visited[] and parent to detect
// cycle in subgraph reachable from vertex v.
bool Graph::Cyclic_Util(int v, bool visited[], int parent) 
{
	// Mark the current node as visited
	visited[v] = true;

	// Recur for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for (i = adjacen[v].begin(); i != adjacen[v].end(); ++i)
	{
		// If an adjacent is not visited, then recur for that adjacent
		if (!visited[*i])
		{
			if (Cyclic_Util(*i, visited, v))
				return true;
		}

		// If an adjacent is visited and not parent of current vertex,
		// then there is a cycle.
		else if (*i != parent)
			return true;
	}
	return false;
}

bool Graph::Cyclic()  // True if graph has cycle else false
{
	bool *visited = new bool[V]; // Mark all vertices as not visited and part of recursion
	for (int i = 0; i < V; i++)
		visited[i] = false;


	for (int u = 0; u < V; u++)
		if (!visited[u]) // No recur for u if it is already visited
			if (Cyclic_Util(u, visited, -1))
				return true;

	return false;
}

// Driver program to test above functions
int main()
{
	Graph g1(5);
	g1.Include_Edge(1, 0);
	g1.Include_Edge(0, 2);
	g1.Include_Edge(2, 0);
	g1.Include_Edge(0, 3);
	g1.Include_Edge(3, 4);
	g1.Cyclic() ? cout << "Undirected Graph isn't a tree\n" : cout
		<< "Undirected Graph is a tree\n";

	Graph g2(5);
	g2.Include_Edge(1, 0);
	g2.Include_Edge(0, 2);
	g2.Include_Edge(2, 1);
	g2.Include_Edge(0, 3);
	g2.Include_Edge(3, 4);
	g2.Cyclic() ? cout << "Undirected Graph isn't a tree\n" : cout
		<< "Undirected Graph is a tree\n";

	return 0;
}