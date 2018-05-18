// Code to read graph instances from a file.  Uses the Boost Graph Library (BGL).

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <fstream>

#include <boost/graph/adjacency_list.hpp>

#define LargeValue 99999999

using namespace std;
using namespace boost;

int const NONE = -1;  // Used to represent a node that does not exist

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

int exhaustiveColoring(Graph &g, int numColors, int t);
void RGT(Graph &g, Graph &bestG, int &bestGConflicts, int numColors, Graph::vertex_iterator start, pair<Graph::vertex_iterator, Graph::vertex_iterator> range);
void checkConflicts(Graph &g, Graph &bestG, int &bestGConflicts);
void printSolution(Graph &g, int numConflicts, string filePath_output);

struct VertexProperties
{
	pair<int, int> cell; // maze cell (x,y) value
	Graph::vertex_descriptor pred;
	bool visited;
	bool marked;
	int weight;
	int color;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
	int weight;
	bool visited;
	bool marked;
};

void initializeGraph(Graph &g, ifstream &fin)
// Initialize g using data from fin.
{
	int n, e;
	int j, k;

	fin >> n >> e;
	Graph::vertex_descriptor v;

	// Add nodes.
	for (int i = 0; i < n; i++)
		v = add_vertex(g);

	for (int i = 0; i < e; i++)
	{
		fin >> j >> k;
		add_edge(j, k, g);  // Assumes vertex list is type vecS
	}
}

void setNodeWeights(Graph &g, int w)
// Set all node weights to w.
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);

	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		g[*vItr].weight = w;
	}
}

int main()
{
	char x;
	ifstream fin;
	string fileName;

	// Read the name of the graph from the keyboard or
	// hard code it here for testing.

	fileName = "color12-3.input";

	//   cout << "Enter filename" << endl;
	//   cin >> fileName;

	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	try
	{
		cout << "Reading graph" << endl;
		Graph g;
		int numColors;
		int numConflicts = -1;
		fin >> numColors;
		initializeGraph(g, fin);

		cout << "Num nodes: " << num_vertices(g) << endl;
		cout << "Num edges: " << num_edges(g) << endl;
		cout << endl;

		// cout << g;

		numConflicts = exhaustiveColoring(g, numColors, 600);
		string output = "/Users/Cassie/source/color12-3.output";
		printSolution(g, numConflicts, output);
		system("pause");


	}
	catch (indexRangeError &ex)
	{
		cout << ex.what() << endl; exit(1);
	}
	catch (rangeError &ex)
	{
		cout << ex.what() << endl; exit(1);
	}
}

int exhaustiveColoring(Graph &g, int numColors, int t) {
	//gets start and end vertex iterators (which allow you to access the vertex)
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);

	Graph::vertex_iterator firstNode = vItrRange.first;
	Graph::vertex_iterator lastNode = vItrRange.second;

	//assign all vertex colors to 0, meaning lack of color
	for (Graph::vertex_iterator vItr = firstNode; vItr != lastNode; ++vItr) {
		g[*vItr].color = 0;
	}

	int i = 0;
	for (Graph::vertex_iterator vItr = firstNode; vItr != lastNode; ++vItr) {
		cout << "Vertex " << i << " color - " << g[*vItr].color << endl;
		i++;
	}
	system("pause");

	Graph bestG = g;
	int bestGConflicts = 0;
	
	RGT(g, bestG, bestGConflicts, numColors, firstNode, vItrRange);
	return bestGConflicts;
}

void RGT(Graph &g, Graph &bestG, int &bestGConflicts, int numColors, Graph::vertex_iterator start, pair<Graph::vertex_iterator, Graph::vertex_iterator> range) {
	for (int x = 1; x <= numColors; x++) {
		g[*start].color = x; //set color of graph for start node to x
		
		/*pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
		Graph::vertex_iterator firstNode = vItrRange.first;
		Graph::vertex_iterator lastNode = vItrRange.second;
		int i = 0;
		for (Graph::vertex_iterator vItr = firstNode; vItr != lastNode; ++vItr) {
			cout << "Vertex " << i << " color - " << g[*vItr].color << endl;
			i++;
		}
		system("pause");*/

		//cout << " 1 " << endl;
							 //check if start is the last night
		if ((start + 1) >= range.second) {  //this might not work....let me know if so
		//	cout << " 2 " << endl;
			checkConflicts(g, bestG, bestGConflicts);
		}

		//otherwise call function recursively
		else {
		//	cout << " 3 " << endl;
			RGT(g, bestG, bestGConflicts, numColors, ++start, range);
		}
		//cout << " 4 " << endl;
		g[*start].color = 0;
	}
	return;
}

void checkConflicts(Graph &g, Graph &bestG, int &bestGConflicts) {
	int conflicts = 0, color1 = 0, color2 = 0;
	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);

	for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr) {
		color1 = g[target(*eItr, g)].color;
		color2 = g[source(*eItr, g)].color;

		if (color1 == color2) {
			conflicts++;
		}
	}

	if (conflicts < bestGConflicts) {
		bestG = g;
	}
}

void printSolution(Graph &g, int numConflicts, string filePath_output) {
	ofstream myfile;
	myfile.open(filePath_output.c_str());

	myfile << "Total Conflicts: " << numConflicts << endl;

	for (int counter = 0; counter < num_vertices(g); counter++)	{
		myfile << counter << ": " << g[counter].color << endl;
	}

	myfile.close();
}